#ifndef WORLD_H
#define WORLD_H

/* This class is the base class for each world (phase 1 & phase 2) */

#include <list>

#include "Irrlicht.h"

#include "EnemyTypes.h"
#include "PlayerShip.h"
#include "StaticObject.h"
#include "Ammo.h"
#include "Gem.h"

class World{
	//VARIABLES
protected:
	//Reference to the player
	PlayerShip *player;

	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

	//keep a reference of all the ships to check for phase completion
	std::list<Object*> shipReferences;

private:
	//Position in which the player has 'passed' the first stage
	float phase1WinPosition;

	//FUNCTIONS
public:
	//constructor
	World(PlayerShip *player, float phase1WinPosition);

	/** abstract functions to load the levels
		Takes the device to load everything into the scene
		Takes the static list to load everything into the list
		*/
	virtual void loadPhase1(irr::IrrlichtDevice *device, std::list<Object*> *objectUpdateList) = 0;
	virtual void loadPhase2(irr::IrrlichtDevice *device, std::list<Object*> *objectUpdateList) = 0;

	//Check if each phase is loaded
	bool isPhase1Loaded();
	bool isPhase2Loaded();

	//Check if the phase is complete
	bool isPhase1Complete();
	bool isPhase2Complete();
};

#endif /* WORLD_H */
