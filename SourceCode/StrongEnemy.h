/* 
 * class for the strong enemy type
 */

#ifndef STRONGENEMY_H
#define	STRONGENEMY_H

#include "EnemyShip.h"

class StrongEnemy : public EnemyShip{
    //FUNCTIONS
public:
    //constructor
    StrongEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference);
    
};

#endif	/* STRONGENEMY_H */

