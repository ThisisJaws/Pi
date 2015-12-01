#include "Game.h"

#include <stdlib.h>

//declaring the static member
std::list<Object*> Game::objectsToUpdate;

//init all the global variables
Game::Game(){
    //create the devie - make sure to pass the address of eReceiver 
    device = irr::createDevice(irr::video::EDT_BURNINGSVIDEO,
                               irr::core::dimension2d<irr::u32>(800, 600),
                               32, false, false, false, &eReceiver);
    
    //get the neccessary pointers
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    
    //make the address of selector 0 for now
    selector = 0;
}

int Game::play(){
    //create a ship for the player
    PlayerShip *player = new PlayerShip(&eReceiver, device->getTimer(), smgr, driver);
    //add a camera to render the scene and give it to the player
    player->addCamera(smgr->addCameraSceneNode());
    
    //BELOW IS ALL TEMPORARY AND IS JUST FOR THE PURPOSE OF A DEMO LEVEL
    //create the points in where the modes will change - TEST
    int changePoints[6] = {3000, 7500, 9000, 12000, 15000, 6000};
    player->addChangeModePoints(changePoints);
    
    srand(1);
    
    //array of test cubes
    int x, y, z = 500;
    StaticObject cubeArray[20] = StaticObject(irr::core::vector3df(x, y, z), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
    for(int i = 0; i < 20; i++){
        cubeArray[i].changePosition(irr::core::vector3df(x,y,z));
        cubeArray[i].getSceneNode()->setScale(irr::core::vector3df(10, 10, 10));
        
        y = rand() % 200 + 1;
        y -= 100;
        
        x = rand() % 200 + 1;
        x -= 100;
        
        int check = rand() % 2;
        if(check > 0){
            z += 200;
        }
    }
    
    //array of test enemies
    z = 3600;
    y = 0;
    x = 0;
    for(int i = 0; i < 3; i++){
        //basic
        BasicEnemy *test1  = new BasicEnemy(player, irr::core::vector3df(0, 50, 1600), device->getTimer(), smgr, driver);
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
    
    //add all objects into the vector
    addObjectToUpdate(player);
    //addObjectToUpdate(enemyTest1);
    
    //used to make checking fps slight more effecient
    int lastFPS = -1;
    int fps;
    
    //set up for frame independent movement
    irr::u32 then = device->getTimer()->getRealTime();
    
    //main loop
    while(device->run()){
        //work out frame delta time
        const irr::u32 now = device->getTimer()->getRealTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.0f;
        then = now;
        
        //tick(update) all objects
        for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
            if((*objectIterator)->isMarkedForDelete()){
                //remove any marked objects
                Object *toDelete = *objectIterator;
                objectIterator = objectsToUpdate.erase(objectIterator);
                delete toDelete;
            }else{
                //update the object
                (*objectIterator)->tick(frameDeltaTime);
            }
        }
        
        //tell irrlicht to draw/updates scenes
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        
        smgr->drawAll();
        
        driver->endScene();
        
        //add fps to window name (because gui isnt set up yet)
        fps = driver->getFPS();
        if (lastFPS != fps){
            irr::core::stringw tmp(L"Pi Cade ");
            tmp += L" FPS: ";
            tmp += fps;
            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
    }
    
    return EXIT_SUCCESS;
}

void Game::cleanUp(){
    //anything made with create needs to be 'droped'
    device->drop();
    selector->drop();
    
    //delete all poiters
    delete device;
    delete driver;
    delete smgr;
    delete selector;
    
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