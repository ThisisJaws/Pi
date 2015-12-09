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

    loaded = false;
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
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Load in the font
    font = guienv->getBuiltInFont();

    //Set up FPS counters
    lastFPS = -1;
    FPS = 0;

    //Start the timer for frame independent movement
    then = device->getTimer()->getRealTime();

    loaded = true;
}

void Game::play(){
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
    font->draw(scoreCount, irr::core::rect<irr::s32>(10, 10, 200, 22), irr::video::SColor(255, 255, 255, 255));

    //Update the ammo text
    irr::core::stringw ammoCount(L"Ammo: ");
    ammoCount += g_player->getAmmo();
    font->draw(ammoCount, irr::core::rect<irr::s32>(10, 30, 200, 42), irr::video::SColor(255, 255, 255, 255));

    //Update FPS text
    FPS = driver->getFPS();
    if(lastFPS != FPS){
        irr::core::stringw FPSText(L"FPS: ");
        FPSText += FPS;
        font->draw(FPSText, irr::core::rect<irr::s32>(10, 60, 200, 72), irr::video::SColor(255, 255, 255, 255));
        lastFPS = FPS;
    }
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

    loaded = false;
}

void Game::addObjectToUpdate(Object* toAdd){
    objectsToUpdate.push_back(toAdd);
}

bool Game::isLoaded(){
    return loaded;
}
