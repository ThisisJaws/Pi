#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
            : EnemyShip(player, spawnPosition, 750, timerReference, "Assets/Ships/EnemyShips/BasicShip.obj", "Assets/Ships/EnemyShips/BasicShipTexture.jpg", sceneManagerReference, driverReference){

	currentStage = stageA;
	timeElapsed = 0;

	//adjust turn speed
	turnSpeed /= 2;
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
	//Moves the ship to the top of the screen while shooting
	if(getPosition().Y < 45){
		moveUp(turnSpeed, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER);
	} else{
		currentStage = stageB;
	}
}

void BasicEnemy::combatStageB(irr::f32 deltaTime){
	//Moves the ship to the bottom of the screen while shooting
	if(getPosition().Y > -45){
		moveDown(turnSpeed, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER);
	} else{
		currentStage = stageC;
	}
}

void BasicEnemy::combatStageC(irr::f32 deltaTime){
	//Makes the ship leave the area
	moveSpeed /= 2;
	currentStage = stageEnd;
}