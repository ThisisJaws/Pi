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
    guienv = device->getGUIEnvironment();
    
    //make the address of selector 0 for now
    //selector = 0;
}

int Game::play(){
    //create a ship for the player
    PlayerShip *player = new PlayerShip(&eReceiver, device->getTimer(), smgr, driver);
    //add a camera to render the scene and give it to the player
    player->addCamera(smgr->addCameraSceneNode());
    
    //BELOW IS ALL TEMPORARY AND IS JUST FOR THE PURPOSE OF A DEMO LEVEL
    //create the points in where the modes will change - TEST
    int changePoints[6] = {4400, 8900, 11000, 13000, 16000, 6000};
    player->addChangeModePoints(changePoints);
    
    srand(1);
    
    //array of test cubes
    int x = 0, y = 0, z = 500;
    int colChance;
	//StaticObject cubeArray[20] = StaticObject(irr::core::vector3df(x, y, z), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
    for(int i = 0; i < 20; i++){
        colChance = rand() % 5 + 1;
        if(colChance == 1){
            Ammo *ap = new Ammo(irr::core::vector3df(x, y, z), smgr, driver);
            addObjectToUpdate(ap);
        }else{
			StaticObject *cube = new StaticObject(irr::core::vector3df(x, y, z), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
            cube->changePosition(irr::core::vector3df(x,y,z));
            cube->getSceneNode()->setScale(irr::core::vector3df(10, 10, 10));
			addObjectToUpdate(cube);
        }
        
        y = rand() % 30 + 1;
        y -= 10;
        
        x = rand() % 40 + 1;
        x -= 20;
       
        z += 200;        
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
    
    //add all objects into the vector
    addObjectToUpdate(player);
    
    //setup the user ammo count - test
    irr::gui::IGUIStaticText *ammoText = guienv->addStaticText(L"Ammo text not set", irr::core::rect<irr::s32>(10, 10, 200, 22), false);
    
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
        for(std::list<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); /*removed increment here because it will crash when iterator is changed*/){
            if((*objectIterator)->isMarkedForDelete()){
                //remove any marked objects
                Object *toDelete = *objectIterator;
                objectIterator = objectsToUpdate.erase(objectIterator);
                delete toDelete;
            }else{
                //update the object
                (*objectIterator)->tick(frameDeltaTime);

				//increment iterator
				++objectIterator;
            }
        }
        
        //update the ammo text
        irr::core::stringw ammoCount(L"Ammo: ");
        ammoCount += player->getAmmo();
        ammoText->setText(ammoCount.c_str());
        
        //tell irrlicht to draw/updates scenes
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        
        smgr->drawAll();
        guienv->drawAll();
        
        driver->endScene();
        
        //add fps to window name
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
    //selector->drop();
    
    //delete all poiters
    delete device;
    delete driver;
    delete smgr;
    delete guienv;
    //delete selector;
    
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