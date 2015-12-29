#include "PlayerShip.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
    : Ship(irr::core::vector3df(0, 0, 0), 150.0f, 250, 1, timerReference, "Assets/Ships/PlayerShip.obj", "Assets/Ships/PlayerShipTexture.jpg", sceneManagerReference, driverReference, TYPE_SHIP_PLAYER){

    //init variables
    score = 0;
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

	lost = false;
}

void PlayerShip::tick(irr::f32 deltaTime){
    Ship::tick(deltaTime);

	//check for collision with static Objects
	irr::scene::ISceneNode *collidedNode = checkCollision(moveDir);
	/*if(collidedNode != NULL){
		if(collidedNode->getID() == TYPE_STATIC_OBJECT){
			lost = true;
		}
	}*/

	//get the previous position to work out score
	unsigned int oldZ = getPosition().Z;
	//move forward
	move(moveSpeed, deltaTime);
	//work out the distance traveled
	unsigned int newZ = getPosition().Z;
	unsigned int difference = newZ - oldZ;
	//increase score by the difference
	increaseScore(difference);

	//check for and apply all position changes
	if(eReceiver->isKeyDown(irr::KEY_KEY_A)){
		turnLeft(turnSpeed, deltaTime);
	} else if(eReceiver->isKeyDown(irr::KEY_KEY_D)){
		turnRight(turnSpeed, deltaTime);
	}
	if(eReceiver->isKeyDown(irr::KEY_KEY_W)){
		moveUp(turnSpeed, deltaTime);
	} else if(eReceiver->isKeyDown(irr::KEY_KEY_S)){
		moveDown(turnSpeed, deltaTime);
	}

    //perform camera updates
    updateCameraPositions();
    updateCamera(camera);

    //check if fire key was pressed
    if(eReceiver->isKeyDown(irr::KEY_SPACE) && currentMode == shooting){
        //check the ammo count
        if(ammo > 0){
            if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_ENEMY)){
                //if the ship successfully shot then take away 1 ammo
                ammo--;
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
    score += amount;
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

void PlayerShip::turnLeft(float speed, irr::f32 deltaTime){
    if(currentMode == flying){
        if(getPosition().X > basePosition.X - maxXOffset){
            float moveBy = speed * deltaTime;

            //move the ship to the left
            updatePosition(-moveBy, 0.0f, 0.0f);
            //move the camera to the right
            cameraXOffset += moveBy;
        }
    }
}
void PlayerShip::turnRight(float speed, irr::f32 deltaTime){
    if(currentMode == flying){
        if(getPosition().X < basePosition.X + maxXOffset){
            float moveBy = speed * deltaTime;

            //move the ship to the right
            updatePosition(moveBy, 0.0f, 0.0f);
            //move the camera to the left
            cameraXOffset -= moveBy;
        }
    }
}
void PlayerShip::moveUp(float speed, irr::f32 deltaTime){
    //if ship is still inside screen
    if(getPosition().Y < basePosition.Y + maxYOffset){
        float moveBy = speed * deltaTime;

        //move the ship up
        updatePosition(0.0f, moveBy, 0.0f);
        //move the camera down
        cameraYOffset -= moveBy;
    }
}
void PlayerShip::moveDown(float speed, irr::f32 deltaTime){
    //if ship is still inside screen
    if(getPosition().Y > basePosition.Y - minYOffset){
        float moveBy = speed * deltaTime;

        //move the ship down
        updatePosition(0.0f, -moveBy, 0.0f);
        //move the camera up
        cameraYOffset += moveBy;
    }
}

void PlayerShip::changeMode(int increaseSpeedByFactor){
    if(currentMode == flying){
        //switch the enum
        currentMode = shooting;

        //update the offsets
        maxYOffset = 50;
        minYOffset = -maxYOffset;

    }else{
        //switch the enum
        currentMode = flying;

        //update the offsets
        maxYOffset = 20;
        minYOffset = -8;
    }

    //reset X and Y pos so player is aligned properly
    irr::core::vector3df newPos = getPosition();
    newPos.X = 0;
    newPos.Y = 0;
    changePosition(newPos);
    //make sure the offsets are reset
    cameraXOffset = 0;
    cameraYOffset = 0;

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