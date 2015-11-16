/* 
 * This is the class the enemies will use and will
 * control all the AI that the enemies will need
 */

#ifndef ENEMYSHIP_H
#define	ENEMYSHIP_H

#include "Ship.h"
#include "PlayerShip.h"

#include <cmath>

class EnemyShip : public Ship{
    //VARIABLES
private:
    //the player, the enemy's target
    PlayerShip *playerTarget;
    
    //how far the player needs to be for the enemy to engage
    float combatDistance;
    
    //FUNCTIONS
public:
    //constructor
    EnemyShip(PlayerShip *player, irr::core::vector3df spawnPos, float movementSpeed, int firingSpeed, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    //destructor
    ~EnemyShip();
    
    //override
    virtual void tick(irr::f32 deltaTime);
    
private:
    //computes the distance between two objects
    float computeDistance(irr::core::vector3df positionA, irr::core::vector3df positionB);
};

#endif	/* ENEMYSHIP_H */

