# include "EnemyShip.h"

EnemyShip::EnemyShip(PlayerShip *player, irr::core::vector3df spawnPosition, float movementSpeed, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
        : Ship(movementSpeed, firingSpeed, -1, timerReference, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    //set the spawn position
    objectPosition = spawnPosition;
    
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
    if(computeDistance(getPosition(), playerTarget->getPosition()) <= combatDistance){
        shoot();
    }
}

float EnemyShip::computeDistance(irr::core::vector3df positionA, irr::core::vector3df positionB){
    return sqrt((pow(positionB.X, 2) - pow(positionA.X, 2)) + (pow(positionB.Y, 2) - pow(positionA.Y, 2)) + (pow(positionB.Z, 2) - pow(positionA.Z, 2)));
}