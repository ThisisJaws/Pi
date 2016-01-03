#ifndef ICEWORLD_H
#define ICEWORLD_H

#include "World.h"

class IceWorld : public World{
	//FUNCTIONS
public:
	//constructor
	IceWorld(PlayerShip *player);

	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

protected:
	virtual void loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Ammo(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
};

#endif // !ICEWORLD_H
