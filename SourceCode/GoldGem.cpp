#include "GoldGem.h"

GoldGem::GoldGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager * sceneManagerReference)
	: Gem(spawnPosition, 30000, "Assets/Collectables/SpaceGem_Gold.jpg", sceneManagerReference){
	//Everything has been passed through
}