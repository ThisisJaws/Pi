#include "LavaWorld.h"

#include "Game.h"
LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player){

	//Set the player start pos
	phase1StartPosition = irr::core::vector3df(256, 60, -500);

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

	//Load in the Lava
	//TODO
	//

	//Call the super function to finish loading the phase
	World::loadPhase1(device);
}

void LavaWorld::loadPhase1Obsticles(const irr::core::vector3df &playerStartPos, irr::scene::ISceneManager *sceneManager, irr::video::IVideoDriver *videoDriver){
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
