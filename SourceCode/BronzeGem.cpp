#include "BronzeGem.h"

BronzeGem::BronzeGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager * sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
		: Gem(spawnPosition, 10000, "Assets/Collectables/SpaceGem_Bronze.jpg", sceneManagerReference, audiereDevice){
	//Everything has been passed through
}
