#include "Gem.h"

Gem::Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
        : Collectable(spawnPosition, "Mesh", "Texture", sceneManagerReference, driverReference){
    
    scoreIncrease = 100;
}

void Gem::activate(PlayerShip* player){
    //increase score
}