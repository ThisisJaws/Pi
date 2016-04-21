#ifndef LAVAWORLD_H
#define	LAVAWORLD_H

#include "World.h"

class LavaWorld : public World{
	//VARIABLES
private:
	//Ash particles
	irr::scene::IParticleSystemSceneNode *ashParticleSystem;
	
	//FUNCTIONS
public:
	//constructor
	LavaWorld(PlayerShip *player);

	//Override to load in particles
	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	//Override phase 2
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

	//Override to reset the particles
	virtual void clearTerrains() override;
};


#endif // ! LAVAWORLD_H
