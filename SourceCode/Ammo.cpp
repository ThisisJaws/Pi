#include "Ammo.h"

Ammo::Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Collectable(spawnPosition, "Assets/Collectables/SpaceBattery_b.obj", "Assets/Collectables/SpaceBattery_b.jpg", sceneManagerReference, driverReference){

    ammoIncrease = 10;
}

void Ammo::activate(PlayerShip* player){
	//Call base
	Collectable::activate(player);
	//Increase ammo
    player->increaseAmmo(ammoIncrease);
}
