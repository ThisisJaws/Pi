#include "Game.h"

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
    PlayerShip player = PlayerShip(&eReceiver, device->getTimer(), smgr, driver);
    //add a camera to render the scene and give it to the player
    player.addCamera(smgr->addCameraSceneNode());
    
    //create the points in where the modes will change - TEST
    int changePoints[6] = {1000, 2000, 3000, 4000, 5000, 6000};
    player.addChangeModePoints(changePoints);
    
    //create the enemies
    EnemyShip enemyTest = EnemyShip(&player, irr::core::vector3df(1200, 50, 0), 30.0f, 250, device->getTimer(), "Assets/PlaceHolders/ship 1 obj.obj", "Assets/PlaceHolders/ship 1 obj.mtl", smgr, driver);
    
    //create the static objects - these wont get added onto the update vector
    StaticObject testCube1 = StaticObject(irr::core::vector3df(160, 0, 0), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
    StaticObject testCube2 = StaticObject(irr::core::vector3df(370, 0, 60), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
    StaticObject testCube3 = StaticObject(irr::core::vector3df(350, 0, -70), "Assets/PlaceHolders/HeightCube.obj", "", smgr, driver);
    
    //temp - resize
    testCube1.getSceneNode()->setScale(irr::core::vector3df(20, 20, 20));
    testCube2.getSceneNode()->setScale(irr::core::vector3df(20, 20, 20));
    testCube3.getSceneNode()->setScale(irr::core::vector3df(20, 20, 20));
    
    //add all objects into the vector
    objectsToUpdate.push_back(&player);
    objectsToUpdate.push_back(&enemyTest);
    
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
        for(std::vector<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
            if(*objectIterator == NULL){
                //remove any destroyed or dleted objects
                objectIterator = objectsToUpdate.erase(objectIterator);
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
    for(std::vector<Object*>::iterator objectIterator = objectsToUpdate.begin(); objectIterator != objectsToUpdate.end(); ++objectIterator){
        Object *toDelete = *objectIterator;
        delete toDelete;
    }
    objectsToUpdate.clear();
    objectsToUpdate.resize(0);
}