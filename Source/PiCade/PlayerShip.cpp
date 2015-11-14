#include "PlayerShip.h"

#include <iostream>

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object("Assets/ship 1 obj.obj", "Assets/ship 1 obj.mtl", sceneManagerReference, driverReference){
    
    //init variables
    currDeltaTime = 0;
    moveSpeed = 30.0f;
    turnSpeed = moveSpeed + 10.0f;
    this->eReceiver = eReceiver;
    
    //store the pointers to be able to fire new bullets
    smgr = sceneManagerReference;
    drv = driverReference;
    
    //set the ship's default mode
    currentMode = flying;
}

PlayerShip::~PlayerShip(){
    //clear references (these get deleted properly elsewhere)
    smgr = 0;
    drv = 0;
    
    //delete the pointers
    delete smgr;
    delete drv;
    delete bullet;
}

void PlayerShip::tick(float deltaTime){  
    //updated global deltatime for other functions
    currDeltaTime = deltaTime;
    
    //iterate through the vector of fire bullets and update them
    for(int i = 0; i < firedBullets.size(); i ++){
        firedBullets[i].tick(deltaTime);
    }
        
    //make the player constantly move forward
    objectPosition.X += moveSpeed * deltaTime;
    
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
        updatePosition(objectPosition);
        
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

void PlayerShip::shoot(){
    if(currentMode == shooting){
        //construct a new bullet
        bullet = new Bullet(smgr, drv);
        //fire it
        bullet->fire(objectPosition);
        
        //add it onto the vector to be updated
        firedBullets.push_back(*bullet);
        
        //clear the pointer to prevent memory leaks
        bullet = 0;
    }
}

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = objectPosition.X - 100;
    thirdPersonPosition.Y = objectPosition.Y + 50;
    thirdPersonPosition.Z = objectPosition.Z;
    
    sideViewPosition.X = objectPosition.X + 100;
    sideViewPosition.Y = objectPosition.Y;
    sideViewPosition.Z = objectPosition.Z - 200;
}

void PlayerShip::updateCamera(irr::scene::ICameraSceneNode* sceneCamera){
    if(currentMode == flying){
        //set pos of camera
        sceneCamera->setPosition(thirdPersonPosition);
        //set the target for the camera to look at
        sceneCamera->setTarget(objectPosition);
    }else if(currentMode == shooting){
        //set pos of camera
        sceneCamera->setPosition(sideViewPosition);
        //set the target for thecamera to look at
        irr::core::vector3df lookAtPos = objectPosition;
        lookAtPos.X += 100;
        sceneCamera->setTarget(lookAtPos);
    }
}