#include "FastEnemy.h"

FastEnemy::FastEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 125, timerReference, "Assets/Ships/EnemyShips/FastShip.obj", "Assets/Ships/EnemyShips/FastShipTexture.jpg", sceneManagerReference, driverReference){

}

void FastEnemy::combatManouver(irr::f32 deltaTime){}