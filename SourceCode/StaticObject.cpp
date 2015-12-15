#include "StaticObject.h"

StaticObject::StaticObject(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool rotate)
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, true, spawnPosition){
    
    //make sure it is the ight type
    typeID = TYPE_STATIC_OBJECT;
    
    //set up the rotation variables
	if(rotate){
		this->rotate = rotate;
		rotSpeed = rand() % 50 + 1;
		//make the x y z 0 - 3 the multiply by the speed
		rotAxis = irr::core::vector3df((rand() % 4) * rotSpeed, (rand() % 4) * rotSpeed, (rand() % 4) * rotSpeed);
	}
}

void StaticObject::tick(irr::f32 deltaTime){
    if(rotate){
		//Rotate the object around random axis
        irr::core::vector3df currentRot = getSceneNode()->getRotation();
        currentRot += rotAxis * deltaTime;
        getSceneNode()->setRotation(currentRot);
    }

	//Check if the player has collided
	Object *collidedObject = checkCollision();
	if(collidedObject != NULL){
		if(collidedObject->getTypeID() == TYPE_SHIP_PLAYER){
			collidedObject->markForDelete();
		}
	}
}