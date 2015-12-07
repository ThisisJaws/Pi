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

    //Create a font variable to draw text
    irr::gui::IGUIFont *font = device->getGUIEnvironment()->getBuiltInFont();

    //Create a camera to use
    device->getSceneManager()->addCameraSceneNode();

    //The main loop of the entire program
    while(device->run()){
        //If escape is pressed at any point, break the loop
        if(receiver.isKeyDown(irr::KEY_ESCAPE)){
            device->closeDevice();
        }

        //Begin the scene
        device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        //Update the game
        //game.play();

        //Set up the text for the main menu
        font->draw(L"TEST", irr::core::rect<irr::s32>(10, 10, 200, 22), irr::video::SColor(255, 255, 255, 255));

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

