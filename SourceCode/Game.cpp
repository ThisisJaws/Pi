#include "Game.h"

#include <stdlib.h>

//declaring the static member
std::list<Object*> Game::objectsToUpdate;

//init all the global variables
Game::Game(){
    //make a nul device to get the desktop res
    irr::IrrlichtDevice *nullDevice = irr::createDevice(irr::video::EDT_NULL);
    irr::core::dimension2d<irr::u32> deskres = nullDevice->getVideoModeList()->getDesktopResolution();

    //create the device - make sure to pass the address of eReceiver
    device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO, deskres, 32, true, false, true, &eReceiver);

    //get the neccessary pointers
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    //make the address of selector 0 for now
    //selector = 0;

	playGame = false;

	previousScore = 0;
}

bool Game::play(){
    //create a ship for the player
    PlayerShip *player = new PlayerShip(&eReceiver, device->getTimer(), smgr, driver);

	irr::scene::ICameraSceneNode *camera = smgr->addCameraSceneNode();

    //add a camera to render the scene and give it to the player
	//player->addCamera(smgr->addCameraSceneNode());
	player->addCamera(camera);

    //BELOW IS ALL TEMPORARY AND IS JUST FOR THE PURPOSE OF A DEMO LEVEL
    //create the points in where the modes will change - TEST
    int changePoints[6] = {4500, 9000, 11000, 13000, 16000, 6000};
    player->addChangeModePoints(changePoints);

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
            StaticObject *cube = new StaticObject(irr::core::vector3df(x, y, z), "Assets/Environment/Asteroid/Asteroid1.obj", "Assets/Environment/Asteroid/Asteroid1Texture.jpg", smgr, driver);
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

        y = rand() % 100 + 1;
        y -= 50;

        z += 400;

        //strong
        StrongEnemy *test2  = new StrongEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
        test2->changePosition(irr::core::vector3df(x,y,z));
        addObjectToUpdate(test2);

        y = rand() % 200 + 1;
        y -= 100;

        z += 400;

        //fast
        FastEnemy *test3  = new FastEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
        test3->changePosition(irr::core::vector3df(x,y,z));
        addObjectToUpdate(test3);

        y = rand() % 200 + 1;
        y -= 100;

        z += 400;
    }
    //add in the terrain as a static object
    //StaticObject terrain = StaticObject(irr::core::vector3df(0, -250, 0), "Assets/PlaceHolders/terrainSnow.obj", "", smgr, driver);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //add all objects into the vector
    addObjectToUpdate(player);

    //setup the user ammo count and score - test
    irr::gui::IGUIStaticText *scoreText = guienv->addStaticText(L"", irr::core::rect<irr::s32>(10, 10, 200, 22));
    irr::gui::IGUIStaticText *ammoText = guienv->addStaticText(L"", irr::core::rect<irr::s32>(10, 32, 200, 54));

    //Text for fps
    irr::gui::IGUIStaticText *fpsText = guienv->addStaticText(L"", irr::core::rect<irr::s32>(10, 700, 200, 722));

    //used to make checking fps slight more effecient
    int lastFPS = -1;
    int fps;

    //set up for frame independent movement
    irr::u32 then = device->getTimer()->getRealTime();

	//set up the variables for the menu screen
	irr::core::stringw textForMenu(L"Press Enter to start, Previous Score: ");
	textForMenu += previousScore;
	irr::gui::IGUIStaticText *menuText = guienv->addStaticText(textForMenu.c_str(), irr::core::rect<irr::s32>(500, 500, 700, 522));
	
	camera->setPosition(irr::core::vector3df(0, 50, 0));
	camera->setTarget(irr::core::vector3df(0, 51, 0));

    //main loop
    while(device->run()){
		//check for escape key
		if(eReceiver.isKeyDown(irr::KEY_ESCAPE)){
			device->closeDevice();
			//return true;
		}

		if(eReceiver.isKeyDown(irr::KEY_RETURN) && playGame == false){
			menuText->remove();
			playGame = true;
		}

		//work out frame delta time
		const irr::u32 now = device->getTimer()->getRealTime();
		const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.0f;
		then = now;

		if(playGame){
			//tick(update) all objects
			for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); /*removed increment here because it will crash when iterator is changed*/){
				if((*objectIterator)->isMarkedForDelete()){
					//remove any marked objects
					Object *toDelete = *objectIterator;
					objectIterator = objectsToUpdate.erase(objectIterator);
					toDelete->removeFromScene();
					delete toDelete;
				}
				else{
					//update the object
					(*objectIterator)->tick(frameDeltaTime);

					//increment iterator
					++objectIterator;
				}
			}

			//update score
			irr::core::stringw scoreCount(L"Score: ");
			scoreCount += player->getScore();
			scoreText->setText(scoreCount.c_str());

			//update the ammo text
			irr::core::stringw ammoCount(L"Ammo: ");
			ammoCount += player->getAmmo();
			ammoText->setText(ammoCount.c_str());

			//add fps to window name
			fps = driver->getFPS();
			if(lastFPS != fps){
				irr::core::stringw tmp(L"FPS: ");
				tmp += fps;
				fpsText->setText(tmp.c_str());
				lastFPS = fps;
			}

		}

        //tell irrlicht to draw/updates scenes
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();

		//if player loses return to the menu
		if(player->playerLost()){
			//device->closeDevice();

			previousScore = player->getScore();

			for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
				Object *toDelete = *objectIterator;
				toDelete->getSceneNode()->remove();
				delete toDelete;
			}

			objectsToUpdate.clear();
			objectsToUpdate.resize(0);

			scoreText->remove();
			ammoText->remove();
			fpsText->remove();

			playGame = false;
			return false;
		}
    }

    return true;
}

void Game::cleanUp(){
    //anything made with create needs to be 'droped'
    device->drop();

    //loop through object vector and delete all pointers
    for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
        Object *toDelete = *objectIterator;
        delete toDelete;
    }
    objectsToUpdate.clear();
    objectsToUpdate.resize(0);
}

void Game::addObjectToUpdate(Object* toAdd){
    objectsToUpdate.push_back(toAdd);
}
