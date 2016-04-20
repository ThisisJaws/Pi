#ifndef ICEWORLD_H
#define ICEWORLD_H

#include "World.h"

class IceWorld : public World{
	//VARIABLES
private:
	//Snow particles
	irr::scene::IParticleSystemSceneNode *snowParticleSystem;

	//FUNCTIONS
public:
	//constructor
	IceWorld(PlayerShip *player);

	//Override to load in particles
	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	//Override phase 2
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

	//Override to reset the particles
	virtual void clearTerrains() override;
};

#endif // !ICEWORLD_H
