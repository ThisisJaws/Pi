/* 
 * This is the class for the bullets the ships will fire
 */

#ifndef BULLET_H
#define	BULLET_H

#include "Object.h"

#include <iostream>

class Bullet : public Object{
    //VARIABLES
private:
    //move speed of the bullet
    float moveSpeed;
    //check if it has been fired
    bool fired;
    
    //bellow variables are for if the object wasnt spawned on construct
    irr::scene::ISceneManager *sceneMRef;
    irr::video::IVideoDriver *drvrRef;
    
    //FUNCTIONS
public:
    //constructor
    Bullet(irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
    //destructor
    ~Bullet();
    
    //override
    void tick(float deltatime);
    
    //call to fire the bullet
    void fire(irr::core::vector3df firePos);
};

#endif	/* BULLET_H */

