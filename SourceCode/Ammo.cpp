#include "Ammo.h"

Ammo::Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Collectable(spawnPosition, "Mesh", "Texture", sceneManagerReference, driverReference){
    
    ammoIncrease = 10;
}

void Ammo::activate(PlayerShip* player){
    player->increaseAmmo(ammoIncrease);
}