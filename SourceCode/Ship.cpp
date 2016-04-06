#include "Ship.h"

Ship::Ship(const irr::core::vector3df &spawnPosition, const float &movementSpeed, const int &firingSpeed, const int &movementDirection, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice, const irr::s32 &objectTypeID, const unsigned short &startingLives)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, spawnPosition, objectTypeID, true){

    //set up variables
    moveSpeed = movementSpeed;
    turnSpeed = moveSpeed / 2;
    //direction of movement +1 is along the positive Z axis, -1 is along the negative Z axis
    moveDir = movementDirection;

	//Set the rotation variables
	maxZRotate = 45;
	maxXRotate = 35;
	rotSpeed = 175;

    //time between each bullet firing 1000 = 1 second
    timeBetweenShots = firingSpeed;
    timeSinceLastFire = 0;
    canFire = true;
    this->timerReference = timerReference;

    //reference the pointers
    smgr = sceneManagerReference;

	//Set the lives
	lives = startingLives;

	//Create a prticle effect for the thruster
	engineParticleSystem = sceneManagerReference->addParticleSystemSceneNode(false, getSceneNode());
	//Set up an emitter for the system to use
	irr::scene::IParticleEmitter* em = engineParticleSystem->createPointEmitter(
		irr::core::vector3df(0.0f, 0.0f, -0.0001f),		// direction, also acts as speed
		50U, 70U,										// emit rate
		irr::video::SColor(0, 255, 255, 255),			// darkest color
		irr::video::SColor(0, 255, 255, 255),			// brightest color
		50, 100, 0,										// min and max age, angle
		irr::core::dimension2df(0.5f, 0.5f),			// min size
		irr::core::dimension2df(2.0f, 2.0f));			// max size

	engineParticleSystem->setEmitter(em);	//Give the emitter to the system
	em->drop();								//Safe to drop now we don't need it

	//Change the materials of the particle system
	engineParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	engineParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	engineParticleSystem->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture("Assets/FireParticle_b.png"));
	engineParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

	//Move the system back slighty to line up with the engine
	engineParticleSystem->setPosition(irr::core::vector3df(0, 0.5f, -7));

	//Init the audio
	shootSFX = audiere::OpenSound(audiereDevice, "Assets/Sound/Old/Shoot.mp3");
	damageSFX = audiere::OpenSound(audiereDevice, "Assets/Sound/Taking Damage/Damage.mp3");
}

Ship::~Ship(){
    //clear references (these get deleted properly elsewhere)
    smgr = 0;
    bullet = 0;
}

void Ship::tick(irr::f32 deltaTime){
	Object::tick(deltaTime);
    //check how long is left before the ship can fire again
    if(!canFire){
        if((timeSinceLastFire + timeBetweenShots) < timerReference->getRealTime()){
            canFire = true;
        }
    }

	//Check if the ship needs to be rotated back
	if(rotateBackX){
		//DOWN
		if(getRotation().X < 0){
			updateRotation(rotSpeed * deltaTime, 0, 0);
		}
		//UP
		if(getRotation().X > 0){
			updateRotation(-rotSpeed * deltaTime, 0, 0);
		}
	}
	if(rotateBackY){
		//RIGHT
		if(getRotation().Z > 0){
			updateRotation(0, 0, -rotSpeed * deltaTime);
		}
		//LEFT
		if(getRotation().Z < 0){
			updateRotation(0, 0, rotSpeed * deltaTime);
		}
	}

	//Set this to true at the end of each loop
	rotateBackX = true;
	rotateBackY = true;
}

float Ship::getMovementSpeed(){
	return moveSpeed;
}

unsigned short Ship::getLives(){
	return lives;
}

void Ship::increaseLives(const unsigned short &amount){
	lives += amount;
}

void Ship::dealDamage(const unsigned short &amount){
	//Play the damange sound effect
	damageSFX->play();

	//If there are no lives left, mark the ship for delete
	if(lives == 0){
		markForDelete();
	}

	//Take away the amount of lives
	lives -= amount;
}

bool Ship::shoot(const irr::core::vector3df &direction, const int &targetTypeID, const std::vector<irr::core::vector3df> &firingPositions){
	if(canFire && getSceneNode()->isVisible()){
		//For each position to fire from
		for(int i = 0; i < firingPositions.size(); i++){
			//construct a new bullet
			bullet = new Bullet(smgr);

			//then fire the bullet
			bullet->fire(firingPositions.at(i) + getPosition(), direction, moveSpeed, targetTypeID);

			//Play the sound
			shootSFX->reset();
			shootSFX->play();

			//clear the pointer to prevent memory leaks
			bullet = 0;
		}

        //stop the ship firing immediately after
        canFire = false;

        //update the time since last fire variables
        timeSinceLastFire = timerReference->getRealTime();

        //return true if the fire was successful
        return true;
    }else{
        //return false if the ship didn't shoot
        return false;
    }
}

void Ship::move(const float &speed, const irr::f32 &deltaTime){
    updatePosition(0.0f, 0.0f, speed * deltaTime);
}

void Ship::moveUp(const float &speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(0.0f, moveBy, 0.0f);
	//Rotate the ship up
	if(getRotation().X > -maxXRotate){
		updateRotation(-rotSpeed * deltaTime, 0, 0);
		rotateBackX = false;
	}
}

void Ship::moveDown(const float &speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(0.0f, -moveBy, 0.0f);
	//Rotate the ship down
	if(getRotation().X < maxXRotate){
		updateRotation(rotSpeed * deltaTime, 0, 0);
		rotateBackX = false;
	}
}

void Ship::turnLeft(const float & speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(-moveBy, 0.0f, 0.0f);
	//Rotate the ship to the left
	if(getRotation().Z < maxZRotate){
		updateRotation(0, 0, rotSpeed * deltaTime);
		rotateBackY = false;
	}
}

void Ship::turnRight(const float & speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(moveBy, 0.0f, 0.0f);
	//Rotate the ship to the right
	if(getRotation().Z > -maxZRotate){
		updateRotation(0, 0, -rotSpeed * deltaTime);
		rotateBackY = false;
	}
}
