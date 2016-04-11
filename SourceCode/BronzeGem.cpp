#include "BronzeGem.h"

BronzeGem::BronzeGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager * sceneManagerReference)
		: Gem(spawnPosition, 10000, "Assets/Collectables/SpaceGem_Bronze.jpg", sceneManagerReference){
	//Everything has been passed through
}
