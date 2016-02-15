/* 
 * class for the fast enemy type
 */

#ifndef FASTENEMY_H
#define	FASTENEMY_H

#include "EnemyShip.h"

class FastEnemy : public EnemyShip{
    //VARIABLES
private:
	//What stage the manouver is in
	enum combatStage{
		stageStart,
		stageA,
		stageB
	}currentStage;

	//Time (deltatime) elapsed
	float timeElapsed;
	
	//FUNCTIONS
public:
    //constructor
    FastEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference);
    
	//What the enemy will do when in range of the player
	virtual void combatManouver(irr::f32 deltaTime) override;

private:
	//Combat manouver stages
	void combatStageA(irr::f32 deltaTime);
	void combatStageB(irr::f32 deltaTime);
};

#endif	/* FASTENEMY_H */

