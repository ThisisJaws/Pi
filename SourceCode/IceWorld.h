#ifndef ICEWORLD_H
#define ICEWORLD_H

#include "World.h"

class IceWorld : public World{
	//FUNCTIONS
public:
	//constructor
	IceWorld(PlayerShip *player);

	//Override phase 2
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;

};

#endif // !ICEWORLD_H
