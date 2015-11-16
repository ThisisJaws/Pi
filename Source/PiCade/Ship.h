/* 
 * This is the base class for all ships ie. player and enemies
 * this class will contain all shared functionality
 */

#ifndef SHIP_H
#define	SHIP_H

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
    short moveDir;
    
private:
    //if the ship is able to fire
    bool canFire;
    //control the time between each bullet firing
    irr::u32 timeSinceLastFire;
    irr::ITimer *timerReference;
    int timeBetweenShots;
    
    //the bullets the ship will fire
    Bullet *bullet;
    std::list<Bullet*> firedBullets;
    
    //needed to construct new bullets
    irr::scene::ISceneManager *smgr;
    irr::video::IVideoDriver *drv;
    
    //FUNCTIONS
public:
    //constructor 
    Ship(float movementSpeed, int firingSpeed, int movementDirecion, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct = true);
    //destructor
    ~Ship();
    
    //override
    virtual void tick(irr::f32 deltaTime);
    
protected:
    //makes the ship shoot
    void shoot();    
};

#endif	/* SHIP_H */
