#ifndef JUNGLEWORLD_H
#define JUNGLEWORLD_H

#include "World.h"

class JungleWorld : public World{
	//VARIABLES

	//FUNCTIONS
public:
	//constructor
	JungleWorld(PlayerShip *player);

	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

};

 #endif //JUNGLEWORLD_H