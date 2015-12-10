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
    //irr::IrrlichtDevice *nullDevice = irr::createDevice(irr::video::EDT_NULL);
    //irr::core::dimension2d<irr::u32> deskres = nullDevice->getVideoModeList()->getDesktopResolution();
    //nullDevice->drop();

    //Create the device to handle input
    EventReceiver receiver;
    //Create the device the run the game
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600), 16, false, false, false, &receiver);
    //Create the class that will handle the actual playing of the game
    Game game = Game(device, &receiver);

    //Create a texture variable to draw the menu
    irr::video::ITexture *menuScreen = device->getVideoDriver()->getTexture("Assets/PlaceHolders/AsteroidMenu.jpg");
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
    irr::gui::IGUIStaticText *scoreText = device->getGUIEnvironment()->addStaticText(L"Score set up", irr::core::rect<irr::s32>(10, 10, 200, 22));
    scoreText->setVisible(false);
    irr::core::stringw scoreCount(L"Empty");

    //The main loop of the entire program
    while(device->run()){
        //If escape is pressed at any point, break the loop
        if(receiver.isKeyDown(irr::KEY_ESCAPE)){
            device->closeDevice();
        }

        //Start the game when enter is pressed
        if(receiver.isKeyDown(irr::KEY_RETURN)){
            if(gameState == startMenu){
                gameState = gamePlaying;
                menuImage->setVisible(false);
            }
        }
        //Leave score screen when space bar is pressed
        if(receiver.isKeyDown(irr::KEY_BACK)){
            if (gameState == scoreScreen){
                gameState = startMenu;
                menuImage->setVisible(true);
                scoreText->setVisible(false);
            }
        }

        //Begin the scene
        device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

        //Hadle logic depending on the game state
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

