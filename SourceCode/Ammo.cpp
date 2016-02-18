#include "Ammo.h"

Ammo::Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference)
        : Collectable(spawnPosition, "Assets/Collectables/SpaceBattery_b.obj", "Assets/Collectables/SpaceBattery_b.jpg", sceneManagerReference){

    ammoIncrease = 10;
}

void Ammo::performAction(PlayerShip* player){
	//Increase ammo
    player->increaseAmmo(ammoIncrease);
}
