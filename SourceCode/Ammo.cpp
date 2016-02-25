#include "Ammo.h"

Ammo::Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
        : Collectible(spawnPosition, "Assets/Collectables/SpaceBattery_b.obj", "Assets/Collectables/SpaceBattery_b.jpg", sceneManagerReference, audiereDevice){

    ammoIncrease = 10;
}

void Ammo::performAction(PlayerShip* player){
	//Increase ammo
    player->increaseAmmo(ammoIncrease);

	//Display text
	displayText(ammoIncrease, "Ammo", getPosition());
}
