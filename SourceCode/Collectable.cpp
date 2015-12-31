#include "Collectable.h"

#include "Game.h"

Collectable::Collectable(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, true, spawnPosition, TYPE_COLLECTABLE){

    //set the rotation speed
    rotSpeed = 50.0f;

	//Resize all collectibles, might be temp
	getSceneNode()->setScale(irr::core::vector3df(2));
}

void Collectable::tick(irr::f32 deltaTime){
    //make the collectable rotate
    irr::core::vector3df rotation = getSceneNode()->getRotation();
    rotation.Y += rotSpeed * deltaTime;
    getSceneNode()->setRotation(rotation);
}

void Collectable::activate(PlayerShip * player){
	//Base function simply marks for delete
	markForDelete();
}
