# include "EnemyShip.h"
#include "Ammo.h"

EnemyShip::EnemyShip(PlayerShip *player, irr::core::vector3df spawnPosition, float movementSpeed, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
        : Ship(spawnPosition, movementSpeed, firingSpeed, -1, timerReference, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){

    //change the type of the object
    typeID = TYPE_SHIP_ENEMY;

    //rotate to the right position
    getSceneNode()->setRotation(irr::core::vector3df(0, 180, 0));

    //set the player
    playerTarget = player;

    //init variables
    combatDistance = 125.0f;
    activeDistance = combatDistance + 50;
    canMove = false;

    rewardScore = true;
    scoreAmount = 500;
}

EnemyShip::~EnemyShip(){
    //clear the pointer, data gets deleted elsewhere
    playerTarget = 0;
}

void EnemyShip::tick(irr::f32 deltaTime){
    if(canMove){
        //call the base class function
        Ship::tick(deltaTime);
    }

    //check the distance of the player
    if(!canMove && getPosition().getDistanceFrom(playerTarget->getPosition()) <= activeDistance){
        canMove = true;
    }
    if(playerTarget != NULL && getPosition().getDistanceFrom(playerTarget->getPosition()) <= combatDistance){
        shoot(irr::core::vector3df(0, 0, moveDir));
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
