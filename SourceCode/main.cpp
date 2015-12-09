/*
 * Check the make file for the executable target name/directory
 * click build then run the executable from there
 *
 * make sure to include all source files in the makefile!!!
 */

#include "irrlicht.h"

#include "Game.h"
#include "EventReceiver.h"

//so it can work on windows
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

/*
 * program entry point
 */
int main(int argc, char** argv) {
    //Create a null device to get the desktop res
    irr::IrrlichtDevice *nullDevice = irr::createDevice(irr::video::EDT_NULL);
    irr::core::dimension2d<irr::u32> deskres = nullDevice->getVideoModeList()->getDesktopResolution();
    nullDevice->drop();

    //Create the device to handle input
    EventReceiver receiver;
    //Create the device the run the game
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OGLES1, deskres, 32, true, false, true, &receiver);
    //Create the class that will handle the actual playing of the game
    Game game = Game(device, &receiver);

    //Create a texture variable to draw the menu
    //irr::video::ITexture *menuScreen = device->getVideoDriver()->getTexture("Assets/PlaceHolders/AsteroidMenu.jpg");

    //Create a camera to use
    irr::scene::ICameraSceneNode *camera = device->getSceneManager()->addCameraSceneNode();

    //Create the sky box
    device->getSceneManager()->addSkyBoxSceneNode(device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                                  device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                                  device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                                  device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                                  device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"),
                                                  device->getVideoDriver()->getTexture("Assets/PlaceHolders/TestSkyBox.jpg"));

    //The main loop of the entire program
    while(device->run()){
        //If escape is pressed at any point, break the loop
        if(receiver.isKeyDown(irr::KEY_ESCAPE)){
            device->closeDevice();
        }

        //Load and start the game when enter is pressed
        if(receiver.isKeyDown(irr::KEY_RETURN) && !game.isLoaded()){
            game.load(camera);
        }

        //Begin the scene
        device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        if(game.isLoaded()){
            //Update the game
            game.play();
        }else{
            //Draw menu graphic
            //device->getVideoDriver()->draw2DImage(device->getVideoDriver()->getTexture("Assets/PlaceHolders/AsteroidMenu.jpg"), irr::core::position2d<irr::s32>(0, 0));
        }
        //Draw everything
        device->getSceneManager()->drawAll();
        device->getGUIEnvironment()->drawAll();

        //End the scene
        device->getVideoDriver()->endScene();
    }

    //Drop the device to end the program
    device->drop();

    //create a game object - everything gets initialised in the constructor
    //Game currentGame = Game();

	//bool exit = false;

	//do{
	//	exit = currentGame.play();
	//} while(!exit);

    //once the loop breaks go straight to clean up (for now)
    //currentGame.cleanUp();

    //once the 'play' loop has ended then exit program
    return 0;
}

