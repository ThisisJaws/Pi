#include "FastEnemy.h"

FastEnemy::FastEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference) 
	: EnemyShip(player, spawnPosition, 500, timerReference, "Assets/Ships/EnemyShips/FastShip.obj", "Assets/Ships/EnemyShips/FastShipTexture.jpg", sceneManagerReference, driverReference){

	//Start at the top of the screen
	changePosition(irr::core::vector3df(getPosition().X, 45, getPosition().Z));

	currentStage = stageA;
	timeElapsed = 0;

	//adjust move speed
	moveSpeed -= 20;
}

void FastEnemy::combatManouver(irr::f32 deltaTime){
	//Shoot constantly
	shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER);

	//Decide which stage to perform
	switch(currentStage){
		case stageA:
			combatStageA(deltaTime);
			break;

		case stageB:
			combatStageB(deltaTime);
			break;
	}
}

void FastEnemy::combatStageA(irr::f32 deltaTime){
	//Moves the ship to the top of the screen while shooting
	if(getPosition().Y > -45){
		moveDown(turnSpeed, deltaTime);
	} else{
		currentStage = stageB;
	}
}

void FastEnemy::combatStageB(irr::f32 deltaTime){
	//Moves the ship to the bottom of the screen while shooting
	if(getPosition().Y < 45){
		moveUp(turnSpeed, deltaTime);
	} else{
		currentStage = stageA;
	}
}