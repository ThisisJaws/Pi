/* 
 * This is the class the enemies will use and will
 * control all the AI that the enemies will need
 */

#ifndef ENEMYSHIP_H
#define	ENEMYSHIP_H

#include "Ship.h"
#include "PlayerShip.h"

class EnemyShip : public Ship{
    //VARIABLES
private:
    //the player, the enemy's target
    PlayerShip *playerTarget;
    
    //how far the player needs to be for the enemy to start shooting
    float combatDistance;
    //how far the player has to be for the enemy to start moving
    float activeDistance;
    bool canMove;
    
    //FUNCTIONS
public:
    //constructor
    EnemyShip(PlayerShip *player, irr::core::vector3df spawnPos, float movementSpeed, int firingSpeed, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    //destructor
    ~EnemyShip();
    
    virtual void tick(irr::f32 deltaTime) override;
};

#endif	/* ENEMYSHIP_H */

