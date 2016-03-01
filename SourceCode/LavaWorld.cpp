#include "LavaWorld.h"

#include "Game.h"

LavaWorld::LavaWorld(PlayerShip *player)
	: World(player, "Assets/LevelAssets/LevelMaps/LavaWorld.stm", "Assets/SkyDomes/LavaSkydome_small.jpg"){
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice * device, audiere::AudioDevicePtr audDevice){
	//Unload the terrains from the scene
	clearTerrains();

	//Make sure the previous phase is no longer considered loaded
	phase1Loaded = false;

	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//array of Enemies - these get deleted once they move off screen
	irr::f32 x = 0; irr::f32 y = 0; irr::f32 z = 500;
	for(int i = 0; i < 2; i++){
		//basic
		BasicEnemy *basicEnemy = new BasicEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
		Game::addObjectToUpdate(basicEnemy);

		z += 1200;

		//strong
		StrongEnemy *strongEnemy = new StrongEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
		Game::addObjectToUpdate(strongEnemy);

		z += 2800;

		//fast
		FastEnemy *fastEnemy = new FastEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
		Game::addObjectToUpdate(fastEnemy);

		z += 800;
	}

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	//Gem *gem;
	for(int i = 0; i < 3; i++){
		y = rand() % 20 + 1;
		y -= 10;
		//gem = new Gem(irr::core::vector3df(x, y, z), "Assets/Collectables/SpaceGem_Bronze.jpg", smgr, audDevice);

		//Game::addObjectToUpdate(gem);

		z += rand() % 3000 + 100;
	}

	phase2Loaded = true;
}
