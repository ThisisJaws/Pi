#include "PlayerShip.h"

#include "Game.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference)
    : Ship(irr::core::vector3df(0, 0, 0), 200.0f, 250, 1, timerReference, "Assets/Ships/PlayerShip.obj", "Assets/Ships/PlayerShipTexture.jpg", sceneManagerReference, TYPE_SHIP_PLAYER, 3){

    //init variables
    score = 0;
	lifeIncreasePoints = 100000;
	previousLifeIncrease = score + lifeIncreasePoints;

	damageRecieved = false;
	flashCount = 0;
	maxFlash = 12;
	flashLength = 0.15f;
	timeSinceLastFlash = flashLength;

    ammo = 20;
    this->eReceiver = eReceiver;

    //Init the camera variables
    tpDistance = 30;
    tpOffset = 7;
    sideViewDistance = 75;
    sideViewOffset = 60;

	//Set the default contrains for the different modes
	flyingTop = 22;
	flyingBottom = -11;
	shootingTop = 44;
	shootingBottom = -44;

    //set the ship's default mode
    currentMode = flying;
	//Set the contrain variables for the above mode
	constrainX = 23;
	constrainTop = flyingTop;
	constrainBottom = flyingBottom;

    //Set up the light
	lightPos = irr::core::vector3df(0, 1000, -zOffSet);
    light = sceneManagerReference->addLightSceneNode(0, lightPos);
    light->setRadius(10000);

	//Turn on shadows for this scene node
	getSceneNode()->addShadowVolumeSceneNode(0, -1, false);

	//Make sure the controls aren't locked
	controlsLocked = false;

	//Default is false
	lost = false;

	//Set the cannon positions
	cannonPositions.push_back(irr::core::vector3df( 1, 1.5f, -1.5f));
	cannonPositions.push_back(irr::core::vector3df(-1, 1.5f, -1.5f));

	//Create the prticle effect for phase 2
	phase2AmbientParticles = sceneManagerReference->addParticleSystemSceneNode(false);
	//Set up an emitter for the system to use
	irr::scene::IParticleEmitter* em = phase2AmbientParticles->createBoxEmitter(irr::core::aabbox3df(-50, -150, -150, 50, 150, 150), irr::core::vector3df(0), 10U, 20U);
	//Give the emitter to the system
	phase2AmbientParticles->setEmitter(em);
	//Safe to drop now we don't need it
	em->drop();
	//Adjust position
	phase2AmbientParticles->setPosition(irr::core::vector3df(0, 0, 100));
	//Change the materials of the particle system
	phase2AmbientParticles->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	phase2AmbientParticles->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	phase2AmbientParticles->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture("Assets/PlaceHolders/particlegreen.jpg"));
	phase2AmbientParticles->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	//Turn off visibility
	phase2AmbientParticles->setVisible(false);

	//Assign the buffer
	noAmmoBuff.loadFromFile("Assets/Sound/No Ammo/noammo.wav");
	noAmmoSFX.setBuffer(noAmmoBuff);
}

PlayerShip::~PlayerShip(){
	//Make sure the light gets removed
	if(light){
		light->remove();
	}
	//Particles get cleaned up anyeway because they are a child
}

void PlayerShip::tick(irr::f32 deltaTime){
	Ship::tick(deltaTime);

	//If the player has recently received damage then begin to make the ship flash
	if(damageRecieved){
		if(timeSinceLastFlash >= flashLength){
			//Swap the visibility
			if(getSceneNode()->isVisible()){
				getSceneNode()->setVisible(false);
			} else{
				getSceneNode()->setVisible(true);
			}

			//Reset time since last flash back to 0
			timeSinceLastFlash = 0;
			//Increment the flash count
			flashCount++;
		} else{
			timeSinceLastFlash += deltaTime;
		}

		if(flashCount >= maxFlash){
			//Once the ship has flash enough times, reset everything
			flashCount = 0;
			damageRecieved = false;

			//Make sure it always ends visible
			getSceneNode()->setVisible(true);
		}
	}

	//check for collision with static Objects
	irr::s32 collidedObjectUniqueID = checkCollision(moveDir);
	if(collidedObjectUniqueID > 0){
		//If the ID is greater than 0 (0 is no collision) then search for the object
		Object *collidedObject = Game::getObjectReferenceByID(collidedObjectUniqueID);
		//Perform the collision checks for the object types
		if(collidedObject != NULL){
			switch(collidedObject->getTypeID()){
				case TYPE_STATIC_OBJECT:
					dealDamage();
					break;

				case TYPE_COLLECTABLE:
					//Dynamic cast to a collectable to see the activate function
					Collectible *collectible = dynamic_cast<Collectible *>(collidedObject);
					collectible->activate(this);
					break;

				case TYPE_SHIP_ENEMY:
					dealDamage();
					break;
			}
		}
	}

	//get the previous position to work out score
	unsigned int oldZ = (unsigned int)getPosition().Z;
	//move forward
	move(moveSpeed, deltaTime);
	//work out the distance traveled
	unsigned int newZ = (unsigned int)getPosition().Z;
	unsigned int difference = newZ - oldZ;

	//Update the phase 2 particles
	if(phase2AmbientParticles->isVisible()){
		phase2AmbientParticles->setPosition(irr::core::vector3df(phase2AmbientParticles->getPosition().X, phase2AmbientParticles->getPosition().Y, getPosition().Z));
	}

	//Check if the player can control the ship
	if(!controlsLocked){
		//increase score by the difference above
		increaseScore(difference);

		//Move the light along the Z axis
		lightPos.Z = getPosition().Z - zOffSet;
		light->setPosition(lightPos);

		//Move horizontally or vertically depending on input
		moveVertical(turnSpeed, eReceiver->getVerticalValue(), deltaTime);
		moveHorizontal(turnSpeed, eReceiver->getHorizontalValue(), deltaTime);

		//Perform camera updates after movement
		updateCamera(camera);

		//check if fire key was pressed
		if(eReceiver->isFirePressed() && currentMode == shooting){
			//check the ammo count
			if(ammo > 0){
				if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_ENEMY, cannonPositions)){
					//if the ship successfully shot then take away 1 ammo
					ammo--;
				}
			} else{
				//Play the sound letting the user know that they are out of ammo
				noAmmoSFX.play();
			}
		}
	}
}

