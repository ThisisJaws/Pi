#include "LavaPlume.h"

LavaPlume::LavaPlume(const irr::core::vector3df &spawnPosition, irr::scene::ISceneManager *sceneManagerReference)
	: StaticObject(spawnPosition, "Assets/LevelAssets/O_LavaWorldPlume_a.obj", "Assets/LevelAssets/O_LavaWorldPlume.jpg", sceneManagerReference, false){

	//Set the max height to move down from
	maxHeight = spawnPosition.Y;

	//Set the minimun position to move up from
	minHeight = -10;
}

void LavaPlume::tick(irr::f32 deltaTime){
	StaticObject::tick(deltaTime);

}
