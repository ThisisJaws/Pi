/* 
 * Class for the basic enemy type
 */

#ifndef BASICENEMY_H
#define	BASICENEMY_H

#include "EnemyShip.h"

class BasicEnemy : public EnemyShip{
    //FUNCTIONS
public:
    //constructor
    BasicEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference);
    
};

#endif	/* BASICENEMY_H */

