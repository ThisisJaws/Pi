#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 250, timerReference, "Assets/Ships/EnemyShips/BasicShip.obj", "Assets/Ships/EnemyShips/BasicShipTexture.jpg", sceneManagerReference, driverReference){

}