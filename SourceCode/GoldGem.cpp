#include "GoldGem.h"

GoldGem::GoldGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager * sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
	: Gem(spawnPosition, 100000, "Assets/Collectables/SpaceGem_Gold.jpg", sceneManagerReference, audiereDevice){
	//Everything has been passed through
}