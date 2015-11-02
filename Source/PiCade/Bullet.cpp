#include "Bullet.h"

//pass everythig through the constructor
Bullet::Bullet(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    fired = false;
    moveSpeed = 50.0f;
}

void Bullet::tick(float deltaTime){
    //if the bulet has been fired then move it forward
    if(fired){
        objectPosition.X += moveSpeed * deltaTime;
    }
}

void Bullet::fire(irr::core::vector3df firePos){
    objectPosition = firePos;
    fired = true;
}