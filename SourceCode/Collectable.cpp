#include "Collectable.h"

Collectable::Collectable(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    //set spawn pos
    changePosition(spawnPosition);
    
    //set the movement speeds
    rotSpeed = 50.0f;
}

void Collectable::tick(irr::f32 deltaTime){
    //make the collectable rotate
    irr::core::vector3df rotation = getSceneNode()->getRotation();
    rotation.Y += rotSpeed * deltaTime;
    getSceneNode()->setRotation(rotation);
    
    //check for collision
    Object *collidedObject = checkCollision();
    if(collidedObject != NULL){
        if(collidedObject->getTypeID() == TYPE_PLAYER){
            //if we collide with the player then activate the power up
            activate(collidedObject);
            //then remove from the scene
            markForDelete();
        }
    }
}