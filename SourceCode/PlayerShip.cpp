#include "PlayerShip.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Ship(150.0f, 250, 1, timerReference, "Assets/Ships/PlayerShip.obj", "Assets/Ships/PlayerShipTexture.bmp", sceneManagerReference, driverReference){
    
    //change the object type
    typeID = TYPE_PLAYER;
    
    //init variables
    currDeltaTime = 0;
    this->eReceiver = eReceiver;
    
    //init the camera variables
    tpDistance = 50;
    tpOffset = tpDistance / 2; 
    
    sideViewDistance = 150;
    sideViewOffset = sideViewDistance / 2;
    
    modeChangeIteration = 0;
    
    //store the timer pointer so time between each shot can be fired
    timerReference = timerReference;
    
    //set the ship's default mode
    currentMode = flying;
}

void PlayerShip::tick(irr::f32 deltaTime){  
    //call base class function to handle shooting/movement
    Ship::tick(deltaTime);
    
    //updated global deltatime for other functions
    currDeltaTime = deltaTime;
    
    //check for and apply all position changes
    if(!checkCollision()){
        //check for movement input
        if(eReceiver->isKeyDown(irr::KEY_KEY_A)){
            turnLeft();
        }else if(eReceiver->isKeyDown(irr::KEY_KEY_D)){
            turnRight();
        }
        if(eReceiver->isKeyDown(irr::KEY_KEY_W)){
            moveUp();
        }else if(eReceiver->isKeyDown(irr::KEY_KEY_S)){
            moveDown();
        }
    }
    
    //perform camera updates
    updateCameraPositions();
    updateCamera(camera);
    
    //check if fire key was pressed
    if(eReceiver->isKeyDown(irr::KEY_SPACE) && currentMode == shooting){
        shoot(irr::core::vector3df(0, 0, moveDir));
    }
    
    if(modeChangePoints[modeChangeIteration] > 0 && getPosition().Z >= modeChangePoints[modeChangeIteration]){
        //if we have a point that is greater than 0 and player the player's X is past that then change modes
        changeMode();
    }
}

void PlayerShip::addCamera(irr::scene::ICameraSceneNode* camera){
    this->camera = camera;
}

void PlayerShip::addChangeModePoints(int zPoints[6]){
    //copy the array
    std::copy(zPoints, zPoints+6, modeChangePoints);
}

void PlayerShip::turnLeft(){
    if(currentMode == flying){
        //update the ship position to go to the left
        updatePosition((turnSpeed * currDeltaTime) * -1, 0.0f, 0.0f);
    }
}
void PlayerShip::turnRight(){
    if(currentMode == flying){
        //update the ship position to go to the right
        updatePosition(turnSpeed * currDeltaTime, 0.0f, 0.0f);
    }
}
void PlayerShip::moveUp(){
    updatePosition(0.0f, turnSpeed * currDeltaTime, 0.0f);
}
void PlayerShip::moveDown(){
    updatePosition(0.0f, (turnSpeed * currDeltaTime) * -1, 0.0f);
}

void PlayerShip::changeMode(){
    if(currentMode == flying){
        //switch the enum
        currentMode = shooting;
        //reset X pos so player is aligned properly
        irr::core::vector3df newPos = getPosition();
        newPos.X = 0;
        changePosition(newPos);
    }else{
        //switch the enum
        currentMode = flying;
    }
    
    //move the mode iterator along one after the change
    modeChangeIteration++;
}

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = getPosition().X;
    thirdPersonPosition.Y = getPosition().Y + tpOffset;
    thirdPersonPosition.Z = getPosition().Z - tpDistance;
    
    sideViewPosition.X = getPosition().X + sideViewDistance;
    sideViewPosition.Y = getPosition().Y;
    sideViewPosition.Z = getPosition().Z + sideViewOffset;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode* sceneCamera){
    if(currentMode == flying){
        //set pos of camera
        sceneCamera->setPosition(thirdPersonPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = getPosition();
        lookAtPos.Y += tpOffset;
        sceneCamera->setTarget(lookAtPos);
    }else if(currentMode == shooting){
        //set pos of camera
        sceneCamera->setPosition(sideViewPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = getPosition();
        lookAtPos.Z += sideViewOffset;
        sceneCamera->setTarget(lookAtPos);
    }
}