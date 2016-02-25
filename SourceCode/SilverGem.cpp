#include "SilverGem.h"

SilverGem::SilverGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager * sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
	: Gem(spawnPosition, 20000, "Assets/Collectables/SpaceGem_Silver.jpg", sceneManagerReference, audiereDevice){
	//Everything has been passed through
}
