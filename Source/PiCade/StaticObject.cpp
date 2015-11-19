#include "StaticObject.h"

StaticObject::StaticObject(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    changePosition(spawnPosition);
}