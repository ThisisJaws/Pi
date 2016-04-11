#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference)
            : EnemyShip(player, spawnPosition, 750, timerReference, "Assets/Ships/EnemyShips/BasicShip.obj", "Assets/Ships/EnemyShips/BasicShipTexture.jpg", sceneManagerReference){

	currentStage = stageA;
	timeElapsed = 0;
	stageCTimeElpased = 0;

	//adjust turn speed
	turnSpeed /= 2;

	//Set up the shooting positions
	cannonPositions.push_back(irr::core::vector3df(1, 0, -10));
	cannonPositions.push_back(irr::core::vector3df(-1, 0, -10));

	//Adjust the particle system's position
	engineParticleSystem->setPosition(irr::core::vector3df(0, 0.3f, -4));
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
	if(getPosition().Y < 40){
		moveUp(turnSpeed, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions);
	} else{
		currentStage = stageB;
	}
}

void BasicEnemy::combatStageB(irr::f32 deltaTime){
	//Moves the ship to the bottom of the screen while shooting
	if(getPosition().Y > -40){
		moveDown(turnSpeed, deltaTime);
		shoot(irr::core::vector3df(0, 0, moveDir), TYPE_SHIP_PLAYER, cannonPositions);
	} else{
		currentStage = stageC;
	}
}

void BasicEnemy::combatStageC(irr::f32 deltaTime){
	//Makes the ship leave the area
	if(stageCTimeElpased > 1){
		moveSpeed /= 2;
		currentStage = stageEnd;
	} else{
		stageCTimeElpased += deltaTime;
	}
}