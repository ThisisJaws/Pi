#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Collectable(spawnPosition, "Assets/Collectables/SpaceGem.obj", "Assets/Collectables/SpaceGemOrange.jpg", sceneManagerReference, driverReference){

    scoreIncrease = 10000;
}

void Gem::activate(PlayerShip* player){
	//Call base
	Collectable::activate(player);
	//Increase score
    player->increaseScore(scoreIncrease);
}
