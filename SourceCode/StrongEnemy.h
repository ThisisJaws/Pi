/* 
 * class for the strong enemy type
 */

#ifndef STRONGENEMY_H
#define	STRONGENEMY_H

#include "EnemyShip.h"

class StrongEnemy : public EnemyShip{
    //VARIABLES
public:
    //strong enemy takes two hits to kill
    int hitsTaken;
    
    //FUNCTIONS
public:
    //constructor
    StrongEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference);
    
    //override
    void markForDelete();
};

#endif	/* STRONGENEMY_H */

