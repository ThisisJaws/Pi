# include "EnemyShip.h"
#include "Ammo.h"

EnemyShip::EnemyShip(PlayerShip *player, irr::core::vector3df spawnPosition, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference, const unsigned short &startingLives)
        : Ship(spawnPosition, player->getMovementSpeed(), firingSpeed, -1, timerReference, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, TYPE_SHIP_ENEMY, startingLives){

    //rotate to the right position
    getSceneNode()->setRotation(irr::core::vector3df(0, 180, 0));

    //set the player
    playerTarget = player;

    //init variables
	activeDistance = 125.0f;
    canMove = false;
	timeElapsed = 0;
	combatStartTime = 0.5f;

    rewardScore = true;
    scoreAmount = 1000;

	//Change the direction of the particle system
	engineParticleSystem->getEmitter()->setDirection(irr::core::vector3df(0, 0, 0.1f));
}

EnemyShip::~EnemyShip(){
    //clear the pointer, data gets deleted elsewhere
    playerTarget = 0;
}

void EnemyShip::tick(irr::f32 deltaTime){
    Ship::tick(deltaTime);

    if(canMove){
		//Let the ship move
        move(moveSpeed, deltaTime);
		if(timeElapsed >= combatStartTime){
			//Perform the combat manouver
			combatManouver(deltaTime);
		}else{
			timeElapsed += deltaTime;
		}
    }

    //check the distance of the player
    if(!canMove && (getPosition().Z - playerTarget->getPosition().Z) <= activeDistance){
		canMove = true;
    }

    //check if the enemy is too far off to the left of the screen
    if(getPosition().Z + 15 < playerTarget->getPosition().Z){
        //don,t reward score if the ship goes off scren
        rewardScore = false;
        markForDelete();
    }
}

void EnemyShip::markForDelete(){
    //check if the player should get some score
    if(rewardScore){
        playerTarget->increaseScore(scoreAmount);
    }
    //call the base function
    Object::markForDelete();
}
