#include "StrongEnemy.h"

StrongEnemy::StrongEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 500, timerReference, "Assets/Ships/EnemyShips/StrongShip.obj", "Assets/Ships/EnemyShips/StrongShipTexture.jpg", sceneManagerReference, driverReference){

    hitsTaken = 0;

}

void StrongEnemy::markForDelete(){
    hitsTaken++;

    if(hitsTaken >= 2){
        EnemyShip::markForDelete();
    }
}

void StrongEnemy::combatManouver(irr::f32 deltaTime){}
