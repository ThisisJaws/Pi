#include "LavaWorld.h"

#include "Game.h"
LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player){

	//Set the player start pos
	phase1StartPosition = irr::core::vector3df(256, 100, -500);

	//Load in all the file paths
	heightMapLocations[0] = "Assets/Environment/Levels/LavaWorld/Land/HeightMap-Piece1-512x512.jpg";
	heightMapLocations[1] = "Assets/Environment/Levels/LavaWorld/Land/HeightMap-Piece2-512x512.jpg";
	heightMapLocations[2] = "Assets/Environment/Levels/LavaWorld/Land/HeightMap-Piece3-512x512.jpg";
	heightMapLocations[3] = "Assets/Environment/Levels/LavaWorld/Land/HeightMap-Piece4-512x512.jpg";
	heightMapLocations[4] = "Assets/Environment/Levels/LavaWorld/Land/HeightMap-Piece5-512x512.jpg";

	//Load in the texture's file path
	terrainTexturePath = "Assets/Environment/Levels/LavaWorld/Land/LavaWorldTexture-Land.png";
}

void LavaWorld::loadPhase1(irr::IrrlichtDevice *device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the seed
	srand(1);
	//The position to place each terrain
	irr::core::vector3df terrainPos(0);
	//Loop through and place each terrain
	for(int i = 0; i < TERRAIN_NODE_COUNT; i++){
		//Random number for which tile to load
		int tile = rand() % HEIGHT_MAP_COUNT;
		//Create a terrain scene node using the tile selection
		terrainNodes[i] = loadTerrain(device, heightMapLocations[tile], driver->getTexture(terrainTexturePath), irr::core::vector3df(1), terrainPos);
		//Get an array to hold all of the edges
		irr::core::vector3d<irr::f32> edges[8];
		//Get the bounding box of the mesh
		irr::core::aabbox3d<irr::f32> boundingBox = terrainNodes[i]->getTransformedBoundingBox();
		//Get the edges of the box
		boundingBox.getEdges(edges);
		//Increase the starting pos by the length of the box
		terrainPos.Z += (edges[2].Z - edges[0].Z);
	}

	//This level requires two types of terrains so any extra one has to be loaded in 
	//terrainLava = loadTerrain(device,
	//						  "Assets/Environment/Levels/LavaWorldHeightMapLava.jpg",
	//						  driver->getTexture("Assets/PlaceHolders/Levels/lava.jpg"),
	//						  irr::core::vector3df(10, 2, 10),
	//						  irr::core::vector3df(0, 70, 0));

	//Load in all the individual objects
	//loadPhase1Rocks(phase1StartPosition, smgr, driver);
	//loadPhase1Gems(phase1StartPosition, smgr, driver);
	//loadPhase1Ammo(phase1StartPosition, smgr, driver);

	//Set the player position to the phase start position
	player->changePosition(phase1StartPosition);

	//Phase is now loaded
	phase1Loaded = true;
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice *device){
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

void LavaWorld::loadPhase1Rocks(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver){
	//The pointer that will init all the rocks into memory then be passed into the list
	StaticObject *rock;

	//Where the rock will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//The path of the mesh and textures
	irr::io::path meshPath = "Assets/Environment/Rocks.obj";
	irr::io::path texturePath = "Assets/PlaceHolders/Levels/mountain.png";

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 1000;
	//Create the new object
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	//Put it on the update list
	Game::addObjectToUpdate(rock);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//Repeating for all objects
	//2
	spawnPos.Z += 300;
	spawnPos.X += 15;
	spawnPos.Y -= 10;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//3
	spawnPos.Z += 790;
	spawnPos.X += 15;
	spawnPos.Y -= 5;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//4
	spawnPos.Z += 460;
	spawnPos.X += 10;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;

	//5
	spawnPos.Z += 250;
	spawnPos.X -= 15;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;

	//6
	spawnPos.Z += 200;
	spawnPos.X += 17;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//7
	spawnPos.Z += 1350;
	spawnPos.X -= 13;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;

	//8
	spawnPos.Z += 130;
	spawnPos.X += 13;
	spawnPos.Y += 4;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//9
	spawnPos.Z += 200;
	spawnPos.Y += 12;
	spawnPos.X -= 3;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//10
	spawnPos.Z += 1010;
	spawnPos.X -= 12;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	
	//11
	spawnPos.Z += 500;
	spawnPos.X -= 10;
	spawnPos.Y -= 2;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//12
	spawnPos.X += 12;
	spawnPos.Y += 4;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//13
	spawnPos.Z += 400;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);

	//14
	spawnPos.Z += 200;
	spawnPos.X += 11;
	spawnPos.Y += 3;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//15
	spawnPos.Z += 150;
	spawnPos.X -= 7;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);
	spawnPos.X = playerStartPos.X;

	//16
	spawnPos.Z += 1034;
	spawnPos.X -= 18;
	spawnPos.Y += 9;
	rock = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	Game::addObjectToUpdate(rock);

	//Clear the pointer when done
	rock = 0;
}

void LavaWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//The pointer that will init all the gems into memory then be passed into the list
	Gem *gem;

	//Where the gems will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 2090;
	spawnPos.X -= 10;
	spawnPos.Y += 5;
	//Create the new object
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	//Put it on the update list
	Game::addObjectToUpdate(gem);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//Repeating for all objects
	//2
	spawnPos.Z += 1217;
	spawnPos.X += 20;
	spawnPos.Y -= 2;
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(gem);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//3
	spawnPos.Z += 2387;
	spawnPos.X += 20;
	spawnPos.Y -= 6;
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(gem);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//4
	spawnPos.Z += 1880;
	spawnPos.X -= 20;
	spawnPos.Y += 17;
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(gem);

	//Clear the pointer when done
	gem = 0;
}

void LavaWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//The pointer that will init all the ammo into memory then be passed into the list
	Ammo *ammo;

	//Where the ammo will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 3510;
	spawnPos.X -= 17;
	spawnPos.Y += 18;
	//Create the new object
	ammo = new Ammo(spawnPos, sceneManager, videoDriver);
	//Put it on the update list
	Game::addObjectToUpdate(ammo);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//2
	spawnPos.Z += 1400;
	spawnPos.Y -= 7;
	ammo = new Ammo(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(ammo);

	//Clear the pointer when done
	ammo = 0;
}
