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
protected:
    //the player, the enemy's target
    PlayerShip *playerTarget;

private:
    //How far the player has to be for the enemy to start moving
    float activeDistance;
    bool canMove;
	//Time variables for starting manouvers
	float timeElapsed;
	float combatStartTime;

    //reward score when the enemy dies
    bool rewardScore;
    unsigned int scoreAmount;

    //FUNCTIONS
public:
    //constructor
    EnemyShip(PlayerShip *player, irr::core::vector3df spawnPos, int firingSpeed, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, const unsigned short &startingLives = 0);
    //destructor
    virtual ~EnemyShip();

    virtual void tick(irr::f32 deltaTime) override;

    //overriden so the enemy can award score
    virtual void markForDelete() override;

protected:
	//What to do when the enemy is in range of the player
	virtual void combatManouver(irr::f32 deltaTime) = 0;
};

#endif	/* ENEMYSHIP_H */

