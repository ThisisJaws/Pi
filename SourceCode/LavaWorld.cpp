#include "LavaWorld.h"

#include "Game.h"
LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player){

}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//load in the terrain
	terrain = loadTerrain(device,
						  "Assets/Environment/Levels/LavaWorldHeightMapLand.jpg",
						  driver->getTexture("Assets/PlaceHolders/Levels/mountain.png"),
						  irr::core::vector3df(-1477.0f, -165, 250),
						  irr::core::vector3df(6.0f, 2, 6.0f));

	////This level requires two types of terrains so any extra one has to be loaded in 
	//terrainLava = loadTerrain(device,
	//						  "Assets/Environment/Levels/LavaWorldHeightMapLava.jpg",
	//						  driver->getTexture("Assets/PlaceHolders/Levels/lava.jpg"),
	//						  irr::core::vector3df(-1477.0f, -165, 250),
	//						  irr::core::vector3df(6.0f, 2, 6.0f));

	phase1Loaded = true;
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice *device){
	//Unload the node from the scene
	if(terrain){
		terrain->remove();
	}

	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//array of Enemies
	int x = 0; int y = 0; int z = 500;
	for(int i = 0; i < 2; i++){
		//basic
		BasicEnemy *basicEnemy = new BasicEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, driver);
		Game::addObjectToUpdate(basicEnemy);

		z += 1200;

		//strong
		StrongEnemy *strongEnemy = new StrongEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, driver);
		Game::addObjectToUpdate(strongEnemy);

		z += 2800;

		//fast
		FastEnemy *fastEnemy = new FastEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, driver);
		Game::addObjectToUpdate(fastEnemy);

		z += 800;
	}

	phase2Loaded = true;
}
