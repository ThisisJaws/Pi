#include "StaticObject.h"

#include "Game.h"

StaticObject::StaticObject(const irr::core::vector3df &spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, bool updateRotation, bool checkForCollision)
    : Object(pathOfMesh, pathOfTexture, sceneManagerReference, spawnPosition, TYPE_STATIC_OBJECT){

    //set up the rotation variables
	if(rotate){
		this->rotate = rotate;
		rotSpeed = (float)(rand() % 50 + 1);
		//make the x y z 0 - 3 the multiply by the speed
		rotAxis = irr::core::vector3df((rand() % 4) * rotSpeed, (rand() % 4) * rotSpeed, (rand() % 4) * rotSpeed);
	}

	//Remove the collision of the object
	if(!checkForCollision){
		getSceneNode()->getTriangleSelector()->drop();
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
        markForDelete();
    }
}
