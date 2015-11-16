#include "PlayerShip.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Ship(30.0f, 250, 1, timerReference, "Assets/ship 1 obj.obj", "Assets/ship 1 obj.mtl", sceneManagerReference, driverReference){
    
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
    
    //check if fire key was pressed
    if(eReceiver->isKeyDown(irr::KEY_SPACE)){
        shoot();
    }
    
    //temp, changing mode will not be handled by user input
    if(eReceiver->isKeyDown(irr::KEY_KEY_G)){
        changeMode();
    }
    
    //apply all position changes
    if(!checkCollision()){
        //perform camera updates
        updateCameraPositions();
        updateCamera(camera);
    }
}

void PlayerShip::addCamera(irr::scene::ICameraSceneNode* camera){
    this->camera = camera;
}

void PlayerShip::changeMode(){
    if(currentMode == flying){
        currentMode = shooting;
    }else{
        currentMode = flying;
    }
}

void PlayerShip::turnLeft(){
    if(currentMode == flying){
        //update the ship position to go to the left
        objectPosition.Z += turnSpeed * currDeltaTime;
    }
}
void PlayerShip::turnRight(){
    if(currentMode == flying){
        //update the ship position to go to the right
        objectPosition.Z -= turnSpeed * currDeltaTime;
    }
}
void PlayerShip::moveUp(){
    objectPosition.Y += turnSpeed * currDeltaTime;
}
void PlayerShip::moveDown(){
    objectPosition.Y -= turnSpeed * currDeltaTime;
}

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = objectPosition.X - tpDistance;
    thirdPersonPosition.Y = objectPosition.Y + tpOffset;
    thirdPersonPosition.Z = objectPosition.Z;
    
    sideViewPosition.X = objectPosition.X + sideViewOffset;
    sideViewPosition.Y = objectPosition.Y;
    sideViewPosition.Z = objectPosition.Z - sideViewDistance;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode* sceneCamera){
    if(currentMode == flying){
        //set pos of camera
        sceneCamera->setPosition(thirdPersonPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = objectPosition;
        lookAtPos.X += tpOffset;
        sceneCamera->setTarget(objectPosition);
    }else if(currentMode == shooting){
        //set pos of camera
        sceneCamera->setPosition(sideViewPosition);
        //set the target for the camera to look at
        irr::core::vector3df lookAtPos = objectPosition;
        lookAtPos.X += sideViewOffset;
        sceneCamera->setTarget(lookAtPos);
    }
}