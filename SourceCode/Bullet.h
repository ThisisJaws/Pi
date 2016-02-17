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
	//The type ID of the target
	int targetTypeID;
    
    //how long the bullet is 'alive' for before despawning
    float currentLifeTime;
    float maxLifeTime;
    
    //when fired a direction is given and stored
    irr::core::vector3df direction;
    
    //bellow variables are for constructing the bullet later
    irr::scene::ISceneManager *sceneMRef;
    
    //FUNCTIONS
public:
    //constructor
    Bullet(irr::scene::ISceneManager *sceneManagerReference);
    //destructor
    virtual ~Bullet();
    
    void tick(irr::f32 deltatime) override;
    
    //call to fire the bullet
    void fire(const irr::core::vector3df &firePos, const irr::core::vector3df &direction, const float &shipSpeed, const int &targetTypeID);
};

#endif	/* BULLET_H */

