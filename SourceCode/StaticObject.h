/* 
 * this class is for all the static objects
 * trees, rocks, asteriods ect. that are just there
 * for collision - these objects wont get put into the update
 * list
 */

#ifndef STATICOBJECT_H
#define	STATICOBJECT_H

#include "Object.h"

class StaticObject : public Object{
    //VARIABLES
private:
    //used to rotate the object
    bool rotate;
    float rotSpeed;
    irr::core::vector3df rotAxis;
    
    //FUNCTIONS
public:
    //constructor
    StaticObject(const irr::core::vector3df &spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, bool updateRotation = true);

    virtual void tick(irr::f32 deltaTime) override;
};

#endif	/* STATICOBJECT_H */

