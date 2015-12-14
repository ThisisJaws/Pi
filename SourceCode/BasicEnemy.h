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

	//What the enemy will do when in range of the player
	virtual void combatManouver(irr::f32 deltaTime) override;
};

#endif	/* BASICENEMY_H */

