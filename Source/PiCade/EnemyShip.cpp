# include "EnemyShip.h"

EnemyShip::EnemyShip(irr::core::vector3df spawnPosition, float movementSpeed, int firingSpeed, irr::ITimer* timerReference, const irr::io::path& pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference)
        : Ship(movementSpeed, firingSpeed, -1, timerReference, "Assets/ship 1 obj.obj", "Assets/ship 1 obj.mtl", sceneManagerReference, driverReference){
    
    //set the position
    updatePosition(spawnPosition);
}