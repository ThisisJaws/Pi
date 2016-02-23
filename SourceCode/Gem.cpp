#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
        : Collectible(spawnPosition, "Assets/Collectables/SpaceGem_a.obj", "Assets/Collectables/SpaceGemBronze.jpg", sceneManagerReference, audiereDevice){

    scoreIncrease = 10000;
}

void Gem::performAction(PlayerShip* player){
	//Increase score
    player->increaseScore(scoreIncrease);
}
