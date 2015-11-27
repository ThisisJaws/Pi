#include "FastEnemy.h"

FastEnemy::FastEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 60.0f, 125, timerReference, "Assets/Ships/EnemyShips/FastShip.obj", "Assets/Ships/EnemyShips/FastShipTexture.bmp", sceneManagerReference, driverReference){
    
}