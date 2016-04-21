#ifndef JUNGLEWORLD_H
#define JUNGLEWORLD_H

#include "World.h"

class JungleWorld : public World{
	//VARIABLES
private:
	//leaf particles
	irr::scene::IParticleSystemSceneNode *leafParticleSystem;

	//FUNCTIONS
public:
	//constructor
	JungleWorld(PlayerShip *player);

	//Override to load in particles
	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	//Override phase 2
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

	//Override to reset the particles
	virtual void clearTerrains() override;

};

 #endif //JUNGLEWORLD_H