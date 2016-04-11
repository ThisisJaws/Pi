/* 
 * Class for the basic enemy type
 */

#ifndef BASICENEMY_H
#define	BASICENEMY_H

#include "EnemyShip.h"

class BasicEnemy : public EnemyShip{
	//VARIABLES
private:
	//What stage the combat manouver is in
	enum combatStage{
		stageA,
		stageB,
		stageC,
		stageEnd
	} currentStage;

	//Time elapsed before stage start
	float timeElapsed;
	//Elapsed for stage c
	float stageCTimeElpased;

    //FUNCTIONS
public:
    //constructor
    BasicEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference);

	//What the enemy will do when in range of the player
	virtual void combatManouver(irr::f32 deltaTime) override;

private:
	//Combat manouver stages
	void combatStageA(irr::f32 deltaTime);
	void combatStageB(irr::f32 deltaTime);
	void combatStageC(irr::f32 deltaTime);
};

#endif	/* BASICENEMY_H */

