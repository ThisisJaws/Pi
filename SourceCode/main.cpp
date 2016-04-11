/*
 * Check the make file for the executable target name/directory
 * click build then run the executable from there
 *
 * make sure to include all source files in the makefile!!!
 */

#include "irrlicht.h"

#include "Game.h"
#include "ScoreScreen.h"
#include "EventReceiver.h"

//so it can work on windows
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

//Defines for version number
#define CURRENT_VERSION_MAJOR	 0
#define CURRENT_VERSION_MINOR	 10
#define CURRENT_VERSION_REVISION 0

/*
 * program entry point
 */
int main(int argc, char** argv) {
    //Create the device to handle input
    EventReceiver receiver;
    
	//Create the device the run the game
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600), 16, false, true, false, &receiver);
    
	//Force all textures to be 16 bit
	device->getVideoDriver()->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, true);
	
	//Create the class that will handle the actual playing of the game
    Game game = Game(device, &receiver);
	
	//Create the score class which will handle all of the score
	ScoreScreen score = ScoreScreen(device->getGUIEnvironment());
	
	//Keep track if the player has entered their name
	bool nameEntered = false;

	//Change the window name
	irr::core::stringw windowName(L"Space Trip: ");
	windowName += CURRENT_VERSION_MAJOR; windowName += "."; windowName += CURRENT_VERSION_MINOR; windowName += "."; windowName += CURRENT_VERSION_REVISION;
	device->setWindowCaption(windowName.c_str());

    //Create a texture variable to draw the menu
    irr::video::ITexture *menuScreen = device->getVideoDriver()->getTexture("Assets/PlaceHolders/AsteroidMenu800x600.jpg");
    //Add the texture to the gui
    irr::gui::IGUIImage *menuImage = device->getGUIEnvironment()->addImage(menuScreen, irr::core::position2d<irr::s32>(0, 0));

	//Create a gui image for the score screen
	irr::gui::IGUIImage *scoreImage = device->getGUIEnvironment()->addImage(device->getVideoDriver()->getTexture("Assets/Scoreboard.jpg"), irr::core::position2d<irr::s32>(0, 0));
	scoreImage->setVisible(false);
	//Set the right drawing order
	scoreImage->getParent()->sendToBack(scoreImage);

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

        //Begin the scene
        device->getVideoDriver()->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

		//Wait on the start menu
		if(gameState == startMenu){
			if(receiver.isKeyPressed(irr::KEY_RETURN)){
				gameState = gamePlaying;
				menuImage->setVisible(false);
				/*mainMusic->stop();
				buttonPress->play();*/
			}
		}
		//Update the game if it is playing
		if(gameState == gamePlaying){
			if(!game.isLoaded()){
				game.load(camera);
			}
			if(game.play()){ //play() will be true when the game is over
				//Set and display the scores
				gameState = scoreScreen;
				scoreImage->setVisible(true);
				score.displayScore(true);
				score.addScore(game.getFinalScore());
			}
		}
		//Update the score screen
		if(gameState == scoreScreen){
			//Wait for the player to enter their name
			if(score.waitForPlayerName(&receiver, device->getTimer()->getRealTime())){
				//When the player is done entering their name, wait to go back to start
				if(receiver.isKeyPressed(irr::KEY_RETURN)){
					gameState = startMenu;
					menuImage->setVisible(true);
					score.displayScore(false);
					score.reset();
					scoreImage->setVisible(false);
				}
			}
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

