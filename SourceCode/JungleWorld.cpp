#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player){

	phase1StartPosition = irr::core::vector3df(4920, 190, -500);
}

void JungleWorld::loadPhase2(irr::IrrlichtDevice * device){
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

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	Gem *gem;
	for(int i = 0; i < 3; i++){
		y = rand() % 20 + 1;
		y -= 10;
		gem = new Gem(irr::core::vector3df(x, y, z), smgr, driver);

		z += rand() % 3000 + 100;
	}

	phase2Loaded = true;
}

void IceWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}
