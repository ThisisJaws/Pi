/* 
 * This is the class for the bullets the ships will fire
 */

#ifndef BULLET_H
#define	BULLET_H

#include "Object.h"

class Bullet : public Object{
    //VARIABLES
private:
    float moveSpeed;
    bool fired;
    
    //FUNCTIONS
public:
    //constructor
    Bullet(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    
    //override
    void tick(float deltatime);
    
    //call to fire the bullet
    void fire(irr::core::vector3df firePos);
};

#endif	/* BULLET_H */

