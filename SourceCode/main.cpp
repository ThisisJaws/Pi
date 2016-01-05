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

//Defines for version number
#define CURRENT_VERSION_MAJOR	 0
#define CURRENT_VERSION_MINOR	 3
#define CURRENT_VERSION_REVISION 2

/*
 * program entry point
 */
int main(int argc, char** argv) {
	//Resolution for the pi
	//irr::core::dimension2d<irr::s32> piRes(1280, 720);

    //Create the device to handle input
    EventReceiver receiver;
    //Create the device the run the game
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600), 16, false, false, false, &receiver);
    //Create the class that will handle the actual playing of the game
    Game game = Game(device, &receiver);

	//Change the window name
	irr::core::stringw windowName(L"Space Trip Version: ");
	windowName += CURRENT_VERSION_MAJOR;
	windowName += ".";
	windowName += CURRENT_VERSION_MINOR;
	windowName += ".";
	windowName += CURRENT_VERSION_REVISION;
	device->setWindowCaption(windowName.c_str());

    //Create a texture variable to draw the menu
    irr::video::ITexture *menuScreen = device->getVideoDriver()->getTexture("Assets/PlaceHolders/AsteroidMenu800x600.jpg");
    //Add the texture to the gui
    irr::gui::IGUIImage *menuImage = device->getGUIEnvironment()->addImage(menuScreen, irr::core::position2d<irr::s32>(0, 0));

    //Create a camera to use
    irr::scene::ICameraSceneNode *camera = device->getSceneManager()->addCameraSceneNode();

    //enum to keep track of game states
    enum state{
        startMenu,
        gamePlaying,
        scoreScreen
    } gameState;
    gameState = startMenu;

    //Show the player's score
    irr::gui::IGUIStaticText *scoreText = device->getGUIEnvironment()->addStaticText(L"Score set up", irr::core::rect<irr::s32>(10, 10, 600, 40));
    scoreText->setVisible(false);
    irr::core::stringw scoreCount(L"Empty");

    //The main loop of the entire program
    while(device->run()){
        //If escape is pressed at any point, break the loop
        if(receiver.isKeyDown(irr::KEY_ESCAPE)){
			//Make sure to clean up the game if it has been loaded
			if(game.isLoaded()){
				gameState = startMenu;
				game.cleanUp();
			}

            device->closeDevice();
        }

        //Start the game when enter is pressed
        if(receiver.isKeyPressed(irr::KEY_RETURN)){
            if(gameState == startMenu){
                gameState = gamePlaying;
                menuImage->setVisible(false);
            }else if(gameState == scoreScreen){
				gameState = startMenu;
				menuImage->setVisible(true);
				scoreText->setVisible(false);
			}
        }

        //Begin the scene
        device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        //Handle logic depending on the game state
        switch(gameState){
            case startMenu:
                //Start menu logic
                break;
            case gamePlaying:
                if(!game.isLoaded()){
                    game.load(camera);
                }
                if(game.play()){
                    gameState = scoreScreen;
                    scoreText->setVisible(true);
                }
                break;
            case scoreScreen:
                scoreCount = L"Final Score: ";
                scoreCount += game.getFinalScore();
                scoreText->setText(scoreCount.c_str());
                break;

            default:
                break;
        }

        //Draw everything
        device->getSceneManager()->drawAll();
        device->getGUIEnvironment()->drawAll();

        //End the scene
        device->getVideoDriver()->endScene();

		//Update the keyStates
		receiver.endOfLoop();
    }

    //Drop the device to end the program
    device->drop();

    return 0;
}

