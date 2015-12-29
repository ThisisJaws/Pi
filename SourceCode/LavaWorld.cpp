#include "LavaWorld.h"

#include "Game.h"
LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player){

}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//load in the terrain
	terrain = loadTerrain(device,
						  "Assets/Environment/Levels/LavaWorldHeightMapLand.jpg",
						  driver->getTexture("Assets/PlaceHolders/Levels/mountain.png"),
						  irr::core::vector3df(10, 2, 10));

	//This level requires two types of terrains so any extra one has to be loaded in 
	terrainLava = loadTerrain(device,
							  "Assets/Environment/Levels/LavaWorldHeightMapLava.jpg",
							  driver->getTexture("Assets/PlaceHolders/Levels/lava.jpg"),
							  irr::core::vector3df(10, 2, 10),
							  irr::core::vector3df(0, 70, 0));
	
	//Set the player position to the phase start position
	player->changePosition(irr::core::vector3df(5275, 190, -500));

	//Phase is now loaded
	phase1Loaded = true;
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice *device){
	//Unload the node from the scene
	if(terrain){
		terrain->remove();
		terrainLava->remove();
	}

	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//array of Enemies - these get deleted once they move off screen
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

void LavaWorld::reset(){
	//Call the super function
	World::reset();
	//Make sure the lava terrain also gets removed
	terrainLava->remove();
}
