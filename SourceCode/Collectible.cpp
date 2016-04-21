#include "Collectible.h"

#include "Game.h"

//static members
sf::SoundBuffer *Collectible::pickupBuff;
int Collectible::buffCount = 0;
Collectible::Collectible(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference)
        : Object(pathOfMesh, pathOfTexture, sceneManagerReference, spawnPosition, TYPE_COLLECTABLE, true){

    //set the rotation speed
    rotSpeed = 75.0f;

	//Create a prticle effect around the collectible
	ps = sceneManagerReference->addParticleSystemSceneNode(false, getSceneNode());
	//Set up an emitter for the system to use
	irr::scene::IParticleEmitter* em = ps->createBoxEmitter(
		irr::core::aabbox3df(-7, -7, -7, 7, 7, 7),			// size of the box to emit from
		irr::core::vector3df(0.0f, 0.03f, 0.0f),			// direction, also acts as speed
		3U, 6U,												// emit rate
		irr::video::SColor(0, 255, 255, 255),				// darkest color
		irr::video::SColor(0, 255, 255, 255),				// brightest color
		1800, 1800, 0,										// min and max age, angle
		irr::core::dimension2df(3.0f, 3.0f),				// min size
		irr::core::dimension2df(5.0f, 5.0f));				// max size
	
	ps->setEmitter(em); //Give the emitter to the system
	em->drop();			//Safe to drop now we don't need it

	//Add change the materials of the particle system
	ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	ps->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture("Assets/Particles/ship flame small red.png"));
	ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);

	ps->setParticlesAreGlobal(false);

	//Set the aduio
	if(pickupBuff == NULL){
		pickupBuff = new sf::SoundBuffer();
		pickupBuff->loadFromFile("Assets/Sound/PickUp/Pickup.wav");
	}
	pickUp.setBuffer(*pickupBuff);
	buffCount++;

	actionPefromed = false;
}

Collectible::~Collectible(){
	buffCount--;
	if(buffCount <= 0){
		delete pickupBuff;
		pickupBuff = 0;
	}
}

void Collectible::tick(irr::f32 deltaTime){
	Object::tick(deltaTime);
    //Make the collectable rotate
    updateRotation(0, rotSpeed * deltaTime, 0);
}

void Collectible::activate(PlayerShip *player){
	if(!actionPefromed){
		pickUp.play();
		performAction(player);
		markForDelete();
		actionPefromed = true;
	}
}


