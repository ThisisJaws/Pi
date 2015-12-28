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
};


#endif // ! LAVAWORLD_H
