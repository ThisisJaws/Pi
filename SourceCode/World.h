#ifndef WORLD_H
#define WORLD_H

/* This class is the base class for each world (phase 1 & phase 2) */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "irrlicht.h"

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

private:
	//The light that will act as a sun
	irr::scene::ILightSceneNode *sun;

	//String to the level data
	std::string levelLocation;

	//Vector of the all the terrain segments to tell when the player has beaten the level
	std::vector<StaticObject*> terrainSegments;

	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

	//Keep track of what has been completed
	bool phase1Complete;
	bool phase2Complete;

	//Structured used for sorting vectors
	struct less_than_key{
		inline bool operator() (StaticObject *obj1, StaticObject *obj2){
			return (obj1->getPosition().Z < obj2->getPosition().Z);
		}
	};

	//FUNCTIONS
public:
	//constructor
<<<<<<< HEAD
	World(PlayerShip *player, const int &sceneNodesToSpawn, const irr::core::vector3df &phase1StartPos, const irr::core::vector3df &worldScale);
=======
	World(PlayerShip *player, const std::string &levelLocation);
>>>>>>> WindowsBuild

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
<<<<<<< HEAD
	//Takes a height map and returns the loaded terrain
	irr::scene::ITerrainSceneNode* loadTerrain(irr::IrrlichtDevice *device, const irr::io::path &heightMapFileLocation, irr::video::ITexture *texture, const irr::core::vector3df &position = irr::core::vector3df(0), const irr::core::vector3df &scaleFactor = irr::core::vector3df(1), const irr::s32 &smoothFactor = 1, const float &tileAmount = 3.0f);

	//Derived classes will override these to place objects
	virtual void loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
	virtual void loadPhase1Gems(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
	virtual void loadPhase1Ammo(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver) = 0;
=======
	//Loads in the map file for the level
	void loadMapFile(const std::string &mapFile, irr::IrrlichtDevice *device);
>>>>>>> WindowsBuild
};

#endif /* WORLD_H */
