#include "Ship.h"
#include "Game.h"

Ship::Ship(const irr::core::vector3df &spawnPosition, const float &movementSpeed, const int &firingSpeed, const int &movementDirection, irr::ITimer *timerReference, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, const irr::s32 &objectTypeID, const unsigned short &startingLives, const bool &spawnOnConstruct)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, spawnOnConstruct, spawnPosition, objectTypeID){

    //set up variables
    moveSpeed = movementSpeed;
    turnSpeed = 75;
    //direction of movement +1 is along the positive X axis, -1 is along the negative X axis
    moveDir = movementDirection;

    //time between each bullet firing 1000 = 1 second
    timeBetweenShots = firingSpeed;
    timeSinceLastFire = 0;
    canFire = true;
    this->timerReference = timerReference;

    //reference the pointers
    smgr = sceneManagerReference;
    drv = driverReference;

	//Set the lives
	lives = startingLives;
}

Ship::~Ship(){
    //clear references (these get deleted properly elsewhere)
    smgr = 0;
    drv = 0;
    bullet = 0;
}

void Ship::tick(irr::f32 deltaTime){
    //check how long is left before the ship can fire again
    if(!canFire){
        if((timeSinceLastFire + timeBetweenShots) < timerReference->getRealTime()){
            canFire = true;
        }
    }
}

float Ship::getMovementSpeed(){
	return moveSpeed;
}

unsigned short Ship::getLives(){
	return lives;
}

void Ship::increaseLives(const unsigned short &amount){
	lives += amount;
}

void Ship::dealDamage(const unsigned short &amount){
	//If there are no lives left, mark the ship for delete
	if(lives == 0){
		markForDelete();
	}

	//Take away the amount of lives
	lives -= amount;
}

bool Ship::shoot(irr::core::vector3df direction, int targetTypeID){
    if(canFire){
        //construct a new bullet
        bullet = new Bullet(smgr, drv);

		//then fire the bullet
        bullet->fire(getPosition(), direction, moveSpeed, targetTypeID);

        //add it onto the list to be updated
        Game::addObjectToUpdate(bullet);

        //clear the pointer to prevent memory leaks
        bullet = 0;

        //stop the ship firing immediately after
        canFire = false;

        //update the time since last fire variables
        timeSinceLastFire = timerReference->getRealTime();

        //return true if the fire was successful
        return true;
    }else{
        //return false if the ship didn't shoot
        return false;
    }
}

void Ship::move(const float &speed, const irr::f32 &deltaTime){
    updatePosition(0.0f, 0.0f, speed * deltaTime);
}

void Ship::moveUp(const float &speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(0.0f, moveBy, 0.0f);
}

void Ship::moveDown(const float &speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(0.0f, -moveBy, 0.0f);
}

void Ship::turnLeft(const float & speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(-moveBy, 0.0f, 0.0f);

}

void Ship::turnRight(const float & speed, const irr::f32 &deltaTime){
	float moveBy = speed * deltaTime;
	updatePosition(moveBy, 0.0f, 0.0f);
}
