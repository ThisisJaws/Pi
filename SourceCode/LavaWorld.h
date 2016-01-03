#ifndef LAVAWORLD_H
#define	LAVAWORLD_H

#include "World.h"

class LavaWorld : public World{
	//VARIABLES
private:
	//Holds the lava (see loadPhase1 in .cpp)
	irr::scene::ITerrainSceneNode *terrainLava;

	//FUNCTIONS
public:
	//constructor
	LavaWorld(PlayerShip *player);

	//Override to load in the lava as well
	virtual void loadPhase1(irr::IrrlichtDevice *device) override;

protected:
	//Function to load in all the rocks for phase 1, takes the start position as point of reference
	virtual void loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
	virtual void loadPhase1Ammo(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
};


#endif // ! LAVAWORLD_H
