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

#define HEIGHT_MAP_COUNT 5		//How many inividual height maps there are
#define TERRAIN_NODE_COUNT 10	//How many segments to lay out for each level

class World{
	//VARIABLES
protected:
	//Reference to the player
	PlayerShip *player;

	//An array that holds the locations of the heightmap pieces
	irr::io::path heightMapLocations[HEIGHT_MAP_COUNT];

	//An array of the scene nodes that will make up the entire terrain
	irr::scene::ITerrainSceneNode *terrainNodes[TERRAIN_NODE_COUNT];

	//The path to the texture
	irr::io::path terrainTexturePath;

	//The start position of the player for phase 1
	irr::core::vector3df phase1StartPosition;

private:
	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

	//Keep track of what has been completed
	bool phase1Complete;
	bool phase2Complete;

	//FUNCTIONS
public:
	//constructor
	World(PlayerShip *player);

	/** abstract functions to load the levels
		Takes the device to load everything into the scene*/
	virtual void loadPhase1(irr::IrrlichtDevice *device);
	virtual void loadPhase2(irr::IrrlichtDevice *device);

	//Check if each phase is loaded
	bool isPhase1Loaded();
	bool isPhase2Loaded();

	//Check if the phase is complete
	bool isPhase1Complete();
	bool isPhase2Complete();

	//Loops through the array of terrain nodes and deletes them
	virtual void clearTerrains();

	//Resets the world
	void reset();

protected:
	//Takes a height map and returns the loaded terrain
	irr::scene::ITerrainSceneNode* loadTerrain(irr::IrrlichtDevice *device, const irr::io::path &heightMapFileLocation, irr::video::ITexture *texture, irr::core::vector3df position = irr::core::vector3df(0), irr::core::vector3df &scaleFactor = irr::core::vector3df(1), irr::s32 smoothFactor = 1, float tileAmount = 20.0f);

	//Derived classes will override these to place objects
	virtual void loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
	virtual void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
	virtual void loadPhase1Ammo(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
};

#endif /* WORLD_H */
