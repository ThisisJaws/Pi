#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference)
        : Collectible(spawnPosition, "Assets/Collectables/SpaceGem_a.obj", "Assets/Collectables/SpaceGemBronze.jpg", sceneManagerReference){

    scoreIncrease = 10000;
}

void Gem::performAction(PlayerShip* player){
	//Increase score
    player->increaseScore(scoreIncrease);
}
