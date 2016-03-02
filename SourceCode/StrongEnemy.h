/* 
 * class for the strong enemy type
 */

#ifndef STRONGENEMY_H
#define	STRONGENEMY_H

#include "EnemyShip.h"

class StrongEnemy : public EnemyShip{
    //VARIABLES
private:
	//How many times to loop through the manouver
	const unsigned short COMBAT_LOOP_COUNT = 2;
	unsigned short currentLoop;

	//keep track of shots fired
	unsigned short shotsFired;
	const unsigned short MAX_SHOT_COUNT = 3;

	//Time elapsed before stage start
	float timeElapsed;

	//What stage of combat the Enemy is in
	enum combatStage{
		stageA,
		stageB,
		stageC,
		stageEnd
	}currentStage;

    //FUNCTIONS
public:
    //constructor
    StrongEnemy(PlayerShip *player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, audiere::AudioDevicePtr audiereDevice);

	//What the enemy will do when in range of the player
	virtual void combatManouver(irr::f32 deltaTime) override;

private:
	//Combat manouver stages
	void combatStageA(irr::f32 deltaTime);
	void combatStageB(irr::f32 deltaTime);
	void combatStageC(irr::f32 deltaTime);
};

#endif	/* STRONGENEMY_H */

