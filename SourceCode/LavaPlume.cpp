#include "LavaPlume.h"

LavaPlume::LavaPlume(const irr::core::vector3df &spawnPosition, irr::scene::ISceneManager *sceneManagerReference)
	: StaticObject(spawnPosition, "Assets/LevelAssets/O_LavaWorldPlume_a.obj", "Assets/LevelAssets/O_LavaWorldPlume.jpg", sceneManagerReference, true){

	//Set the max height to move down from
	maxHeight = spawnPosition.Y + 40;

	//Set the minimun position to move up from
	minHeight = -220;

	//Set the movespeed of the plume
	srand(spawnPosition.X + spawnPosition.Y + spawnPosition.Z);
	moveSpeed = ((float)rand() / (RAND_MAX) + 1); // 1 < r < 2
	currentSpeed = moveSpeed;
}

void LavaPlume::tick(irr::f32 deltaTime){
	StaticObject::tick(deltaTime);

	//Move the plumes 50% of the distance to the target
	updatePosition(0, ((maxHeight - getPosition().Y)) * currentSpeed * deltaTime, 0);

	//Make sure the plume doesn't go too high or too low
	if(getPosition().Y >= maxHeight - 20){
		currentSpeed = -moveSpeed;	//using negative movespeed so it slowly mvoes away from the target
	} else if(getPosition().Y <= minHeight + 20){
		currentSpeed =  moveSpeed;
	}
}
