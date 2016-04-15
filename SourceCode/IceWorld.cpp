#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player,  "Assets/LevelAssets/LevelMaps/IceWorld.stm", "Assets/SkyDomes/IceSkydome_small.jpg"){
}

void IceWorld::loadPhase2(irr::IrrlichtDevice * device){
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

	//Make an array for the spawn order
	int spawnOrder[10] = {1, 1, 2, 1, 2, 3, 1, 1, 3, 2};

	//Set up the enemy positions
	irr::f32 x = 0; irr::f32 y = 0; irr::f32 z = 500;
	for(int i = 0; i < 20; i++){
		//Deside which enemy to place
		if(spawnOrder[i] == 1){
			BasicEnemy *basicEnemy = new BasicEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr);
		} else if(spawnOrder[i] == 2){
			FastEnemy *fastEnemy = new FastEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr);
		} else if(spawnOrder[i] == 3){
			StrongEnemy *strongEnemy = new StrongEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr);
		}
		z += 1500;
	}

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	for(int i = 0; i < 3; i++){
		y = (irr::f32)(rand() % 40 + 1) - 20;
		BronzeGem *gem = new BronzeGem(irr::core::vector3df(x, y, z), smgr);
		z += rand() % 3000 + 1000;
	}

	//Add some asteroids to the level
	x = 0; y = 0; z = 2000;
	for(int i = 0; i < 16; i++){
		y = (irr::f32)(rand() % 70 + 1) - 35;
		StaticObject *Obsticle = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", device->getSceneManager(), true);
		z += rand() % 500 + 500;
	}

	phase2Loaded = true;
}
