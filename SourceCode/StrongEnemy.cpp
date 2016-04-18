#include "StrongEnemy.h"

StrongEnemy::StrongEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference)
	: EnemyShip(player, spawnPosition, 500, timerReference, "Assets/Ships/EnemyShips/StrongShip.obj", "Assets/Ships/EnemyShips/StrongShipTexture.jpg", sceneManagerReference, 2){

	//Start the ship at the bottom
	changePosition(irr::core::vector3df(getPosition().X, -45, getPosition().Z));

	currentLoop = 0;

	currentStage = stageA;

	timeElapsed = 0;

	shotsFired = 0;

	//adjust turn speed
	turnSpeed /= 3;

	//Set the cannon positions
	cannonPositions.push_back(irr::core::vector3df( 1, -1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df(-1, -1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df( 1,  1.5f, -1));
	cannonPositions.push_back(irr::core::vector3df(-1,  1.5f, -1));

	//Adjust the particle system's position
	engineParticleSystem->setPosition(irr::core::vector3df(0, 0.5f, -4));
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
	}
}

void StrongEnemy::combatStageA(irr::f32 deltaTime){
	if(shotsFired < MAX_SHOT_COUNT){
		//Shoots 3 bullets
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	} else{
		//Moves to the middle of the screen
		if(getPosition().Y < 0){
			moveVertical(turnSpeed, deltaTime);
		} else{
			//Reset shot count and advance stage
			shotsFired = 0;
			currentStage = stageB;
		}
	}
}

void StrongEnemy::combatStageB(irr::f32 deltaTime){
	if(shotsFired < MAX_SHOT_COUNT){
		//Shoots 3 bullets
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	} else{
		//Moves to the top of the screen
		if(getPosition().Y < 45){
			moveVertical(turnSpeed, deltaTime);
		} else{
			//Reset shot count and advance stage
			shotsFired = 0;
			currentStage = stageC;
		}
	}
}

void StrongEnemy::combatStageC(irr::f32 deltaTime){
	if(shotsFired != MAX_SHOT_COUNT){
		if(shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions)){
			shotsFired++;
		}
	}else{
		if(currentLoop < COMBAT_LOOP_COUNT){
			//Moves to the bottom of the screen
			if(getPosition().Y > -45){
				moveVertical(-turnSpeed, deltaTime);
			}else{
				if(currentLoop != COMBAT_LOOP_COUNT){
					//Reset shout count, increment loop count and reset stage
					shotsFired = 0;
					currentLoop++;
					currentStage = stageA;
				}
			}
		}else{
			//If the loop count is reached then leave the area
			if(timeElapsed > 1){
				moveSpeed /= 2;
				currentStage = stageEnd;
			} else{
				timeElapsed += deltaTime;
			}
		}
	}
}
