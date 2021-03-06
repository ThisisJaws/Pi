/*
 * This is the base class for all ships ie. player and enemies
 * this class will contain all shared functionality
 */

#ifndef _SHIP_H
#define	_SHIP_H

#include <vector>

#include "Object.h"
#include "Bullet.h"
#include "SFML/Audio.hpp"

class Ship : public Object{
    //VARIABLES
protected:
    //how fast the ship can move
    float moveSpeed;
    //how quickly the ship will move up/down/left/right
    float turnSpeed;
    //the direction to move in (will be +1 or -1)
    signed char moveDir;

	//The maximum amount the ship can rotate
	float maxZRotate;
	float maxXRotate;
	//How fast the ship will rotate
	float rotSpeed;
	//Keep track of the ship if it needs to rotate back
	bool rotateBackX;
	bool rotateBackY;

	//The cannon positions for each ship to set
	std::vector<irr::core::vector3df> cannonPositions;

	//Particle system scene node
	irr::scene::IParticleSystemSceneNode *engineParticleSystem;

	//Sound effects
	static sf::SoundBuffer *shootBuff;
	sf::Sound shootSFX;
	static sf::SoundBuffer *damageBuff;
	sf::Sound damageSFX;
	//This static counter lets the program know when to free the above pointers
	static int bufferCount;

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

	//The lives this ship has - or how many hits it can take
	unsigned short lives;

    //FUNCTIONS
public:
    //constructor
    Ship(const irr::core::vector3df &spawnPosition, const float &movementSpeed, const int &firingSpeed, const int &movementDirection, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, const irr::s32 &objectTypeID, const unsigned short &startingLives = 0);
    //destructor
    virtual ~Ship();

    //checks the cool down on shooting
    virtual void tick(irr::f32 deltaTime) override;

	//Returns the movement speed
	float getMovementSpeed();

	//Returns the amount of lives
	unsigned short getLives();

	//Increment the ship's lives
	void increaseLives(const unsigned short &amount = 1);

	//Call to deal 'damage'
	virtual void dealDamage(const unsigned short &amount = 1);

protected:
    //makes the ship shoot, returns true if it fired
    virtual bool shoot(const irr::core::vector3df &direction, const int &targetTypeID, const std::vector<irr::core::vector3df> &firingPositions);

    //moves the ship forward
    void move(const float &speed, const irr::f32 &deltaTime);
	//Moves the ship up or down
	virtual void moveVertical(const float &speed, const float &force, const irr::f32 &deltaTime);
	virtual void moveHorizontal(const float &speed, const float &force, const irr::f32 &deltaTime);
};

#endif	/* _SHIP_H */

