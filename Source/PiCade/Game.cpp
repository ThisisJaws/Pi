#include "Game.h"

//init all the global variables
Game::Game(){
    //create the devie - make sure to pass the address of eReceiver 
    device = irr::createDevice(irr::video::EDT_OPENGL,
                               irr::core::dimension2d<irr::u32>(800, 600),
                               16, false, false, false, &eReceiver);
    
    //get the neccessary pointers
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    
    //make the address of selector 0 for now
    selector = 0;
}

int Game::play(){
    //TEMPORARY JUST TO GIVE THE PLAYER SOMETHING TO COLLIDE WITH
    //add a box to our scene for something to collide with
    irr::scene::ISceneNode *boxNode1 = smgr->addCubeSceneNode();
    //set up the box
    if(boxNode1){
        boxNode1->setPosition(irr::core::vector3df(160, 0, 0));
        boxNode1->setScale(irr::core::vector3df(3, 3, 3));
        //set up a triangle selector for the box
        selector = smgr->createTriangleSelectorFromBoundingBox(boxNode1);
        boxNode1->setTriangleSelector(selector);
        selector->drop();
    }else{
        cleanUp();
        return EXIT_FAILURE;
    }
    
    //add a box to our scene for something to collide with
    irr::scene::ISceneNode *boxNode2 = smgr->addCubeSceneNode();
    //set up the box
    if(boxNode2){
        boxNode2->setPosition(irr::core::vector3df(370, 0, 60));
        boxNode2->setScale(irr::core::vector3df(3, 3, 3));
        //set up a triangle selector for the box
        selector = smgr->createTriangleSelectorFromBoundingBox(boxNode1);
        boxNode2->setTriangleSelector(selector);
        selector->drop();
    }else{
        cleanUp();
        return EXIT_FAILURE;
    }
    
    //add a box to our scene for something to collide with
    irr::scene::ISceneNode *boxNode3 = smgr->addCubeSceneNode();
    //set up the box
    if(boxNode3){
        boxNode3->setPosition(irr::core::vector3df(350, 0, -70));
        boxNode3->setScale(irr::core::vector3df(3, 3, 3));
        //set up a triangle selector for the box
        selector = smgr->createTriangleSelectorFromBoundingBox(boxNode1);
        boxNode3->setTriangleSelector(selector);
        selector->drop();
    }else{
        cleanUp();
        return EXIT_FAILURE;
    }
    //////////////////////////////////////////////////////////////////////
    
    //create a ship for the player
    PlayerShip player = PlayerShip("/home/pi/piCade/Projects/PiCade/Assets/ship 1 obj.obj", "/home/pi/piCade/Projects/PiCade/Assets/ship 1 obj.mtl", smgr, driver);
    
    //add the boxes into the collibeable vector
    player.addCollideable(boxNode1);
    player.addCollideable(boxNode2);
    player.addCollideable(boxNode3);
    
    //add all objects into the vector
    objectsToUpdate.push_back(&player);
    
    //add a camera to render the scene and give it to the player
    irr::scene::ICameraSceneNode *camera = smgr->addCameraSceneNode();
    player.addCamera(camera);
    
    //set up for frame independent movement
    irr::u32 then = device->getTimer()->getTime();
    
    //main loop
    while(device->run()){
        //work out frame delta time
        const irr::u32 now = device->getTimer()->getTime();
        const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.0f;
        then = now;
        
        //tick(update) all objects
        for(int i = 0; i < objectsToUpdate.size(); i++){
            objectsToUpdate[i]->tick(frameDeltaTime);
        }
        
        //read player input
        if(eReceiver.isKeyDown(irr::KEY_KEY_A)){
            player.turnLeft();
        }else if(eReceiver.isKeyDown(irr::KEY_KEY_D)){
            player.turnRight();
        }
        if(eReceiver.isKeyDown(irr::KEY_SPACE)){
            player.changeMode();
        }
        
        //tell irlicht to draw/updates scenes
        driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
        
        smgr->drawAll();
        
        driver->endScene();
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
    for(int i = 0; i < objectsToUpdate.size(); i++){
        delete objectsToUpdate[i];
    }
    objectsToUpdate.clear();
    objectsToUpdate.resize(0);
}