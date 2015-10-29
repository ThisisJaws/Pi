#include "PlayerShip.h"

#include <iostream>

PlayerShip::PlayerShip(const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference) 
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    //set the object to not need lighting (for now)
    objectNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    
    //init variables
    currDeltaTime = 0;
    moveSpeed = 30.0f;
    turnSpeed = moveSpeed + 10.0f;
    shipPosition = objectNode->getPosition();
    
    //set the ship's default mode
    currentMode = flying;
}

void PlayerShip::tick(float deltaTime){
    currDeltaTime = deltaTime;
    
    //make the player constantly move forward
    shipPosition.X += moveSpeed * currDeltaTime;
    
    //apply all position changes
    if(!checkCollision()){
        objectNode->setPosition(shipPosition);
        
        //perform camera updates
        updateCameraPositions();
        updateCamera();
    }
}

void PlayerShip::turnLeft(){
    shipPosition.Z += turnSpeed * currDeltaTime;
}
void PlayerShip::turnRight(){
    shipPosition.Z -= turnSpeed * currDeltaTime;
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

void PlayerShip::updateCameraPositions(){
    thirdPersonPosition.X = shipPosition.X - 100;
    thirdPersonPosition.Y = shipPosition.Y + 50;
    thirdPersonPosition.Z = shipPosition.Z;
    
    sideViewPosition.X = shipPosition.X;
    sideViewPosition.Y = shipPosition.Y;
    sideViewPosition.Z = shipPosition.Z - 150;
}

void PlayerShip::updateCamera(){
    if(currentMode == flying){
        camera->setPosition(thirdPersonPosition);
    }else if(currentMode == shooting){
        camera->setPosition(sideViewPosition);
    }
    
    camera->setTarget(shipPosition);
}