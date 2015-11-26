#include "FastEnemy.h"

FastEnemy::FastEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 30.0f, 250, timerReference, "Assets/Ships/EnemyShips/EnemyShip3.obj", "Assets/PlaceHolders/ship 1 obj.mtl", sceneManagerReference, driverReference){
    
}