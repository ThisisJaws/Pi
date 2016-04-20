#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player,  "Assets/LevelAssets/LevelMaps/IceWorld.stm", "Assets/SkyDomes/IceSkydome_small.jpg"){
}

void IceWorld::loadPhase1(irr::IrrlichtDevice *device){
	World::loadPhase1(device);

	//Set up the snow particles
	snowParticleSystem = device->getSceneManager()->addParticleSystemSceneNode(false);
	irr::scene::IParticleEmitter* em = snowParticleSystem->createBoxEmitter(irr::core::aabbox3df(500, -100, -200, 700, 800, 20000), 
																			irr::core::vector3df(-0.25, -0.1f, 0), 
																			1000U, 1500U, 
																			irr::video::SColor(255, 255, 255, 255), 
																			irr::video::SColor(255, 255, 255, 255),
																			4000U, 6000U, 0, 
																			irr::core::dimension2df(5, 5), 
																			irr::core::dimension2df(15, 15));
	snowParticleSystem->setEmitter(em);
	em->drop();
	snowParticleSystem->setPosition(irr::core::vector3df(0, 0, 100));
	snowParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	snowParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	snowParticleSystem->setMaterialTexture(0, device->getSceneManager()->getVideoDriver()->getTexture("Assets/Particles/rsz_snow.png"));
	snowParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
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
		z += 1500 + (player->getMovementSpeed() * 2.7f);
	}

	//Add some gems to the level
	x = 0; y = 0; z = 1200;
	for(int i = 0; i < 3; i++){
		y = (irr::f32)(rand() % 40 + 1) - 20;
		BronzeGem *gem = new BronzeGem(irr::core::vector3df(x, y, z), smgr);
		gem->moveAwayFromPlayer(true, Game::getCurrentPlayer()->getMovementSpeed());
		z += (rand() % 3000 + 1000) + (player->getMovementSpeed() * 2.7f);
	}

	//Add some asteroids to the level
	x = 0; y = 0; z = 2000;
	for(int i = 0; i < 14; i++){
		y = (irr::f32)(rand() % 70 + 1) - 35;
		StaticObject *Obsticle = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", device->getSceneManager(), true);
		Obsticle->moveAwayFromPlayer(true, Game::getCurrentPlayer()->getMovementSpeed());
		z += (rand() % 500 + 500) + (player->getMovementSpeed() * 2.7f);
	}

	phase2Loaded = true;
}

void IceWorld::clearTerrains(){
	World::clearTerrains();

	//Clear the particle system
	if(snowParticleSystem){
		snowParticleSystem->remove();
	}
}
