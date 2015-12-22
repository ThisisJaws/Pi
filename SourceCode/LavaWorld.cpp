#include "LavaWorld.h"

#include "Game.h"
LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player){

}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//Load in the mesh
	worldNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh("Assets/PlaceHolders/Levels/LavaWLandLong.obj"));
	worldNode->setMaterialTexture(0, driver->getTexture("Assets/PlaceHolders/Levels/mountain.png"));
	worldNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	worldNode->setRotation(irr::core::vector3df(0, 180, 0));


	//Spawn in the asteroids/collectables
	/*int x = 0, y = 0, z = 500;
	int colChanceA;
	int colChanceB;
	for(int i = 0; i < 40; i++){
		colChanceA = rand() % 5 + 1;
		colChanceB = rand() % 2 + 1;
		if(colChanceA == 1){
			if(colChanceB == 1){
				Ammo *ap = new Ammo(irr::core::vector3df(x, y, z), smgr, driver);
				Game::addObjectToUpdate(ap);
			} else{
				Gem *gp = new Gem(irr::core::vector3df(x, y, z), smgr, driver);
				Game::addObjectToUpdate(gp);
			}
		} else{
			StaticObject *rock = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", smgr, driver);
			Game::addObjectToUpdate(rock);
		}

		y = rand() % 30 + 1;
		y -= 10;

		x = rand() % 40 + 1;
		x -= 20;

		z += 100;
	}*/

	phase1Loaded = true;
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice *device){
	//Unload the node from the scene
	if(worldNode){
		worldNode->remove();
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
