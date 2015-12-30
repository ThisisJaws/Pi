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
}

void Game::load(irr::scene::ICameraSceneNode *camera){
    //Create a ship for the player
    PlayerShip *player = new PlayerShip(eReceiver, device->getTimer(), smgr, driver);
    //Give the player the camera
    player->addCamera(camera);
    //Add the player oto the update list
    addObjectToUpdate(player);
    //Add to the global variable
    g_player = player;

	//Add the worlds into the array to load later
	worlds[0] = new LavaWorld(g_player);

	//Load the first world
	worlds[0]->loadPhase1(device);

    //Load in the sky box
    skyBox = smgr->addSkyBoxSceneNode(driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"));

    //Set the font
	guienv->getSkin()->setFont(guienv->getFont("Assets/Font.png"));
    //Set the colour
	guienv->getSkin()->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 0, 255, 0)); //ARGB
	//Load in the static text variables
    scoreText = guienv->addStaticText(L"Score set up", irr::core::rect<irr::s32>(10, 10, 500, 40));
    ammoText = guienv->addStaticText(L"Ammo set up", irr::core::rect<irr::s32>(10, 41, 300, 71));
    FPSText = guienv->addStaticText(L"FPS Set up", irr::core::rect<irr::s32>(10, 72, 300, 102));

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

    //Update the ammo text
    irr::core::stringw ammoCount(L"Ammo: ");
    ammoCount += g_player->getAmmo();
    ammoText->setText(ammoCount.c_str());

    //Update FPS text
    irr::core::stringw FPSCount(L"FPS: ");
    FPSCount += driver->getFPS();;
    FPSText->setText(FPSCount.c_str());

    //If the player loses, end this current game
	if(g_player->playerLost()){
		previousScore = g_player->getScore();
		cleanUp();
		return true;
	}

	//Check the win condition of the current game
	if(worlds[currentWorld]->isPhase1Complete() && !worlds[currentWorld]->isPhase2Loaded()){
		//Load phase 2
		resetObjectsToUpdate();
		//Change mode first because of speed increase
		g_player->changeMode();
		//Load in the next phase
		worlds[currentWorld]->loadPhase2(device);
	} 
	
	//When phase 2 is complete
	if(worlds[currentWorld]->isPhase2Complete()){
		//Reset the objects
		resetObjectsToUpdate();
		//Reset the world
		worlds[currentWorld]->reset();
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
	}

    return false;
}

void Game::cleanUp(){
    //loop through object vector and delete all pointers
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		Object *toDelete = *objectIterator;
		toDelete->getSceneNode()->remove();
		delete toDelete;
	}
    objectsToUpdate.resize(0);

    //clear the player pointer
    g_player = 0;

    //Get rid of the skybox
    skyBox->remove();

    //Remove the static text objects
    scoreText->remove();
    ammoText->remove();
    FPSText->remove();

    //Game is not loaded
    loaded = false;

	//Loop through all worlds
	for(int i = 0; i < NUM_WORLDS; i++){
		//Make sure there are no scene nodes left
		worlds[i]->reset();
		//Delete the world
		delete worlds[i];
	}
}

void Game::addObjectToUpdate(Object* toAdd){
    objectsToUpdate.push_back(toAdd);
}

bool Game::objectToUpdateContainsAnyType(int typeID){
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getTypeID() == typeID){
			return true;
		}
	}

	//if the loop completes, no objects are of requested type
	return false;
}

bool Game::isLoaded(){
    return loaded;
}

unsigned int Game::getFinalScore(){
    return previousScore;
}

void Game::resetObjectsToUpdate(){
	//loop through object vector and delete all pointers
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		if((*objectIterator)->getTypeID() != g_player->getTypeID()){
			Object *toDelete = *objectIterator;
			toDelete->getSceneNode()->remove();
			delete toDelete;
		}
	}
	objectsToUpdate.resize(1);
}