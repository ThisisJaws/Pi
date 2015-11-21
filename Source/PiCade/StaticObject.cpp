#include "StaticObject.h"

StaticObject::StaticObject(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference){
    
    //make sure it is the ight type
    typeID = TYPE_STATIC_OBJECT;
    
    changePosition(spawnPosition);
}

void StaticObject::tick(irr::f32 deltaTime){}