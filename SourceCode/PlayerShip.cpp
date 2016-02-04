#include "PlayerShip.h"

#include "Game.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
    : Ship(irr::core::vector3df(0, 0, 0), 150.0f, 250, 1, timerReference, "Assets/Ships/PlayerShip.obj", "Assets/Ships/PlayerShipTexture.jpg", sceneManagerReference, driverReference, TYPE_SHIP_PLAYER, 3){

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

    //init the camera variables
    tpDistance = 30;
    tpOffset = 7;

    sideViewDistance = 75;
    sideViewOffset = 60;

    //set up the current offsets as the flying mode ones for the camera
    cameraYOffset = 0;
    maxYOffset = 20;
    minYOffset = 8;

    cameraXOffset = 0;
    maxXOffset = 20;

	//Set the base position, will always start at 0, 0, 0
	basePosition = irr::core::vector3df(0);

    //set the ship's default mode
    currentMode = flying;

    //Set up the light
    light = sceneManagerReference->addLightSceneNode(0, irr::core::vector3df(0, 1000, 0));
    light->setRadius(10000);

	controlsLocked = false;

	//Default is false
	lost = false;

	//Set the cannon positions
	cannonPositions.push_back(irr::core::vector3df( 1, 1.5f, -1.5f));
	cannonPositions.push_back(irr::core::vector3df(-1, 1.5f, -1.5f));
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
					Collectable *collectible = dynamic_cast<Collectable *>(collidedObject);
					collectible->activate(this);
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
	//Move the light along the Z axis
	irr::core::vector3df lightPos = getPosition();
	lightPos.Y = 1000;
	lightPos.X = 0;
	light->setPosition(lightPos);

	//Check if the player can control the ship
	if(!controlsLocked){
		//increase score by the difference above
		increaseScore(difference);

		//check for and apply all position changes
		//Left
		if(eReceiver->isKeyDown(irr::KEY_KEY_A)){
			turnLeft(turnSpeed, deltaTime);
		}
		//Right
		if(eReceiver->isKeyDown(irr::KEY_KEY_D)){
			turnRight(turnSpeed, deltaTime);
		}
		//Up
		if(eReceiver->isKeyDown(irr::KEY_KEY_W)){
			moveUp(turnSpeed, deltaTime);
		}
		//Down
		if(eReceiver->isKeyDown(irr::KEY_KEY_S)){
			moveDown(turnSpeed, deltaTime);
		}

		//Perform camera updates after movement
		updateCameraPositions();
		updateCamera(camera);

		//check if fire key was pressed
		if(eReceiver->isKeyDown(irr::KEY_KEY_J) && currentMode == shooting){
			//check the ammo count
			if(ammo > 0){
				if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_ENEMY, cannonPositions)){
					//if the ship successfully shot then take away 1 ammo
					ammo--;
				}
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
	}
}

void PlayerShip::changePosition(irr::core::vector3df newPosition){
	//Call the super function
	Ship::changePosition(newPosition);

	//Adjust the base position
	basePosition = newPosition;

	//Reset the camera offsets
	cameraXOffset = 0;
	cameraYOffset = 0;
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
}

bool PlayerShip::areControlsLocked(){
	return controlsLocked;
}

void PlayerShip::moveUp(const float &speed, const irr::f32 &deltaTime){
    //if ship is still inside screen
    if(getPosition().Y < basePosition.Y + maxYOffset){
        float moveBy = speed * deltaTime;

        //move the ship up
        updatePosition(0.0f, moveBy, 0.0f);
        //move the camera down
        cameraYOffset -= moveBy;

		//Rotate the ship up
		if(getRotation().X > -maxXRotate){
			updateRotation(-rotSpeed * deltaTime, 0, 0);
			rotateBack = false;
		}
    }
}
void PlayerShip::moveDown(const float &speed, const irr::f32 &deltaTime){
    //if ship is still inside screen
    if(getPosition().Y > basePosition.Y - minYOffset){
        float moveBy = speed * deltaTime;

        //move the ship down
        updatePosition(0.0f, -moveBy, 0.0f);
        //move the camera up
        cameraYOffset += moveBy;

		//Rotate the ship down
		if(getRotation().X < maxXRotate){
			updateRotation(rotSpeed * deltaTime, 0, 0);
			rotateBack = false;
		}
    }
}
void PlayerShip::turnLeft(const float &speed, const irr::f32 &deltaTime){
	if(currentMode == flying){
		if(getPosition().X > basePosition.X - maxXOffset){
			float moveBy = speed * deltaTime;

			//move the ship to the left
			updatePosition(-moveBy, 0.0f, 0.0f);
			//move the camera to the right
			cameraXOffset += moveBy;

			//Rotate the ship to the left
			if(getRotation().Z < maxZRotate){
				updateRotation(0, 0, rotSpeed * deltaTime);
				rotateBack = false;
			}
		}
	}
}
void PlayerShip::turnRight(const float &speed, const irr::f32 &deltaTime){
	if(currentMode == flying){
		if(getPosition().X < basePosition.X + maxXOffset){
			float moveBy = speed * deltaTime;

			//move the ship to the right
			updatePosition(moveBy, 0.0f, 0.0f);
			//move the camera to the left
			cameraXOffset -= moveBy;

			//Rotate the ship to the right
			if(getRotation().Z > -maxZRotate){
				updateRotation(0, 0, -rotSpeed * deltaTime);
				rotateBack = false;
			}
		}
	}
}

void PlayerShip::changeMode(const int &increaseSpeedByFactor){
    if(currentMode == flying){
        //switch the enum
        currentMode = shooting;

        //update the offsets
        maxYOffset = 50;
        minYOffset = maxYOffset;

    }else{
        //switch the enum
        currentMode = flying;

        //update the offsets
        maxYOffset = 20;
        minYOffset = 8;
    }

	//Increase the player's speed
	moveSpeed += 25 * increaseSpeedByFactor;
	turnSpeed += 10 * increaseSpeedByFactor;
}

void PlayerShip::updateCameraPositions(){
    //third person view update
    thirdPersonPosition.X = getPosition().X;
    thirdPersonPosition.Y = getPosition().Y + tpOffset;
    thirdPersonPosition.Z = getPosition().Z - tpDistance;

    //side view update
    sideViewPosition.X = getPosition().X + sideViewDistance;
    sideViewPosition.Y = getPosition().Y;
    sideViewPosition.Z = getPosition().Z + sideViewOffset;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode *sceneCamera){
    irr::core::vector3df cameraLookAt;
    irr::core::vector3df cameraPosition;

    //update the camera's position
    if(currentMode == flying){
        //update position
        cameraPosition = thirdPersonPosition;
        cameraPosition.Y += cameraYOffset;
        cameraPosition.X += cameraXOffset;

        //update look at
        cameraLookAt = cameraPosition;
        cameraLookAt.Z += 1;
    }else if(currentMode == shooting){
        //update position
        cameraPosition = sideViewPosition;
        cameraPosition.Y += cameraYOffset;
        cameraPosition.X += cameraXOffset;

        //update look at
        cameraLookAt = cameraPosition;
        cameraLookAt.X -= 1;
    }

    //apply look at and position changes
    sceneCamera->setTarget(cameraLookAt);
    sceneCamera->setPosition(cameraPosition);
}
