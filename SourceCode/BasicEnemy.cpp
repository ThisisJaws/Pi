#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 320, timerReference, "Assets/Ships/EnemyShips/BasicShip.obj", "Assets/Ships/EnemyShips/BasicShipTexture.jpg", sceneManagerReference, driverReference){

	currentStage = stageA;
	timeElapsed = 0;
}

void BasicEnemy::combatManouver(irr::f32 deltaTime){
	timeElapsed += deltaTime;

	//Wait before performing a move
	if(timeElapsed > 2){
		//Perform the appropriate manouver for the stage
		switch(currentStage){
			case stageA:
				combatStageA(deltaTime);
				break;

			case stageB:
				combatStageB(deltaTime);
				break;

			case stageC:
				combatStageC(deltaTime);
				break;
		}
	}else{
		//Move forward slightly before performing the manouver
		move(-5, deltaTime);
	}
}

void BasicEnemy::combatStageA(irr::f32 deltaTime){
	if(getPosition().Y < 45){
		moveUp(turnSpeed / 2, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir));
	} else{
		currentStage = stageB;
	}
}

void BasicEnemy::combatStageB(irr::f32 deltaTime){
	if(getPosition().Y > -45){
		moveDown(turnSpeed / 2, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir));
	} else{
		currentStage = stageC;
	}
}

void BasicEnemy::combatStageC(irr::f32 deltaTime){
	moveSpeed /= 2;
	currentStage = stageEnd;
}