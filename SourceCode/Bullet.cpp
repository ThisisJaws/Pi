#include "Bullet.h"

#include "Game.h"

//pass everythig through the constructor
Bullet::Bullet(irr::scene::ISceneManager *sceneManagerReference) 
    : Object("Assets/Ships/LaserBullet1.obj", "Assets/Ships/LaserBulletTex.jpg", sceneManagerReference, irr::core::vector3df(0), TYPE_BULLET){
    
    fired = false;
    moveSpeed = 250.0f;
    
	travelDistance = 140;
    
    //store the variables so it can be spawned later
    sceneMRef = sceneManagerReference;

	//Always lit
	getSceneNode()->setMaterialFlag(irr::video::EMF_LIGHTING, false);
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
        
		//Update the distance
		startPosition += direction * (shipSpeed * deltaTime);
		currentDistance = startPosition.getDistanceFrom(getPosition());

		//Check the distance
        if(currentDistance >= travelDistance){
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
		//Decrease the movespeed (100 is what percentage of movespeed)
		float percent = (100 / moveSpeed) * 100;
		moveSpeed -= 100 - (percent / 2);
	}

    //Scale the bullets up a little bit
    getSceneNode()->setScale(irr::core::vector3df(3, 3, 3));
	//Rotate them properly
	if(direction.Z == 1){
		changeRotation(irr::core::vector3df(0, 180, 0));
	}
    
    //Set the direction
    this->direction = irr::core::vector3df(0, 0, 1);
    
    //set the position
    changePosition(firePos);

	//Set the start variables for checking distance
	startPosition = firePos;

	//Remeber the ship's speed
	this->shipSpeed = shipSpeed;
    
    //bullet has now been fired
    fired = true;
}