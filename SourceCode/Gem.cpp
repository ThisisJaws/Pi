#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, const unsigned int &scoreIncrease, const irr::io::path &textPath, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
        : Collectible(spawnPosition, "Assets/Collectables/SpaceGem_a.obj", textPath, sceneManagerReference, audiereDevice){

    this->scoreIncrease = scoreIncrease;
}

void Gem::performAction(PlayerShip* player){
	//Increase score
    player->increaseScore(scoreIncrease);

	//Display text
	displayText(scoreIncrease, "Points", player->getPosition());
}
