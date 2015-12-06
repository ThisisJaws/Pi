#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Collectable(spawnPosition, "Assets/Collectables/SpaceGem.obj", "Assets/Collectables/SpaceGem_Orange.jpg", sceneManagerReference, driverReference){

    scoreIncrease = 100;
}

void Gem::activate(PlayerShip* player){
    player->increaseScore(scoreIncrease);
}
