#ifndef BRONZEGEM_H
#define BRONZEGEM_H

#include "Gem.h"

class BronzeGem : public Gem{
public:
	//Just changes the constructor
	BronzeGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference);
};

#endif 