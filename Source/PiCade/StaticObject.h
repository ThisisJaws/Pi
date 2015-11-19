/* 
 * this class is for all the static objects
 * trees, rocks, asteriods ect. that are just there
 * for collision
 */

#ifndef STATICOBJECT_H
#define	STATICOBJECT_H

#include "Object.h"

class StaticObject : public Object{
    //VARIABLES
    
    //FUNCTIONS
public:
    //constructor
    StaticObject(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif	/* STATICOBJECT_H */

