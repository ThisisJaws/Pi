#include "StaticObject.h"

#include "Game.h"

StaticObject::StaticObject(const irr::core::vector3df &spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, bool rotate, bool checkForCollision)
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, spawnPosition, TYPE_STATIC_OBJECT){

	srand(spawnPosition.Z + spawnPosition.Y);
    //Set up the rotation variables
	this->rotate = rotate;
	if(rotate){
		rotSpeed = (float)(rand() % 200 + 1);
		//make the x y z 0 - 3 the multiply by the speed
		rotAxis = irr::core::vector3df((float)rand() / (RAND_MAX) * rotSpeed, (float)rand() / (RAND_MAX)* rotSpeed, (float)rand() / (RAND_MAX)* rotSpeed);
	}

	//Change to undefined type to stop collision checks
	if(!checkForCollision){
		typeID = TYPE_UNDEFINED_TYPE;
	}
}

void StaticObject::tick(irr::f32 deltaTime){
	Object::tick(deltaTime);
    if(rotate){
		//Rotate the object around random axis
		updateRotation(rotAxis * deltaTime);
    }

    //If this object is behind the player then delete it
    if(Game::checkBehidPlayer(getSceneNode()->getTransformedBoundingBox().MaxEdge.Z + 20)){
        //Quick fix for portals -- CHANGE
		if(typeID != 0){
			markForDelete();
		}
    }
}
