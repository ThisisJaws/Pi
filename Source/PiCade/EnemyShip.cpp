# include "EnemyShip.h"

EnemyShip::EnemyShip(PlayerShip *player, irr::core::vector3df spawnPosition, float movementSpeed, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
        : Ship(movementSpeed, firingSpeed, -1, timerReference, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    //set the spawn position
    changePosition(spawnPosition);
    
    //rotate to the right position
    getSceneNode()->setRotation(irr::core::vector3df(0, 180, 0));
    
    //set the player
    playerTarget = player;
    
    //init variables
    combatDistance = 100.0f;
}

EnemyShip::~EnemyShip(){
    //clear the pointer, data gets deleted elsewhere
    playerTarget = 0;
    
    //delete pointers
    delete playerTarget;
}

void EnemyShip::tick(irr::f32 deltaTime){
    //call the base class function
    Ship::tick(deltaTime);

    //check the distance of the player
    if(getPosition().getDistanceFrom(playerTarget->getPosition()) <= combatDistance){
        shoot();
    }
}