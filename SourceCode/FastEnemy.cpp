#include "FastEnemy.h"

FastEnemy::FastEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 60.0f, 125, timerReference, "Assets/Ships/EnemyShips/FastShip.obj", "Assets/Ship/EnemyShips/FastShip.bmp", sceneManagerReference, driverReference){
    
}