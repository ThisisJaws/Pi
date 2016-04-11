#include "Bullet.h"

#include "Game.h"

//pass everythig through the constructor
Bullet::Bullet(irr::scene::ISceneManager *sceneManagerReference) 
    : Object("Assets/Ships/LaserBullet1.obj", "Assets/Ships/LaserBulletTex.jpg", sceneManagerReference, irr::core::vector3df(0), TYPE_BULLET){
    
    fired = false;
    moveSpeed = 250.0f;
    
    currentLifeTime = 0;
    maxLifeTime = 1.3f;
    
    //store the variables so it can be spawned later
    sceneMRef = sceneManagerReference;
}

Bullet::~Bullet(){
    //clear the pointers reference (will get properly deleted elsewhere)
    sceneMRef = 0;
}

void Bullet::tick(irr::f32 deltaTime){
	Object::tick(deltaTime);
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

void Bullet::fire(const irr::core::vector3df &firePos, const irr::core::vector3df &direction, const float &shipSpeed, const int &targetTypeID){
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

    //Scale the bullets up a little bit
    getSceneNode()->setScale(irr::core::vector3df(3, 3, 3));
	//Rotate them properly
	if(direction.Z == 1){
		changeRotation(irr::core::vector3df(0, 180, 0));
	}
    
    //set the direction
    this->direction = direction;
    
    //set the position
    changePosition(firePos);
    
    //bullet has now been fired
    fired = true;
}