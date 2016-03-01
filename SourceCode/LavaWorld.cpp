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
	for(int i = 0; i < 10; i++){
		//basic
		int spawnNum = rand() % 100 + 1;
		if(spawnNum <= 45){
			BasicEnemy *basicEnemy = new BasicEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
			Game::addObjectToUpdate(basicEnemy);
		} else if(spawnNum <= 75){
			//fast
			FastEnemy *fastEnemy = new FastEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
			Game::addObjectToUpdate(fastEnemy);
		} else if(spawnNum <= 100){
			//strong
			StrongEnemy *strongEnemy = new StrongEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, audDevice);
			Game::addObjectToUpdate(strongEnemy);
		}
		z += 1500;
	}

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	for(int i = 0; i < 3; i++){
		y = (rand() % 40 + 1) - 20;
		BronzeGem *gem = new BronzeGem(irr::core::vector3df(x, y, z), smgr, audDevice);
		Game::addObjectToUpdate(gem);
		z += rand() % 3000 + 1000;
	}

	phase2Loaded = true;
}
