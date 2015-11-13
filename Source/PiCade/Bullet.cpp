#include "Bullet.h"

//pass everythig through the constructor
Bullet::Bullet(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct) 
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, spawnOnConstruct){
    
    fired = false;
    moveSpeed = 100.0f;
    
    //temp - set scale of bullet
    //objectNode->setScale(irr::core::vector3df(30, 30, 30));
}

void Bullet::tick(float deltaTime){
    //if the bullet has been fired then move it forward
    if(fired){
        objectPosition.X += moveSpeed * deltaTime;
        updatePosition(objectPosition);
    }
}

void Bullet::fire(irr::core::vector3df firePos){
    objectPosition = firePos;
    fired = true;
}