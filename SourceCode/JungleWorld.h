#ifndef JUNGLEWORLD_H
#define JUNGLEWORLD_H

#include "World.h"

class JungleWorld : public World{
	//FUNCTIONS
public:
	//constructor
	JungleWorld(PlayerShip *player);

	//Override phase 2
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

};

 #endif //JUNGLEWORLD_H