void PlayerShip::addCamera(irr::scene::ICameraSceneNode* camera){
    this->camera = camera;
}

unsigned short PlayerShip::getAmmo(){
    return ammo;
}

void PlayerShip::increaseAmmo(unsigned short amount){
    ammo += amount;
}

unsigned int PlayerShip::getScore(){
    return score;
}

void PlayerShip::increaseScore(unsigned int amount){
	//Increment score
    score += amount;

	//Check to see if the player gets a life
	if(score >= previousLifeIncrease){
		//Increase the player's lives
		increaseLives();

		//Make a new score for the player to reach
		previousLifeIncrease += lifeIncreasePoints;

		//Animate some text
		displayText("Life", getPosition(), 1);
	}
}

void PlayerShip::markForDelete(){
	lost = true;
}

bool PlayerShip::playerLost(){
	return lost;
}

void PlayerShip::dealDamage(const unsigned short &amount){
	//Only damage the player if they haven't recently recieved any
	if(!damageRecieved){
		Ship::dealDamage(amount);
		damageRecieved = true;
	}
}

void PlayerShip::setControlLock(const bool &lock){
	controlsLocked = lock;
	//Deactivate the particles
	phase2AmbientParticles->setVisible(false);
}

bool PlayerShip::areControlsLocked(){
	return controlsLocked;
}

void PlayerShip::moveVertical(const float &speed, const float &force, const irr::f32 &deltaTime){
	//Get the doistance to move by
	float moveBy = speed * force * deltaTime;

	if(moveBy > 0){
		//If player is still inside the screen
		if(getPosition().Y + moveBy < constrainTop){
			//Move the ship up
			updatePosition(0.0f, moveBy, 0.0f);

			//Rotate the ship up
			if(getRotation().X > -maxXRotate * fabs(force)){
				updateRotation(rotSpeed * -force * deltaTime, 0, 0);
				rotateBackX = false;
			}
		}
	} else if(moveBy < 0){
		//If player is still inside the screen
		if(getPosition().Y + moveBy > constrainBottom){
			//Move the ship down
			updatePosition(0.0f, moveBy, 0.0f);

			//Rotate the ship down
			if(getRotation().X < maxXRotate * fabs(force)){
				updateRotation(rotSpeed * -force * deltaTime, 0, 0);
				rotateBackX = false;
			}
		}
	}
}

void PlayerShip::moveHorizontal(const float &speed, const float &force, const irr::f32 &deltaTime){
	if(currentMode == flying){
		//Get the doistance to move by
		float moveBy = speed * force * deltaTime;

		if(moveBy > 0){
			//If player is still inside the screen
			if(getPosition().X + moveBy < constrainX){
				//Move the ship to the right
				updatePosition(moveBy, 0.0f, 0.0f);

				//Rotate the ship to the right
				if(getRotation().Z > -maxZRotate * fabs(force)){
					updateRotation(0, 0, rotSpeed * -force * deltaTime);
					rotateBackY = false;
				}
			}
		} else if(moveBy < 0){
			//If player is still inside the screen
			if(getPosition().X + moveBy > -constrainX){
				//Move the ship to the left
				updatePosition(moveBy, 0.0f, 0.0f);

				//Rotate the ship to the left
				if(getRotation().Z < maxZRotate * fabs(force)){
					updateRotation(0, 0, rotSpeed * -force * deltaTime);
					rotateBackY = false;
				}
			}
		}
	}
}

void PlayerShip::changeMode(const int &increaseSpeedByFactor){
    if(currentMode == flying){
        //Switch the enum
        currentMode = shooting;

		//Change the player constrain
		constrainTop = shootingTop;
		constrainBottom = shootingBottom;

		//Activate the particles
		phase2AmbientParticles->setVisible(true);
    }else{
        //Switch the enum
        currentMode = flying;

		//Change the player constrain
		constrainTop = flyingTop;
		constrainBottom = flyingBottom;
    }

	//Increase the player's speed
	moveSpeed += 25 * increaseSpeedByFactor;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode *sceneCamera){
    irr::core::vector3df cameraLookAt;
    irr::core::vector3df cameraPosition;

    //update the camera's position
    if(currentMode == flying){
        //update position
        cameraPosition = getPosition();
		cameraPosition.X = 0;
        cameraPosition.Y = (irr::f32)tpOffset;
        cameraPosition.Z -= (irr::f32)tpDistance;

        //update look at
        cameraLookAt = cameraPosition;
        cameraLookAt.Z += 1;
    }else if(currentMode == shooting){
        //update position
        cameraPosition = getPosition();
        cameraPosition.X += sideViewDistance;
		cameraPosition.Y = 0;
		cameraPosition.Z += sideViewOffset;

        //update look at
        cameraLookAt = cameraPosition;
        cameraLookAt.X -= 1;
    }

    //apply look at and position changes
    sceneCamera->setTarget(cameraLookAt);
    sceneCamera->setPosition(cameraPosition);
}
