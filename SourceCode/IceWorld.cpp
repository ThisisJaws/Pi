#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player, 15, irr::core::vector3df(74, 175, -250), irr::core::vector3df(1, 0.35f, 3)){

	//Load in all the file paths
	heightMapLocations[0] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece1.jpg";
	heightMapLocations[1] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece2.jpg";
	heightMapLocations[2] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece3.jpg";
	heightMapLocations[3] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece4.jpg";
	heightMapLocations[4] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece5.jpg";

	//Load in the texture's file path
	terrainTexturePath = "Assets/Environment/Levels/IceWorld/IceWorldTexture.jpg";
}

void IceWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//Pointers to the objects that will spawn
	StaticObject *iceSpikes;
	//StaticObject *giantHail;

	//Where the objects will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//The path of the meshes and textures
	irr::io::path spike1MeshPath = "Assets/Environment/Spikes/SpikeSingle.obj";
	irr::io::path spike2MeshPath = "Assets/Environment/Spikes/SpikeMultiple.obj";
	irr::io::path texturePath = "";

	//SPIKES START
	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 400;
	spawnPos.X -= 17;
	spawnPos.Y -= 13;
	//Create the new object
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	//Rotate the object
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -7));
	//Put it on the update list
	Game::addObjectToUpdate(iceSpikes);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//2
	spawnPos.X += 9;
	spawnPos.Y -= 7;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 31));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//3
	spawnPos.Z += 130;
	spawnPos.X -= 10;
	spawnPos.Y -= 11;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -5));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//4
	spawnPos.Z += 100;
	spawnPos.X += 7;
	spawnPos.Y -= 7;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(4, 0, 14));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//5
	spawnPos.Z += 4;
	spawnPos.X -= 24;
	spawnPos.Y -= 21;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(-11, 0, -26));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//6
	spawnPos.Z += 200;
	spawnPos.Y -= 3;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(16, 0, 4));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//7
	spawnPos.Z += 73;
	spawnPos.X -= 20;
	spawnPos.Y -= 13;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -14));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//8
	spawnPos.Z += 80;
	spawnPos.X += 13;
	spawnPos.Y -= 15;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(1, 0, -9));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//9
	spawnPos.Z += 250;
	spawnPos.X -= 8;
	spawnPos.Y -= 32;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -7));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//10
	spawnPos.Z += 150;
	spawnPos.X += 18;
	spawnPos.Y -= 35;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 13));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//11
	spawnPos.Z += 280;
	spawnPos.X -= 19;
	spawnPos.Y += 4;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -43));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//12
	spawnPos.Z += 10;
	spawnPos.X += 5;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 14));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//13
	spawnPos.Z += 1100;
	spawnPos.X += 6;
	spawnPos.Y -= 18;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 12));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//14
	spawnPos.Z += 100;
	spawnPos.X -= 6;
	spawnPos.Y -= 28;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 34));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//15
	spawnPos.Z += 210;
	spawnPos.X -= 4;
	spawnPos.Y -= 14;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -17));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//16
	spawnPos.Z += 48;
	spawnPos.X -= 18;
	spawnPos.Y -= 19;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -11));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//17
	spawnPos.Z += 44;
	spawnPos.X += 4;
	spawnPos.Y -= 16;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -17));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//18
	spawnPos.Z += 67;
	spawnPos.X -= 14;
	spawnPos.Y -= 19;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 0));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//19
	spawnPos.Z += 200;
	spawnPos.X -= 3;
	spawnPos.Y -= 14;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 23));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//20
	spawnPos.Z += 50;
	spawnPos.X -= 21;
	spawnPos.Y -= 17;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -3));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//21
	spawnPos.Z += 100;
	spawnPos.X += 8;
	spawnPos.Y -= 9;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 4));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//22
	spawnPos.Z += 50;
	spawnPos.X -= 8;
	spawnPos.Y -= 10;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 0));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//23
	spawnPos.X -= 16;
	spawnPos.Y -= 13;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 0));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//24
	spawnPos.Z += 570;
	spawnPos.X += 4;
	spawnPos.Y -= 30;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -6));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//25
	spawnPos.Z += 20;
	spawnPos.X -= 11;
	spawnPos.Y -= 25;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 3));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//26
	spawnPos.Z += 20;
	spawnPos.X -= 1;
	spawnPos.Y -= 20;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 2));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//27
	spawnPos.Z += 20;
	spawnPos.X -= 8;
	spawnPos.Y -= 10;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -6));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//28
	spawnPos.Z += 420;
	spawnPos.X -= 13;
	spawnPos.Y -= 5;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -14));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//29
	spawnPos.X += 8;
	spawnPos.Y -= 5;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 14));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//30
	spawnPos.Z += 260;
	spawnPos.X += 4;
	spawnPos.Y -= 20;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 17));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//31
	spawnPos.Z += 120;
	spawnPos.X -= 14;
	spawnPos.Y -= 10;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 11));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//32
	spawnPos.Z += 80;
	spawnPos.X -= 8;
	spawnPos.Y -= 13;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -4));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//33
	spawnPos.Z += 97;
	spawnPos.X += 17;
	spawnPos.Y -= 14;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 19));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//34
	spawnPos.Z += 103;
	spawnPos.X -= 0;
	spawnPos.Y -= 11;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 2));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//35
	spawnPos.Z += 210;
	spawnPos.X -= 7;
	spawnPos.Y -= 10;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, -8));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//36
	spawnPos.Z += 400;
	spawnPos.X -= 0;
	spawnPos.Y -= 20;
	iceSpikes = new StaticObject(spawnPos, spike1MeshPath, texturePath, sceneManager, videoDriver, false);
	iceSpikes->getSceneNode()->setRotation(irr::core::vector3df(0, 0, 7));
	Game::addObjectToUpdate(iceSpikes);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;
	//SPIKES END
}

void IceWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//The pointer that will init all the gems into memory then be passed into the list
	Gem *gem;

	//Where the gems will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 410;
	spawnPos.X -= 8;
	spawnPos.Y += 18;
	//Create the new object
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	//Put it on the update list
	Game::addObjectToUpdate(gem);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//2
	//Get the spawn based off the player start position
	spawnPos.Z += 3034;
	spawnPos.X -= 15;
	spawnPos.Y += 10;
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(gem);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//3
	spawnPos.Z += 830;
	spawnPos.X += 6;
	spawnPos.Y += 4;
	gem = new Gem(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(gem);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;
}

void IceWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//The pointer that will init all the ammo into memory then be passed into the list
	Ammo *ammo;

	//Where the ammo will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 1667;
	spawnPos.X -= 1;
	spawnPos.Y += 14;
	//Create the new object
	ammo = new Ammo(spawnPos, sceneManager, videoDriver);
	//Put it on the update list
	Game::addObjectToUpdate(ammo);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;

	//2
	spawnPos.Z += 1985;
	spawnPos.X -= 10;
	spawnPos.Y += 20;
	ammo = new Ammo(spawnPos, sceneManager, videoDriver);
	Game::addObjectToUpdate(ammo);
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;
}
