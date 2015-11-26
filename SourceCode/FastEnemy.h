/* 
 * class for the fast enemy type
 */

#ifndef FASTENEMY_H
#define	FASTENEMY_H

#include "EnemyShip.h"

class FastEnemy : public EnemyShip{
    //FUNCTIONS
public:
    //constructor
    FastEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference);
    
};

#endif	/* FASTENEMY_H */

