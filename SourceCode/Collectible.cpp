#include "Collectible.h"

#include "Game.h"

Collectible::Collectible(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, spawnPosition, TYPE_COLLECTABLE, true){

    //set the rotation speed
    rotSpeed = 75.0f;

	//Used by the static text
	animateText = false;
	textPos = irr::core::vector2di(0);
	scene = sceneManagerReference;

	//Set the collision manager
	collMan = sceneManagerReference->getSceneCollisionManager();

	//Create a prticle effect around the collectible
	ps = sceneManagerReference->addParticleSystemSceneNode(false, getSceneNode());
	//Set up an emitter for the system to use
	irr::scene::IParticleEmitter* em = ps->createPointEmitter(
		irr::core::vector3df(0.0f, 0.01f, 0.0f),			// direction, also acts as speed
		5U, 10U,											// emit rate
		irr::video::SColor(0, 255, 255, 255),				// darkest color
		irr::video::SColor(0, 255, 255, 255),				// brightest color
		500, 1000, 0,										// min and max age, angle
		irr::core::dimension2df(5.0f, 5.0f),				// min size
		irr::core::dimension2df(10.0f, 10.0f));				// max size
	
	ps->setEmitter(em); //Give the emitter to the system
	em->drop();			//Safe to drop now we don't need it

	//Add change the materials of the particle system
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture("Assets/PlaceHolders/particlegreen.jpg"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

	//Resize all collectibles, might be temp
	getSceneNode()->setScale(irr::core::vector3df(2));

	//Init the audio device
	pickupSFX = audiere::OpenSound(audiereDevice, "Assets/Sound/Pickup.mp3");

	soundStarted = false;
	actionPefromed = false;
}

Collectible::~Collectible(){
	if(animatedText){
		animatedText->remove();
	}
}

void Collectible::tick(irr::f32 deltaTime){
    //Make the collectable rotate
    updateRotation(0, rotSpeed * deltaTime, 0);
	//Wait for the sound to stop before deleting
	if(soundStarted){
		if(!pickupSFX->isPlaying()){
			markForDelete();
		}
	}
	//Move the text upwards
	if(animateText){
		textPos.Y--;
		animatedText->setRelativePosition(textPos);
	}
}

void Collectible::activate(PlayerShip *player){
	if(!actionPefromed){
		pickupSFX->play();
		performAction(player);
		getSceneNode()->setVisible(false);
		actionPefromed = true;
		soundStarted = true;
	}
}

void Collectible::displayText(const int &amount, const irr::core::stringw &text, const irr::core::vector3df &playerPos){
	//Set the value of the text
	irr::core::stringw displayText;
	displayText += "+";
	displayText += amount;
	displayText += " ";
	displayText += text;
	//Change the length of the box
	float length = displayText.size() * 22;

	//Convert the player pos to screen coordinates
	textPos = collMan->getScreenCoordinatesFrom3DPosition(playerPos);

	//Init the variable
	animatedText = scene->getGUIEnvironment()->addStaticText(displayText.c_str(), irr::core::rect<irr::s32>(0, 0, length, 30));

	//Center the text
	textPos.X -= animatedText->getAbsolutePosition().getWidth() / 2;

	//Make sure to animate it
	animateText = true;
}


