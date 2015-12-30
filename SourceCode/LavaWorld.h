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

	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

	void reset() override;

private:
	//Function to load in all the rocks for phase 1, takes the start position as point of reference
	void loadPhase1Rocks(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);

	//Loads in all the gems
	void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver);
};


#endif // ! LAVAWORLD_H
