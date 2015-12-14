#include "StrongEnemy.h"

StrongEnemy::StrongEnemy(PlayerShip* player, irr::core::vector3df spawnPosition, irr::ITimer* timerReference, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
	: EnemyShip(player, spawnPosition, 500, timerReference, "Assets/Ships/EnemyShips/StrongShip.obj", "Assets/Ships/EnemyShips/StrongShipTexture.jpg", sceneManagerReference, driverReference){

	//Start the ship at the bottom
	changePosition(irr::core::vector3df(getPosition().X, -45, getPosition().Z));

	hitsTaken = 0;

	combatLoop = 2;
	currentLoop = 0;
	currentStage = stageA;
	speedChanged = false;
	shotsFired = 0;
}

void StrongEnemy::markForDelete(){
	hitsTaken++;

	if(hitsTaken >= 2){
		EnemyShip::markForDelete();
	}
}

void StrongEnemy::combatManouver(irr::f32 deltaTime){
	//Devide what stage to perform
	if(currentLoop < combatLoop){
		switch(currentStage){
			case stageA:
				combatStageA(deltaTime);
				break;

			case stageB:
				combatStageB(deltaTime);
				break;

			case StageC:
				combatStageC(deltaTime);
				break;
		}
	} else if(!speedChanged){
		moveSpeed /= 2;
		speedChanged = true;
	}
}

void StrongEnemy::combatStageA(irr::f32 deltaTime){
	if(shotsFired != 3){
		shoot(irr::core::vector3df(0, 0, moveDir));
		shotsFired++;
	} else{
		if(getPosition().Y < 0){
			moveUp(turnSpeed / 3, deltaTime);
		} else{
			shotsFired = 0;
			currentStage = stageB;
		}
	}
}

void StrongEnemy::combatStageB(irr::f32 deltaTime){

}

void StrongEnemy::combatStageC(irr::f32 deltaTime){

}
