/* 
 * This is the class the enemies will use and will
 * controll all the AI that the enemies will need
 */

#ifndef ENEMYSHIP_H
#define	ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship{
    //VARIABLES
    
    //FUNCTIONS
public:
    //constructor
    EnemyShip(irr::core::vector3df spawnPos, float movementSpeed, int firingSpeed, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif	/* ENEMYSHIP_H */

