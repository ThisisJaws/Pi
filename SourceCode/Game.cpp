#include "Game.h"

#include <stdlib.h>

//declaring the static member
std::list<Object*> Game::objectsToUpdate;

//init all the global variables
Game::Game(irr::IrrlichtDevice *device, EventReceiver *receiver){
    //get a pointer to the irrlicht device
    this->device = device;

    //get the neccessary pointers
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
    eReceiver = receiver;

	//Init default variables
	previousScore = 0;
	currentWorld = 0;

	stageWaitTime = 3.5f;
	stageWaitPast = 0;

	//init the vector to correct length
	levelMusic = std::vector<sf::Music*>(NUM_WORLDS);

	played = false;

	loaded = false;
}

Game::~Game(){
	//loop through object vector and delete all pointers
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		Object *toDelete = *objectIterator;
		delete toDelete;
	}
}

void Game::load(irr::scene::ICameraSceneNode *camera){
    //Create a ship for the player
    PlayerShip *player = new PlayerShip(eReceiver, device->getTimer(), smgr);
    //Give the player the camera
    player->addCamera(camera);
    //Add to the global variable
    g_player = player;

	//Add the worlds into the array to load later
	worlds[0] = new LavaWorld(g_player);
	worlds[1] = new IceWorld(g_player);
	worlds[2] = new JungleWorld(g_player);

	//Load the first world
	worlds[currentWorld]->loadPhase1(device);

	//Load in the music
	levelMusic[0] = new sf::Music();
	levelMusic[0]->openFromFile("Assets/Sound/Levels/Lava Level/Lava Level.wav");
	levelMusic[1] = new sf::Music();
	levelMusic[1]->openFromFile("Assets/Sound/Levels/Ice Level/Ice Level.wav");
	levelMusic[2] = new sf::Music();
	levelMusic[2]->openFromFile("Assets/Sound/Levels/Forest Level/Forest Level.wav");

	//Set up each track
	for(int i = 0; i < NUM_WORLDS; i++){
		levelMusic[i]->setVolume(75);
		levelMusic[i]->setLoop(true);
	}

	//Load in the space music
	spaceMusic = new sf::Music();
	spaceMusic->openFromFile("Assets/Sound/Levels/Space/Space Level.wav");
	spaceMusic->setVolume(75);
	spaceMusic->setLoop(true);

	//Load in the stage complete
	stageCompleteBuff.loadFromFile("Assets/Sound/Phase Transition/Phase transition.wav");
	stageCompleteSFX.setBuffer(stageCompleteBuff);

	//Play the current track
	levelMusic[currentWorld]->play();

    //Load in the sky dome's for the worlds
	for(int i = 0; i < NUM_WORLDS; i++){
		skyDome[i] = smgr->addSkyDomeSceneNode(driver->getTexture(worlds[i]->getSkydomeLocation()));
		skyDome[i]->setVisible(false);
	}

	skyDome[currentWorld]->setVisible(true);

	spaceDome = smgr->addSkyDomeSceneNode(driver->getTexture("Assets/SkyDomes/rsz_162.jpg"));
	spaceDome->setVisible(false);

    //Set the font
	guienv->getSkin()->setFont(guienv->getFont("Assets/TheFont.xml"));
    //Set the colour
	guienv->getSkin()->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 0, 255, 0)); //ARGB
	//Load in the static text variables
    scoreText = guienv->addStaticText(L"Score set up", irr::core::rect<irr::s32>(10, 10, 500, 40));
	livesText = guienv->addStaticText(L"Lives set up", irr::core::rect<irr::s32>(630, 40, 800, 70));
    ammoText = guienv->addStaticText(L"Ammo set up", irr::core::rect<irr::s32>(630, 10, 800, 40));
	stageCompleteText = guienv->addStaticText(L"STAGE COMPLETE", irr::core::rect<irr::s32>(260, 250, 700, 300));
	stageCompleteText->setVisible(false);

    //Start the timer for frame independent movement
    then = device->getTimer()->getRealTime();

    //Game has been loaded
    loaded = true;
}

