#include "Ship.h"

Ship::Ship(float movementSpeed, int firingSpeed, int movementDirection, irr::ITimer *timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference, bool spawnOnConstruct)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, spawnOnConstruct){
    
    //set up variables
    moveSpeed = movementSpeed;
    turnSpeed = moveSpeed + 10.0f;
    //direction of movement +1 is along the positive X axis, -1 is along the negative X axis
    moveDir = movementDirection;
    
    //time between each bullet firing 1000 = 1 second
    timeBetweenShots = firingSpeed;
    timeSinceLastFire = 0;
    canFire = true;
    this->timerReference = timerReference;
    
    //reference the pointers
    smgr = sceneManagerReference;
    drv = driverReference;
}

Ship::~Ship(){
    //clear references (these get deleted properly elsewhere)
    smgr = 0;
    drv = 0;
    
    //delete the pointers
    delete smgr;
    delete drv;
    delete bullet;
}

void Ship::tick(irr::f32 deltaTime){
    //make the ship constantly move forward or backwards
    objectPosition.X += (moveSpeed * deltaTime) * moveDir;
    
    //check how long is left before the ship can fire again
    if(!canFire){
        if((timeSinceLastFire + timeBetweenShots) < timerReference->getRealTime()){
            canFire = true;
        }
    }
    
    //iterate through the list of fired bullets and update them
    for(std::list<Bullet*>::iterator bulletIterator = firedBullets.begin(); bulletIterator != firedBullets.end(); ++bulletIterator){
        if((*bulletIterator)->checkLifeTime()){
            //store the current iterator object
            Bullet *toDelete = *bulletIterator;
            //erase the object from the list
            bulletIterator = firedBullets.erase(bulletIterator);
            //delete the data stored in memory and invoke the destructor
            delete toDelete;
        }else{
            //call update function
            (*bulletIterator)->tick(deltaTime);
        }
    }
    
    //commit position changes
    if(!checkCollision()){
        updatePosition(objectPosition);
    }
}

void Ship::shoot(){
    if(canFire){
        //construct a new bullet
        bullet = new Bullet(smgr, drv);
        //fire it
        bullet->fire(objectPosition);
        
        //add it onto the list to be updated
        firedBullets.push_back(bullet);
        
        //clear the pointer to prevent memory leaks
        bullet = 0;
        
        //stop the ship firing immediately after
        canFire = false;
        
        //update the time since last fire variables
        timeSinceLastFire = timerReference->getRealTime();
    }
}