#include "Bullet.h"

#include "Game.h"

//pass everythig through the constructor
Bullet::Bullet(irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference) 
    : Object("Assets/PlaceHolders/LaserBulletSix.obj", "", sceneManagerReference, driverReference, false, irr::core::vector3df(0), TYPE_BULLET){
    
    fired = false;
    moveSpeed = 250.0f;
    
    currentLifeTime = 0;
    maxLifeTime = 2.0f;
    
    //store the variables so it can be spawned later
    sceneMRef = sceneManagerReference;
    drvrRef = driverReference;
}

Bullet::~Bullet(){
    //clear the pointers reference (will get properly deleted elsewhere)
    sceneMRef = 0;
    drvrRef = 0;
}

void Bullet::tick(irr::f32 deltaTime){
    if(fired){
        //move the bullet forward
        updatePosition(direction * (moveSpeed * deltaTime));
        
        //update lifetime
        currentLifeTime += deltaTime;
        
        if(currentLifeTime >= maxLifeTime){
            markForDelete();
        }
        
        //Check the type of collision
		irr::s32 collidedObjectUniqueID = checkCollision(-1);
		if(collidedObjectUniqueID > 1){
			Object *collidedObject = Game::getObjectReferenceByID(collidedObjectUniqueID);
			if(collidedObject != NULL && collidedObject->getTypeID() == targetTypeID){
				//If the bullet hits it target, then damage it
				Ship *collidedShip = dynamic_cast<Ship *>(collidedObject);
				collidedShip->dealDamage();

				//Delete the bullet after it collides
				markForDelete();
			}
		}
    }
}

void Bullet::fire(irr::core::vector3df firePos, irr::core::vector3df direction, float shipSpeed, int targetTypeID){
    //spawn the object into the scene
    spawnObject("Assets/PlaceHolders/LaserBulletSix.obj", "Assets/PlaceHolders/Laser_bullet_purple.bmp", sceneMRef, drvrRef);
    
	this->targetTypeID = targetTypeID;
	
	//Work out the speed of the bullet
	moveSpeed = shipSpeed;
	if(direction.Z > 0){
		//Increase the forward speed by a consistent amount
		moveSpeed += 100;
	} else{
		//Increase the backwards speed by a percentage amount
		float onePercent = moveSpeed / 100;
		int percentDecrease = 150;
		moveSpeed -= onePercent * percentDecrease;
	}

    //temp - set scale of bullet and rotation
    getSceneNode()->setScale(irr::core::vector3df(10, 10, 10));
    getSceneNode()->setRotation(irr::core::vector3df(0, 90, 0));
    
    //set the direction
    this->direction = direction;
    
    //set the position
    changePosition(firePos);
    
    //bullet has now been fired
    fired = true;
}