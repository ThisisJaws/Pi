#ifndef LAVAWORLD_H
#define	LAVAWORLD_H

#include "World.h"

class LavaWorld : public World{
	//FUNCTIONS
public:
	//constructor
	LavaWorld(PlayerShip *player);

	virtual void loadPhase1(irr::IrrlichtDevice *device) override;
	virtual void loadPhase2(irr::IrrlichtDevice *device) override;
};


#endif // ! LAVAWORLD_H
