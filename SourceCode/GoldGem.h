#ifndef GOLDGEM_H
#define GOLDEM_H

#include "Gem.h"

class GoldGem : public Gem{
public:
	//Just changes the constructor
	GoldGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference);
};

#endif 