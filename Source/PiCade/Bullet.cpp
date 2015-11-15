#include "Bullet.h"

//pass everythig through the constructor
Bullet::Bullet(irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object("Assets/LaserBulletSix.obj", "Assets/Laser_bullet_purple.bmp", sceneManagerReference, driverReference, false){
    
    fired = false;
    moveSpeed = 250.0f;
    
    currentLifeTime = 0;
    maxLifeTime = 1;
    
    //store the variables so it can be spawned later
    sceneMRef = sceneManagerReference;
    drvrRef = driverReference;
}

Bullet::~Bullet(){
    //clear the pointers reference (will get properly deleted elsewhere)
    sceneMRef = 0;
    drvrRef = 0;
    
    //delete the pointers
    delete sceneMRef;
    delete drvrRef;
}

void Bullet::tick(irr::f32 deltaTime){
    if(fired){
        //move the bullet forward
        objectPosition.X += moveSpeed * deltaTime;
        updatePosition(objectPosition);
        
        //update lifetime
        currentLifeTime += deltaTime;
    }
}

void Bullet::fire(irr::core::vector3df firePos){
    //spawn the object into the scene
    spawnObject("Assets/LaserBulletSix.obj", "Assets/Laser_bullet_purple.bmp", sceneMRef, drvrRef);
    //temp - set scale of bullet
    objectNode->setScale(irr::core::vector3df(30, 30, 30));
    
    //set the position
    objectPosition = firePos;
    //bullet has now been fired
    fired = true;
}

bool Bullet::checkLifeTime(){
    return currentLifeTime >= maxLifeTime;
}