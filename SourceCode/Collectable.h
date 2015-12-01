/* 
 * The base class for all the collectables
 * all the individual properties for the collectables
 * will be in classes that inherit from this, this class
 * will just check for collisions
 */

#ifndef COLLLECTABLE_H
#define	COLLLECTABLE_H

#include "Object.h"

class Collectable : public Object{
    //VARIABLES
 private:
     //variables to rate and move up and down
     float rotSpeed;

    //FUNCTIONS
public:
    //constructor
    Collectable(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    
    //tick function will check for collision
    virtual void tick(irr::f32 deltaTime);
    
protected:
    //pure virtual function which gets called when the player player collides
    virtual void activate() = 0;
};

#endif	/* COLLLECTABLE_H */

