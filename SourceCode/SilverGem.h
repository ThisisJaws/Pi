#ifndef SILVERGEM_H
#define SILVERGEM_H

#include "Gem.h"

class SilverGem : public Gem{
public:
	//Just changes the constructor
	SilverGem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice);
};

#endif 