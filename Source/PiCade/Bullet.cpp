#include "Bullet.h"

//pass everythig through the constructor
Bullet::Bullet(irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object("Assets/PlaceHolders/LaserBulletSix.obj", "Assets/PlaceHolders/Laser_bullet_purple.bmp", sceneManagerReference, driverReference, false){
    
    fired = false;
    moveSpeed = 250.0f;
    
    currentLifeTime = 0;
    maxLifeTime = 5.0f;
    
    //store the variables so it can be spawned later
    sceneMRef = sceneManagerReference;
    drvrRef = driverReference;
}

Bullet::~Bullet(){
    //clear the pointers reference (will get properly deleted elsewhere)
    sceneMRef = 0;
    drvrRef = 0;
}

void Bullet::tick(irr::f32 deltaTime){
    if(fired){
        //move the bullet forward
        updatePosition(direction * (moveSpeed * deltaTime));
        
        //update lifetime
        currentLifeTime += deltaTime;
        
        //bullets get deleted based off of lifetime, so when thy collide increase their life time to forcea deletion
        if(checkCollision()){
            currentLifeTime = maxLifeTime;
        }
    }
}

void Bullet::fire(irr::core::vector3df firePos, irr::core::vector3df direction){
    //spawn the object into the scene
    spawnObject("Assets/PlaceHolders/LaserBulletSix.obj", "Assets/PlaceHolders/Laser_bullet_purple.bmp", sceneMRef, drvrRef);
    
    //temp - set scale of bullet
    getSceneNode()->setScale(irr::core::vector3df(30, 30, 30));
    
    //set the direction
    this->direction = direction;
    
    //set the position
    changePosition(firePos);
    
    //bullet has now been fired
    fired = true;
}

bool Bullet::checkLifeTime(){
    return currentLifeTime >= maxLifeTime;
}