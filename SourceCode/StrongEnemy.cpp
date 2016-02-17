#include "StrongEnemy.h"

StrongEnemy::StrongEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference)
	: EnemyShip(player, spawnPosition, 500, timerReference, "Assets/Ships/EnemyShips/StrongShip.obj", "Assets/Ships/EnemyShips/StrongShipTexture.jpg", sceneManagerReference, 2){

	//Start the ship at the bottom
	changePosition(irr::core::vector3df(getPosition().X, -45, getPosition().Z));

	currentLoop = 0;

	currentStage = stageA;

	speedChanged = false;
	shotsFired = 0;

	//adjust turn speed
	turnSpeed /= 3;

	//Set the cannon positions
	cannonPositions.push_back(irr::core::vector3df( 1, -1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df(-1, -1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df( 1,  1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df(-1,  1.5f, -1));
}

void StrongEnemy::combatManouver(irr::f32 deltaTime){
	//Devide what stage to perform
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

		default:
			//Do nothing as default
			break;
	}
}

void StrongEnemy::combatStageA(irr::f32 deltaTime){
	if(shotsFired < maxShotCount){
		//Shoots 3 bullets
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	} else{
		//Moves to the middle of the screen
		if(getPosition().Y < 0){
			moveUp(turnSpeed, deltaTime);
		} else{
			//Reset shot count and advance stage
			shotsFired = 0;
			currentStage = stageB;
		}
	}
}

void StrongEnemy::combatStageB(irr::f32 deltaTime){
	if(shotsFired < maxShotCount){
		//Shoots 3 bullets
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	} else{
		//Moves to the top of the screen
		if(getPosition().Y < 45){
			moveUp(turnSpeed, deltaTime);
		} else{
			//Reset shot count and advance stage
			shotsFired = 0;
			currentStage = stageC;
		}
	}
}

void StrongEnemy::combatStageC(irr::f32 deltaTime){
	if(shotsFired != maxShotCount){
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	}else{
		if(currentLoop < combatLoop){
			//Moves to the bottom of the screen
			if(getPosition().Y > -45){
				moveDown(turnSpeed, deltaTime);
			}else{
				if(currentLoop != combatLoop){
					//Reset shout count, increment loop count and reset stage
					shotsFired = 0;
					currentLoop++;
					currentStage = stageA;
				}
			}
		}else{
			//If the loop count is reached then leave the area
			moveSpeed /= 2;
			currentStage = stageEnd;
		}
	}
}
