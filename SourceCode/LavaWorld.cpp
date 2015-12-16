#include "LavaWorld.h"

LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player, 4500){

}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device, std::list<Object*> *objectUpdateList){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	
	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//Spawn in the asteroids/collectables
	int x = 0, y = 0, z = 500;
	int colChanceA;
	int colChanceB;
	for(int i = 0; i < 40; i++){
		colChanceA = rand() % 5 + 1;
		colChanceB = rand() % 2 + 1;
		if(colChanceA == 1){
			if(colChanceB == 1){
				Ammo *ap = new Ammo(irr::core::vector3df(x, y, z), smgr, driver);
				objectUpdateList->push_back(ap);
			} else{
				Gem *gp = new Gem(irr::core::vector3df(x, y, z), smgr, driver);
				objectUpdateList->push_back(gp);
			}
		} else{
			StaticObject *rock = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", smgr, driver);
			objectUpdateList->push_back(rock);
		}

		y = rand() % 30 + 1;
		y -= 10;

		x = rand() % 40 + 1;
		x -= 20;

		z += 100;
	}

	phase1Loaded = true;
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice *device, std::list<Object*> *objectUpdateList){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	
	//array of Enemies
	int x = 0; int y = 0; int z = 500;
	for(int i = 0; i < 3; i++){
		//basic
		BasicEnemy *basicEnemy = new BasicEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, driver);
		objectUpdateList->push_back(basicEnemy);
		shipReferences.push_back(basicEnemy);

		z += 400;

		//strong
		StrongEnemy *strongEnemy = new StrongEnemy(player, irr::core::vector3df(x, y, z), device->getTimer(), smgr, driver);
		objectUpdateList->push_back(strongEnemy);
		shipReferences.push_back(strongEnemy);

		z += 400;
	}

	phase2Loaded = true;
}
