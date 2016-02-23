#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::gui::IGUIEnvironment *guiEnvironment, audiere::AudioDevicePtr audiereDevice)
        : Collectible(spawnPosition, "Assets/Collectables/SpaceGem_a.obj", "Assets/Collectables/SpaceGemBronze.jpg", sceneManagerReference, guiEnvironment, audiereDevice){

    scoreIncrease = 10000;
}

void Gem::performAction(PlayerShip* player){
	//Increase score
    player->increaseScore(scoreIncrease);
}
