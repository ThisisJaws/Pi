#include "PlayerShip.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Ship(30.0f, 250, 1, timerReference, "Assets/PlaceHolders/ship 1 obj.obj", "Assets/PlaceHolders/ship 1 obj.mtl", sceneManagerReference, driverReference){
    
    //init variables
    currDeltaTime = 0;
    this->eReceiver = eReceiver;
    
    //init the camera variables
    tpDistance = 150;
    tpOffset = tpDistance / 2;
    sideViewDistance = 300;
    sideViewOffset = sideViewDistance / 2;
    
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
    
    //check if fire key was pressed
    if(eReceiver->isKeyDown(irr::KEY_SPACE) && currentMode == shooting){
        shoot(irr::core::vector3df(moveDir, 0, 0));
    }
    
    //temp, changing mode will not be handled by user input
    if(eReceiver->isKeyDown(irr::KEY_KEY_G)){
        changeMode();
    }
    
    //perform camera updates
    updateCameraPositions();
    updateCamera(camera);
}

void PlayerShip::addCamera(irr::scene::ICameraSceneNode* camera){
    this->camera = camera;
}

void PlayerShip::changeMode(){
    if(currentMode == flying){
        //switch the enum
        currentMode = shooting;
        //reset Z pos so player is aligned properly
        irr::core::vector3df newPos = getPosition();
        newPos.Z = 0;
        changePosition(newPos);
    }else{
        //switch the enum
        currentMode = flying;
    }
}

void PlayerShip::turnLeft(){
    if(currentMode == flying){
        //update the ship position to go to the left
        updatePosition(0.0f, 0.0f, turnSpeed * currDeltaTime);
    }
}
void PlayerShip::turnRight(){
    if(currentMode == flying){
        //update the ship position to go to the right
        updatePosition(0.0f, 0.0f, (turnSpeed * currDeltaTime) * -1);
    }
}
void PlayerShip::moveUp(){
    updatePosition(0.0f, turnSpeed * currDeltaTime, 0.0f);
}
void PlayerShip::moveDown(){
    updatePosition(0.0f, (turnSpeed * currDeltaTime) * -1, 0.0f);
}

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = getPosition().X - tpDistance;
    thirdPersonPosition.Y = getPosition().Y + tpOffset;
    thirdPersonPosition.Z = getPosition().Z;
    
    sideViewPosition.X = getPosition().X + sideViewOffset;
    sideViewPosition.Y = getPosition().Y;
    sideViewPosition.Z = getPosition().Z - sideViewDistance;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode* sceneCamera){
    if(currentMode == flying){
        //set pos of camera
        sceneCamera->setPosition(thirdPersonPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = getPosition();
        lookAtPos.X += tpOffset;
        sceneCamera->setTarget(lookAtPos);
    }else if(currentMode == shooting){
        //set pos of camera
        sceneCamera->setPosition(sideViewPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = getPosition();
        lookAtPos.X += sideViewOffset;
        sceneCamera->setTarget(lookAtPos);
    }
}