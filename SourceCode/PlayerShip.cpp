#include "PlayerShip.h"

PlayerShip::PlayerShip(EventReceiver *eReceiver, irr::ITimer *timerReference, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Ship(150.0f, 250, 1, timerReference, "Assets/Ships/PlayerShip.obj", "Assets/Ships/PlayerShipTexture.bmp", sceneManagerReference, driverReference){
    
    //change the object type
    typeID = TYPE_PLAYER;
    
    //init variables
    this->eReceiver = eReceiver;
    
    //init the camera variables
    tpDistance = 15;
    tpOffset = 7;
    
    sideViewDistance = 75;
    sideViewOffset = 60;
    
    cameraYOffset = 0;
    cameraXOffset = 0;
    maxYOffset = 100;
    maxXOffset = 100;
    
    modeChangeIteration = 0;
    
    //store the timer pointer so time between each shot can be fired
    timerReference = timerReference;
    
    //set the ship's default mode
    currentMode = flying;
}

void PlayerShip::tick(irr::f32 deltaTime){  
    //call base class function to handle shooting/movement
    Ship::tick(deltaTime);
    
    //check for and apply all position changes
    if(!checkCollision()){
        //check for movement input
        if(eReceiver->isKeyDown(irr::KEY_KEY_A)){
            turnLeft(turnSpeed, deltaTime);
        }else if(eReceiver->isKeyDown(irr::KEY_KEY_D)){
            turnRight(turnSpeed, deltaTime);
        }
        if(eReceiver->isKeyDown(irr::KEY_KEY_W)){
            moveUp(turnSpeed, deltaTime);
        }else if(eReceiver->isKeyDown(irr::KEY_KEY_S)){
            moveDown(turnSpeed, deltaTime);
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

void PlayerShip::turnLeft(float speed, irr::f32 deltaTime){
    if(currentMode == flying){
        if(cameraXOffset < maxXOffset){
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
        if(cameraXOffset > -maxXOffset){
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
    if(cameraYOffset > -maxYOffset){
        float moveBy = speed * deltaTime;
        
        //move the ship up
        updatePosition(0.0f, moveBy, 0.0f);
        //move the camera down
        cameraYOffset -= moveBy;
    }
}
void PlayerShip::moveDown(float speed, irr::f32 deltaTime){
    //if ship is still inside screen
    if(cameraYOffset < maxYOffset){
        float moveBy = speed * deltaTime;
        
        //move the ship down
        updatePosition(0.0f, -moveBy, 0.0f);
        //move the camera up
        cameraYOffset += moveBy;
    }
}

void PlayerShip::changeMode(){
    if(currentMode == flying){
        //switch the enum
        currentMode = shooting;
        //reset X pos so player is aligned properly
        irr::core::vector3df newPos = getPosition();
        newPos.X = 0;
        changePosition(newPos);
        cameraXOffset = 0;
    }else{
        //switch the enum
        currentMode = flying;
    }
    
    //move the mode iterator along one after the change
    modeChangeIteration++;
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