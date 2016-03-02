#include "World.h"

#include "Game.h"

World::World(PlayerShip *player, const std::string &levelLocation, const irr::io::path &skyDomeLocation){
	this->player = player;
	this->levelLocation = levelLocation;
	this->skyDomeLocation = skyDomeLocation;

	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;
}

void World::loadPhase1(irr::IrrlichtDevice *device, audiere::AudioDevicePtr audDevice){
	//Load the map file
	loadMapFile(levelLocation, device, audDevice);

	//Reset the player's position
	player->changePosition(irr::core::vector3df(0, 0, -500));

	//Phase is now loaded
	phase1Loaded = true;
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
			if(!Game::objectToUpdateContainsAnyType(TYPE_SHIP_ENEMY) && !Game::objectToUpdateContainsAnyType(TYPE_BULLET)){
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

irr::io::path World::getSkydomeLocation(){
	return skyDomeLocation;
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
}

void World::loadMapFile(const std::string &mapFile, irr::IrrlichtDevice *device, audiere::AudioDevicePtr audDevice){
	//Create a variable to read the file
	std::ifstream file;
	//The string that will hold each line of the file
	std::string line;
	//Path to the level segments
	const std::string levelPath = "Assets/LevelAssets/";

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

			//Store the levelPath of the mesh
			std::string meshPath = levelPath + nameOfObject + ".obj";
			//Remove the last two letters off of the string to make setting the textures easier
			nameOfObject.erase(nameOfObject.end() - 2, nameOfObject.end());
			//Set the texture levelPath
			std::string textPath = levelPath + nameOfObject + ".jpg";

			//Check thefirst letter of the name to find out what the object is
			if(nameOfObject.at(0) == 'L'){
				//For land piece
				StaticObject *terrainPiece = new StaticObject(objectPos, meshPath.c_str(), textPath.c_str(), device->getSceneManager(), false);
				terrainPiece->changeRotation(objectRot);
				terrainPiece->getSceneNode()->setScale(objectScale);

				//Add to the internal vector
				terrainSegments.push_back(terrainPiece);

				//Add to the update vector
				Game::addObjectToUpdate(terrainPiece);

			} else if(nameOfObject.at(0) == 'O'){
				//For StaticObjects
				StaticObject *Obsticle = new StaticObject(objectPos, meshPath.c_str(), textPath.c_str(), device->getSceneManager(), false);
				Obsticle->changeRotation(objectRot);
				Obsticle->getSceneNode()->setScale(objectScale);

				//Add to the update vector
				Game::addObjectToUpdate(Obsticle);

			} else if(nameOfObject.at(0) == 'C'){
				//For Collectibles
				if(nameOfObject.at(1) == 'A'){
					//For Ammo
					Ammo *ammo = new Ammo(objectPos, device->getSceneManager(), audDevice);
					//Add to the update vector
					Game::addObjectToUpdate(ammo);
				} else if(nameOfObject.at(1) == 'G'){
					//For Gem - get the texture to use
					std::string gemType;
					if(nameOfObject.at(2) == 'B'){
						//Bronze
						BronzeGem *gem = new BronzeGem(objectPos, device->getSceneManager(), audDevice);
						Game::addObjectToUpdate(gem);
					} else if(nameOfObject.at(2) == 'S'){
						//Silver
						SilverGem *gem = new SilverGem(objectPos, device->getSceneManager(), audDevice);
						Game::addObjectToUpdate(gem);
					} else if(nameOfObject.at(2) == 'G'){
						//Gold
						GoldGem *gem = new GoldGem(objectPos, device->getSceneManager(), audDevice);
						Game::addObjectToUpdate(gem);
					}
				}
			}
		}

		//Close the file when done
		file.close();

		//Sort the vector to put all objects in ascending order of the Z pos
		//This will mean checking the player position for the end of the level will work better
		std::sort(terrainSegments.begin(), terrainSegments.end(), less_than_key());
	}
}
