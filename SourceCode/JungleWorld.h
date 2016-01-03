#ifndef JUNGLEWORLD_H
#define JUNGLEWORLD_H

#include "World.h"

class JungleWorld : public World{
	//FUNCTIONS
public:
	//constructor
	JungleWorld(PlayerShip *player);

protected:
	virtual void loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Ammo(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
};

 #endif //JUNGLEWORLD_H