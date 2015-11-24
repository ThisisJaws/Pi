# include "EnemyShip.h"

EnemyShip::EnemyShip(PlayerShip *player, irr::core::vector3df spawnPosition, float movementSpeed, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
        : Ship(movementSpeed, firingSpeed, -1, timerReference, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    //change the type of the object
    typeID = TYPE_ENEMY;
    
    //set the spawn position
    changePosition(spawnPosition);
    
    //rotate to the right position
    getSceneNode()->setRotation(irr::core::vector3df(0, 180, 0));
    
    //set the player
    playerTarget = player;
    
    //init variables
    combatDistance = 300.0f;
    activeDistance = combatDistance + 100;
    canMove = false;
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
        shoot(irr::core::vector3df(moveDir, 0, 0));
    }
}