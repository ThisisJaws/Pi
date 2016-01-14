/*
 * This is the base class for all ships ie. player and enemies
 * this class will contain all shared functionality
 */

#ifndef _SHIP_H
#define	_SHIP_H

#include <list>

#include "Object.h"
#include "Bullet.h"

class Ship : public Object{
    //VARIABLES
protected:
    //how fast the ship can move
    float moveSpeed;
    //how quickly the ship will move up/down/left/right
    float turnSpeed;
    //the direction to move in (will be +1 or -1)
    signed char moveDir;

private:
    //if the ship is able to fire
    bool canFire;
    //control the time between each bullet firing
    irr::u32 timeSinceLastFire;
    irr::ITimer *timerReference;
    int timeBetweenShots;

    //the bullet the ship will fire
    Bullet *bullet;

    //needed to construct new bullets
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *drv;

	//The lives this ship has - or how many hits it can take
	unsigned short lives;

    //FUNCTIONS
public:
    //constructor
    Ship(const irr::core::vector3df &spawnPosition, const float &movementSpeed, const int &firingSpeed, const int &movementDirection, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, const irr::s32 &objectTypeID, const unsigned short &startingLives = 1, const bool &spawnOnConstruct = true);
    //destructor
    ~Ship();

    //checks the cool down on shooting
    virtual void tick(irr::f32 deltaTime) override;

	//Returns the movement speed
	float getMovementSpeed();

	//Call to deal 'damage'
	virtual void dealDamage(const unsigned short &amount = 1);

protected:
    //makes the ship shoot, returns true if it fired
    bool shoot(irr::core::vector3df direction, int targetTypeID);

    //moves the ship forward
    void move(const float &speed, const irr::f32 &deltaTime);
	//Moves the ship up or down
	virtual void moveUp(const float &speed, const irr::f32 &deltaTime);
	virtual void moveDown(const float &speed, const irr::f32 &deltaTime);
};

#endif	/* _SHIP_H */

