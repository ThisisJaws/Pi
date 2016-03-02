#include "LavaPlume.h"

LavaPlume::LavaPlume(const irr::core::vector3df &spawnPosition, irr::scene::ISceneManager *sceneManagerReference)
	: StaticObject(spawnPosition, "Assets/LevelAssets/O_LavaWorldPlume_a.obj", "Assets/LevelAssets/O_LavaWorldPlume.jpg", sceneManagerReference, false){

	//Set the max height to move down from
	maxHeight = spawnPosition.Y;

	//Set the minimun position to move up from
	minHeight = -220;

	//Set the movespeed of the plume
	srand(1);
	moveSpeed = (float)(rand() % 100 + 100);

	//Set the waitOneTick variable
	waitOneTick = false;
}

void LavaPlume::tick(irr::f32 deltaTime){
	StaticObject::tick(deltaTime);

	//Move the plumes
	updatePosition(0, moveSpeed * deltaTime, 0);

	//Check if the plume needs to waitOneTick - will prevent the plume from getting stuck
	if(!waitOneTick){
		//Make sure the plume doesn't go too high or too low
		if(getPosition().Y >= maxHeight || getPosition().Y <= minHeight){
			moveSpeed *= -1;
			waitOneTick = true;
		}
	} else{
		waitOneTick = false;
	}
}