bool Game::play(){
    //Work out frame delta time
    now = device->getTimer()->getRealTime();
    frameDeltaTime = (irr::f32)(now - then) / 1000.0f;
    then = now;

    //Tick(update) all objects
    for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); /*removed increment here because it will crash when iterator is changed*/){
        if((*objectIterator)->isMarkedForDelete()){
            //Remove the object if it is marked for deletion
            Object *toDelete = *objectIterator;
            objectIterator = objectsToUpdate.erase(objectIterator);
            toDelete->removeFromScene();
            delete toDelete;
        }else{
            //Update the object
            (*objectIterator)->tick(frameDeltaTime);

            //Increment iterator
            ++objectIterator;
        }
    }

    //Update the score text
    irr::core::stringw scoreCount(L"Score: ");
    scoreCount += g_player->getScore();
    scoreText->setText(scoreCount.c_str());

	//Update the lives text
	irr::core::stringw livesCount(L"Lives: ");
	livesCount += g_player->getLives();
	livesText->setText(livesCount.c_str());

    //Update the ammo text
    irr::core::stringw ammoCount(L"Ammo: ");
    ammoCount += g_player->getAmmo();
    ammoText->setText(ammoCount.c_str());

    //If the player loses, end this current game
	if(g_player->playerLost()){
		previousScore = g_player->getScore();
		levelMusic[currentWorld]->stop();
		cleanUp();
		return true;
	}

	//Check if a phase has been completed
	if(worlds[currentWorld]->isPhase1Complete() || worlds[currentWorld]->isPhase2Complete()){
		//If either is complete lock the player's controls
		g_player->setControlLock(true);
		stageCompleteText->setVisible(true);

		//If it is phase 1 that is complete play the phase sound
		if(worlds[currentWorld]->isPhase1Complete() && !worlds[currentWorld]->isPhase2Complete() && !played){
			stageCompleteSFX.play();
			levelMusic[currentWorld]->stop();
			played = true;
		}

		//Wait for a period of time after the stage is completed
		if(stageWaitPast > stageWaitTime){
			//Reset the variables
			stageWaitPast = 0;
			g_player->setControlLock(false);
			stageCompleteText->setVisible(false);
			played = false;

			//Then check what needs to be loaded
			if(!worlds[currentWorld]->isPhase2Loaded()){
				//Reset the objects
				resetObjectsToUpdate(true);
				//Change mode first because of speed increase
				g_player->changeMode();
				//Load in the next phase
				worlds[currentWorld]->loadPhase2(device);
				//Change to the correct music track
				spaceMusic->play();
				skyDome[currentWorld]->setVisible(false);
				spaceDome->setVisible(true);
			} else{
				//Reset the objects
				resetObjectsToUpdate(true);
				//Reset the world
				worlds[currentWorld]->reset();
				//Turn off the dome
				spaceDome->setVisible(false);
				//Stop the current track
				spaceMusic->stop();
				//Increment the cuurent world tracker
				currentWorld++;
				//Check if there are any more worlds to load
				if(currentWorld < NUM_WORLDS){
					//Change mode
					g_player->changeMode();
					//Load the next world
					worlds[currentWorld]->loadPhase1(device);
				} else{
					//Start again but increment speed by double
					currentWorld = 0;
					g_player->changeMode(2);
					worlds[currentWorld]->loadPhase1(device);
				}
				//Turn on the next skydome
				skyDome[currentWorld]->setVisible(true);
				//Play the correct music
				levelMusic[currentWorld]->play();
			}
		} else{
			stageWaitPast += frameDeltaTime;
		}
	}

    return false;
}

void Game::cleanUp(){
	resetObjectsToUpdate(false);

	//Clear the player
	g_player = 0;

	//Reset the current world
	currentWorld = 0;

    //Remove the static text objects
    scoreText->remove();
	livesText->remove();
    ammoText->remove();

	//Loop through all worlds
	for(int i = 0; i < NUM_WORLDS; i++){
		//Make sure there are no scene nodes left
		worlds[i]->reset();
		//Delete the world
		delete worlds[i];
		//And remove the skydomes
		skyDome[i]->remove();
	}
	spaceDome->remove();

	//Delete the music from memory
	for(int i = 0; i < NUM_WORLDS; i++){
		delete levelMusic[i];
	}
	delete spaceMusic;

	//Game is no longer loaded
	loaded = false;
}

void Game::addObjectToUpdate(Object *toAdd){
    objectsToUpdate.push_back(toAdd);
}

bool Game::objectToUpdateContainsAnyType(const int &typeID){
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getTypeID() == typeID){
			return true;
		}
	}

	//if the loop completes, no objects are of requested type
	return false;
}

Object* Game::getObjectReferenceByID(const irr::s32 &objectID){
	//Make sure it isn't looknig for 0
	if(objectID == 0){
		return NULL;
	}

	//Loop through the list to find the object with the same ID
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getUniqueID() == objectID){
			return (*objectIterator);
		}
	}

	//If the loop completes return NULL
	return NULL;
}

PlayerShip* Game::getCurrentPlayer(){
	//Loop through the vector as work around for the non static variable
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getTypeID() == TYPE_SHIP_PLAYER){
			return dynamic_cast<PlayerShip*>(*objectIterator);
		}
	}

	return NULL;
}

bool Game::checkBehidPlayer(const irr::f32 &zPos){
    //Loop through the static vector to find the player
    for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getTypeID() == TYPE_SHIP_PLAYER){
			return (*objectIterator)->getPosition().Z > zPos;
		}
	}

	return false;
}

bool Game::isLoaded(){
    return loaded;
}

unsigned int Game::getFinalScore(){
    return previousScore;
}

void Game::resetObjectsToUpdate(bool keepPlayer){
	//loop through object vector and delete all pointers
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if(keepPlayer && (*objectIterator)->getTypeID() == g_player->getTypeID()){
			continue;
		}
			//Get a reference to the object
			Object *toDelete = *objectIterator;
			//Clear its texture from memory
			device->getVideoDriver()->removeTexture(toDelete->getSceneNode()->getMaterial(0).getTexture(0));
			//Remove it from the scene
			toDelete->getSceneNode()->remove();
			//Delete the object from memory
			delete toDelete;
	}
	objectsToUpdate.resize(keepPlayer ? 1 : 0);
}
