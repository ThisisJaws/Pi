#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player, "Assets/LevelAssets/LevelMaps/JungleWorld.stm", "Assets/SkyDomes/JungleSkydome_small.jpg"){
}

void JungleWorld::loadPhase1(irr::IrrlichtDevice *device){
	World::loadPhase1(device);

	//Set up the snow particles
	leafParticleSystem = device->getSceneManager()->addParticleSystemSceneNode(false, Game::getCurrentPlayer()->getSceneNode());
	irr::scene::IParticleEmitter* em = leafParticleSystem->createBoxEmitter(irr::core::aabbox3df(-20, -20, -100, 20, 0, 0),
																		   irr::core::vector3df(-0.1f, 0.2f, 0),
																		   20U, 25U,
																		   irr::video::SColor(255, 255, 255, 255),
																		   irr::video::SColor(255, 255, 255, 255),
																		   200U, 200U, 180,
																		   irr::core::dimension2df(3, 3),
																		   irr::core::dimension2df(5, 5));
	leafParticleSystem->setEmitter(em);
	em->drop();
	leafParticleSystem->setPosition(irr::core::vector3df(0, 0, 100));
	leafParticleSystem->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	leafParticleSystem->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	leafParticleSystem->setMaterialTexture(0, device->getSceneManager()->getVideoDriver()->getTexture("Assets/Particles/Leaf3Mid.png"));
	leafParticleSystem->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void JungleWorld::loadPhase2(irr::IrrlichtDevice *device){
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
	int spawnOrder[20] = {1, 1, 2, 1, 2, 3, 1, 1, 3, 2, 3, 1, 3, 1, 2, 1, 3, 3, 2, 3};

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
	for(int i = 0; i < 16; i++){
		y = (irr::f32)(rand() % 70 + 1) - 35;
		StaticObject *Obsticle = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", device->getSceneManager(), true);
		Obsticle->moveAwayFromPlayer(true, Game::getCurrentPlayer()->getMovementSpeed());
		z += (rand() % 500 + 500) + (player->getMovementSpeed() * 2.7f);
	}

	phase2Loaded = true;
}


void JungleWorld::clearTerrains(){
	World::clearTerrains();

	//Clear the particle system
	if(leafParticleSystem != NULL){
		leafParticleSystem->remove();
	}
}
