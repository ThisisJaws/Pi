#include "LavaWorld.h"

#include "Game.h"

LavaWorld::LavaWorld(PlayerShip *player)
	: World(player, "Assets/LevelAssets/LevelMaps/LavaWorld.stm", "Assets/SkyDomes/LavaSkydome_small.jpg"){
}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device){
	World::loadPhase1(device);

	//Set up the snow particles
	ashParticleSystem = device->getSceneManager()->addParticleSystemSceneNode(false);
	irr::scene::IParticleEmitter* em = ashParticleSystem->createBoxEmitter(irr::core::aabbox3df(-700, 100, -200, 700, 800, 20000),
																			irr::core::vector3df(0, -0.1f, 0),
																			30U, 70U,
																			irr::video::SColor(255, 255, 255, 255),
																			irr::video::SColor(255, 255, 255, 255),
																			8000U, 8000U, 0,
																			irr::core::dimension2df(5, 5),
																			irr::core::dimension2df(15, 15));
	ashParticleSystem->setEmitter(em);
	em->drop();
	ashParticleSystem->setPosition(irr::core::vector3df(0, 0, 100));
	ashParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ashParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ashParticleSystem->setMaterialTexture(0, device->getSceneManager()->getVideoDriver()->getTexture("Assets/Particles/rsz_ash.png"));
	ashParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice * device){
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
		z += 1500 + (player->getMovementSpeed() * 2.7f);
	}

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	for(int i = 0; i < 3; i++){
		y = (irr::f32)((rand() % 40 + 1) - 20);
		BronzeGem *gem = new BronzeGem(irr::core::vector3df(x, y, z), smgr);
		gem->moveAwayFromPlayer(true, Game::getCurrentPlayer()->getMovementSpeed());
		z += (rand() % 3000 + 1000) + (player->getMovementSpeed() * 2.7f);
	}

	phase2Loaded = true;
}

void LavaWorld::clearTerrains(){
	World::clearTerrains();

	//Clear the particle system
	if(ashParticleSystem){
		ashParticleSystem->remove();
	}
}
