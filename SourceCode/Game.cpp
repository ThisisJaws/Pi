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

    //make the address of selector 0 for now
    //selector = 0;

	previousScore = 0;
}

void Game::load(irr::scene::ICameraSceneNode *camera){
    //Create a ship for the player
    PlayerShip *player = new PlayerShip(eReceiver, device->getTimer(), smgr, driver);
    //Give the player the camera
    player->addCamera(camera);
    //Add the change points to the player - THESE ARE TEMP
    int changePoints[6] = {4500, 9000, 11000, 13000, 16000, 6000};
    player->addChangeModePoints(changePoints);
    //Add the player oto the update list
    addObjectToUpdate(player);
    //Add to the global variable
    g_player = player;

    //BELOW IS ALL TEMPORARY AND IS JUST FOR THE PURPOSE OF A DEMO LEVEL
    srand(1);

    //array of test cubes
    int x = 0, y = 0, z = 500;
    int colChanceA;
    int colChanceB;
    for(int i = 0; i < 40; i++){
        colChanceA = rand() % 5 + 1;
        colChanceB = rand() % 2 + 1;
        if(colChanceA == 1){
            if(colChanceB == 1){
                Ammo *ap = new Ammo(irr::core::vector3df(x, y, z), smgr, driver);
                addObjectToUpdate(ap);
            }else{
                Gem *gp = new Gem(irr::core::vector3df(x, y, z), smgr, driver);
                addObjectToUpdate(gp);
            }
        }else{
            StaticObject *cube = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", smgr, driver);
            cube->changePosition(irr::core::vector3df(x,y,z));
            addObjectToUpdate(cube);
        }

        y = rand() % 30 + 1;
        y -= 10;

        x = rand() % 40 + 1;
        x -= 20;

        z += 100;
    }

    //array of test enemies
    z = changePoints[0] + 600;
    y = 0;
    x = 0;
    for(int i = 0; i < 3; i++){
        //basic
        BasicEnemy *test1 = new BasicEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
        test1->changePosition(irr::core::vector3df(x,y,z));
        addObjectToUpdate(test1);

        z += 400;

        //strong
        StrongEnemy *test2  = new StrongEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
        test2->changePosition(irr::core::vector3df(x,y,z));
        addObjectToUpdate(test2);

        z += 400;

        //fast
        FastEnemy *test3  = new FastEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
        test3->changePosition(irr::core::vector3df(x,y,z));
        addObjectToUpdate(test3);

        z += 400;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Load in the sky box
    skyBox = smgr->addSkyBoxSceneNode(driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                      driver->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"));

    //Load the text variables
    guienv->getSkin()->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 255, 255, 255));
    scoreText = guienv->addStaticText(L"Score set up", irr::core::rect<irr::s32>(10, 10, 200, 22));
    ammoText = guienv->addStaticText(L"Ammo set up", irr::core::rect<irr::s32>(10, 30, 200, 42));
    FPSText = guienv->addStaticText(L"FPS Set up", irr::core::rect<irr::s32>(10, 50, 200, 62));

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
	}else if (g_player->playerReset()){
		resetGame();
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
    objectsToUpdate.clear();
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
}

void Game::addObjectToUpdate(Object* toAdd){
    objectsToUpdate.push_back(toAdd);
}

bool Game::isLoaded(){
    return loaded;
}

unsigned int Game::getFinalScore(){
    return previousScore;
}

void Game::resetGame(){
	//loop through object vector and delete all pointers
	for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
		
		if((*objectIterator)->getTypeID() != g_player->getTypeID()){
			Object *toDelete = *objectIterator;
			toDelete->getSceneNode()->remove();
			delete toDelete;
		}
	}
	//objectsToUpdate.clear();
	objectsToUpdate.resize(1);

	//readd the player
	//addObjectToUpdate(g_player);

	//BELOW IS ALL TEMPORARY AND IS JUST FOR THE PURPOSE OF A DEMO LEVEL
	srand(1);

	//array of test cubes
	int x = 0, y = 0, z = 500;
	int colChanceA;
	int colChanceB;
	for(int i = 0; i < 40; i++){
		colChanceA = rand() % 5 + 1;
		colChanceB = rand() % 2 + 1;
		if(colChanceA == 1){
			if(colChanceB == 1){
				Ammo *ap = new Ammo(irr::core::vector3df(x, y, z), smgr, driver);
				addObjectToUpdate(ap);
			} else{
				Gem *gp = new Gem(irr::core::vector3df(x, y, z), smgr, driver);
				addObjectToUpdate(gp);
			}
		} else{
			StaticObject *cube = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/AsteroidTextureA.jpg", smgr, driver);
			cube->changePosition(irr::core::vector3df(x, y, z));
			addObjectToUpdate(cube);
		}

		y = rand() % 30 + 1;
		y -= 10;

		x = rand() % 40 + 1;
		x -= 20;

		z += 100;
	}

	//array of test enemies
	z = 4500 + 600;
	y = 0;
	x = 0;
	for(int i = 0; i < 3; i++){
		//basic
		BasicEnemy *test1 = new BasicEnemy(g_player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
		test1->changePosition(irr::core::vector3df(x, y, z));
		addObjectToUpdate(test1);

		y = rand() % 100 + 1;
		y -= 50;

		z += 400;

		//strong
		StrongEnemy *test2 = new StrongEnemy(g_player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
		test2->changePosition(irr::core::vector3df(x, y, z));
		addObjectToUpdate(test2);

		y = rand() % 200 + 1;
		y -= 100;

		z += 400;

		//fast
		FastEnemy *test3 = new FastEnemy(g_player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
		test3->changePosition(irr::core::vector3df(x, y, z));
		addObjectToUpdate(test3);

		y = rand() % 200 + 1;
		y -= 100;

		z += 400;
	}
}