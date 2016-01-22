#include "World.h"

#include "Game.h"

World::World(PlayerShip *player, const std::string &levelLocation){
	this->player = player;
	this->levelLocation = levelLocation;

	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;
}

void World::loadPhase1(irr::IrrlichtDevice * device){
	//Reset the player's position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//Load the map file
	loadMapFile(levelLocation, device);

	//Phase is now loaded
	phase1Loaded = true;
}

void World::loadPhase2(irr::IrrlichtDevice *device){
	//Unload the terrains from the scene
	clearTerrains();

	//Make sure the previous phase is no longer considered loaded
	phase1Loaded = false;

	//Change the sun to be with the camera
	sun->setParent(device->getSceneManager()->getActiveCamera());
	sun->setPosition(irr::core::vector3df(0, 0, 0));
	sun->setRadius(500);

	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the random seed
	srand(1);

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	//array of Enemies - these get deleted once they move off screen
	irr::f32 x = 0; irr::f32 y = 0; irr::f32 z = 500;
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

		Game::addObjectToUpdate(gem);

		z += rand() % 3000 + 100;
	}

	phase2Loaded = true;
}


bool World::isPhase1Loaded(){
	return phase1Loaded;
}

bool World::isPhase2Loaded(){
	return phase2Loaded;
}

bool World::isPhase1Complete(){
	//Check if the player has complete phase 1
	if(phase1Loaded){
		//Return if it is already complete to avoid uneccesary calculations
		if(phase1Complete){
			return true;
		} else{
			//Get an array to hold all of the edges
			irr::core::vector3d<irr::f32> edges[8];
			//Get the counding box of the mesh
			irr::core::aabbox3d<irr::f32> boundingBox = terrainSegments.at(terrainSegments.size() - 1)->getSceneNode()->getTransformedBoundingBox();
			//Get the edges of the box
			boundingBox.getEdges(edges);

			if(player->getPosition().Z >= edges[2].Z){
				phase1Complete = true;
				return true;
			} else{
				return false;
			}
		}
	} else{
		return false;
	}
}

bool World::isPhase2Complete(){
	//Check if the player has completed phase 2
	if(phase2Loaded){
		//Return if it is already complete to avoid uneccesary calculations
		if(phase2Complete){
			return true;
		} else{
			if(!Game::objectToUpdateContainsAnyType(TYPE_SHIP_ENEMY)){
				phase2Complete = true;
				return true;
			} else{
				return false;
			}
		}
	} else{
		return false;
	}
}

void World::clearTerrains(){
	//Clear the vector, the object references get deleted in Game.cpp
	terrainSegments.clear();
	terrainSegments.resize(0);
}

void World::reset(){
	//Remove any terrains
	if(phase1Loaded){
		clearTerrains();
	}

	//Reset the bools
	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;

	//Get rid of the light
	if(sun){
		sun->remove();
	}
}

void World::loadMapFile(const std::string &mapFile, irr::IrrlichtDevice *device){
	//Create a variable to read the file
	std::ifstream file;
	//The string that will hold each line of the file
	std::string line;
	//Path to the level segments
	const std::string path = "Assets/LevelAssets/";

	//The name of the object + a temp variable to hold float data
	std::string nameOfObject, tempHold;
	//The vectors that will store the objects variables
	irr::core::vector3df objectPos(0);
	irr::core::vector3df objectRot(0);
	irr::core::vector3df objectScale(0);

	//Open the file
	file.open(mapFile);

	//Check if it is open
	if(file.is_open()){
		//Loop through each line of the file
		while(std::getline(file, line)){
			/* Each part of the file is seperated by a space, ex:
			* Name posX posY posZ rotX rotY rotZ scaleX scaleY scaleZ
			* with a length of 10
			* So each bit of data is handled world by word
			*/

			//Get each word line by line
			std::stringstream stream(line);
			//Then input the neccesaary data
			stream >> nameOfObject;

			//Position
			stream >> tempHold;
			objectPos.X = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectPos.Y = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectPos.Z = std::stof(tempHold.c_str());

			//Rotation
			stream >> tempHold;
			objectRot.X = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectRot.Y = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectRot.Z = std::stof(tempHold.c_str());

			//Scale
			stream >> tempHold;
			objectScale.X = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectScale.Y = std::stof(tempHold.c_str());
			stream >> tempHold;
			objectScale.Z = std::stof(tempHold.c_str());

			//Store the path of the mesh
			std::string meshPath = path + nameOfObject + ".obj";
			//Remove the last two letters off of the string to make setting the textures easier
			nameOfObject.erase(nameOfObject.end() - 2, nameOfObject.end());
			//Set the texture path
			std::string textPath = path + nameOfObject + ".jpg";

			//Check thefirst letter of the name to find out what the object is
			if(nameOfObject.at(0) == 'L'){
				//For land piece
				StaticObject *terrainPiece = new StaticObject(objectPos, meshPath.c_str(), textPath.c_str(), device->getSceneManager(), device->getVideoDriver(), false);
				terrainPiece->changeRotation(objectRot);
				terrainPiece->getSceneNode()->setScale(objectScale);

				//Add to the internal vector
				terrainSegments.push_back(terrainPiece);

				//Add to the update vector
				Game::addObjectToUpdate(terrainPiece);

			} else if(nameOfObject.at(0) == 'O'){
				//For StaticObjects
				StaticObject *Obsticle = new StaticObject(objectPos, meshPath.c_str(), textPath.c_str(), device->getSceneManager(), device->getVideoDriver(), false);
				Obsticle->changeRotation(objectRot);
				Obsticle->getSceneNode()->setScale(objectScale);

				//Add to the update vector
				Game::addObjectToUpdate(Obsticle);

			} else if(nameOfObject.at(0) == 'C'){
				//For Collectibles
				if(nameOfObject.at(1) == 'A'){
					//For Ammo
					Ammo *ammo = new Ammo(objectPos, device->getSceneManager(), device->getVideoDriver());
					//Add to the update vector
					Game::addObjectToUpdate(ammo);
				} else if(nameOfObject.at(1) == 'G'){
					//For Gem
					Gem *gem = new Gem(objectPos, device->getSceneManager(), device->getVideoDriver());
					//Add to the update vector
					Game::addObjectToUpdate(gem);
				}
			}
		}

		//Add in a point light
		sun = device->getSceneManager()->addLightSceneNode(0, irr::core::vector3df(0, 5000, terrainSegments.size() / 2), irr::video::SColorf(1.0f, 1.0f, 1.0f), 10000.0f);

		//Close the file when done
		file.close();
	}
}
