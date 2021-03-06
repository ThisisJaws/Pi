#include "Object.h"
#include "Game.h"

//Init static member here - 0 is reserved for no collision, 1 is reserved for terrain
irr::s32 Object::objectCount = 2;

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, const irr::core::vector3df &spawnPos, const irr::s32 &objectTypeID, const bool &checkCollisionFromBoundingBox){
	//Make the ID of the object the current object count
	uniqueID = objectCount;
	//Increment the object count when the ID has been used
	objectCount++;
	
	//set the ID of the object
    typeID = objectTypeID;

	sceneMan = sceneManagerReference;

    //set the spawn position
    this->spawnPos = spawnPos;

    //Dont want it to get deleted straight away
    markedForDelete = false;
	deleteReady = false;

	//Make sure the collisionManager points to nothing
	collMan = 0;

	//load the mesh
	objectMesh = sceneManagerReference->getMesh(pathOfMesh);

	//create the scene node using loaded mesh
	objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh, NULL, uniqueID, spawnPos);
	objectNode->setMaterialTexture(0, sceneManagerReference->getVideoDriver()->getTexture(pathOfTexture));

	//Create a triangle selector of this object
	irr::scene::ITriangleSelector *selector;
	if(checkCollisionFromBoundingBox){
		selector = sceneManagerReference->createTriangleSelectorFromBoundingBox(objectNode);
	} else{
		selector = sceneManagerReference->createTriangleSelector(objectNode);
	}
	//Give the node the newly created selector
	objectNode->setTriangleSelector(selector);
	//Drop the selector to remove it from memory
	selector->drop();

	//Create a reference to the collision Manager, to use when the collision function is called
	collMan = sceneManagerReference->getSceneCollisionManager();

	//Make sure it has been initialised
	animatedText = 0;

	//Used by the static text
	animateText = false;
	textPos = irr::core::vector2di(0);
	animTimePast = 0;

	moveAway = false;
	awaySpeed = 0;

	//Add this object onto the update vector
	Game::addObjectToUpdate(this);
}

Object::~Object(){
	if(animatedText){
		animatedText->remove();
	}
}

void Object::tick(irr::f32 deltaTime){
	//Move the text upwards
	if(animateText){
		textPos.Y -= ceil(deltaTime) * 1;
		animatedText->setRelativePosition(textPos);
		if(animTimePast > ANIMATE_TIME){
			animatedText->remove();
			animatedText = NULL;
			animTimePast = 0;
			animateText = false;
		} else{
			animTimePast += deltaTime;
		}
	} else{
		//Check if the object is ready to be deleted
		if(markedForDelete){
			deleteReady = true;
		}
	}

	//Move away from player 
	if(moveAway){
		updatePosition(0, 0, awaySpeed * deltaTime);
	}
}

bool Object::isMarkedForDelete(){
    return markedForDelete && deleteReady;
}

void Object::markForDelete(){
    markedForDelete = true;
	objectNode->setVisible(false);
}

irr::s32 Object::getTypeID(){
	return typeID;
}

signed int Object::getUniqueID(){
	return uniqueID;
}

irr::scene::IAnimatedMesh* Object::getMesh(){
    return objectMesh;
}

irr::scene::IAnimatedMeshSceneNode* Object::getSceneNode(){
    return objectNode;
}

irr::core::vector3df Object::getPosition(){
    return objectNode->getPosition();
}

irr::s32 Object::checkCollision(int direction){
	//Cast a ray from the object to slightly infront of the object
	irr::core::line3df ray;
	ray.start = getPosition();
	ray.end = ray.start;
	ray.end.Z += direction * 20;
	//Current interection of a level or a mesh
	irr::core::vector3df interesection;
	//The triangle that was hit
	irr::core::triangle3df hitTriangle;

	//Perform the ray cast and return the scene node
	irr::scene::ISceneNode *objectTest = collMan->getSceneNodeAndCollisionPointFromRay(ray, interesection, hitTriangle);
	
	if(objectTest != NULL && objectTest != objectNode){
		return objectTest->getID();
	} else{
		return 0;
	}
}

void Object::updatePosition(const irr::core::vector3df &newPosition){
    objectNode->setPosition(getPosition() + newPosition);
}

void Object::updatePosition(const float &x, const float &y, const float &z){
	updatePosition(irr::core::vector3df(x, y, z));
}

void Object::changePosition(const irr::core::vector3df &newPosition){
	objectNode->setPosition(newPosition);
}

irr::core::vector3df Object::getRotation(){
	return objectNode->getRotation();
}

void Object::updateRotation(const irr::core::vector3df &angle){
	objectNode->setRotation(getRotation() + angle);
}

void Object::updateRotation(const float &x, const float &y, const float & z){
	updateRotation(irr::core::vector3df(x, y, z));
}

void Object::changeRotation(const irr::core::vector3df &angle){
	objectNode->setRotation(angle);
}

void Object::removeFromScene(){
    objectNode->remove();
}

void Object::moveAwayFromPlayer(const bool &move, const float &playerSpeed){
	moveAway = move;
	if(playerSpeed > 0){
		awaySpeed = playerSpeed * 0.3f; //Make the away speed 30% of the players
	}
}


void Object::displayText(const irr::core::stringw &text, const irr::core::vector3df &worldPos, const int &amount){
	//Set the value of the text
	irr::core::stringw displayText;
	if(amount > 0){
		displayText += "+";
		displayText += amount;
	}
	displayText += " ";
	displayText += text;
	//Change the length of the box
	float length = (float)displayText.size() * 22;

	//Convert the player pos to screen coordinates
	textPos = collMan->getScreenCoordinatesFrom3DPosition(worldPos);

	//Init the variable
	animatedText = sceneMan->getGUIEnvironment()->addStaticText(displayText.c_str(), irr::core::rect<irr::s32>(0, 0, (irr::s32)length, 30));

	//Center the text
	textPos.X -= animatedText->getAbsolutePosition().getWidth() / 2;

	//Make sure to animate it
	animateText = true;
}
