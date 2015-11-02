#include "PlayerShip.h"

#include <iostream>

PlayerShip::PlayerShip(EventReceiver *eReceiver, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference),
    bullet("Assets/Laser_bullet.obj", "Assets/Lasr_bullet_purple.bmp", sceneManagerReference, driverReference){
    
    //set the object to not need lighting (for now)
    objectNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    
    //init variables
    currDeltaTime = 0;
    moveSpeed = 30.0f;
    turnSpeed = moveSpeed + 10.0f;
    this->eReceiver = eReceiver;
    
    //set the ship's default mode
    currentMode = flying;
}

void PlayerShip::tick(float deltaTime){  
    //updated global deltatime for other functions
    currDeltaTime = deltaTime;
    
    //update bullet
    bullet.tick(deltaTime);
    
    //make the player constantly move forward
    objectPosition.X += moveSpeed * deltaTime;
    
    //check for movement input
    if(eReceiver->isKeyDown(irr::KEY_KEY_A)){
        turnLeft();
    }else if(eReceiver->isKeyDown(irr::KEY_KEY_D)){
        turnRight();
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
        objectNode->setPosition(objectPosition);
        
        //perform camera updates
        updateCameraPositions();
        updateCamera();
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

void PlayerShip::shoot(){
    if(currentMode == shooting){
        //bullet.fire(objectPosition);
    }
}

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = objectPosition.X - 100;
    thirdPersonPosition.Y = objectPosition.Y + 50;
    thirdPersonPosition.Z = objectPosition.Z;
    
    sideViewPosition.X = objectPosition.X;
    sideViewPosition.Y = objectPosition.Y;
    sideViewPosition.Z = objectPosition.Z - 150;
}

void PlayerShip::updateCamera(){
    if(currentMode == flying){
        camera->setPosition(thirdPersonPosition);
    }else if(currentMode == shooting){
        camera->setPosition(sideViewPosition);
    }
    
    camera->setTarget(objectPosition);
}