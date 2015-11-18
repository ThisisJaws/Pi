#include <ISceneManager.h>
#include <IAnimatedMeshSceneNode.h>

#include "Object.h"

//static variables need to be defined outside of the class so the lniker knows where to allocate the memory
std::list<irr::scene::ISceneNode*> Object::collideables;

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct){
    //default this to false, no object has been spawned yet
    objectSpawned = false;
    
    //if we want the object to be spawned into the scene when the constructor is called (defaulted as true)
    if(spawnOnConstruct){
        spawnObject(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference);
    }
}

Object::~Object(){
    //remove the object from the collideables list
    for(std::list<irr::scene::ISceneNode*>::iterator nodeIterator = collideables.begin(); nodeIterator != collideables.end(); ++nodeIterator){
        if((*nodeIterator) == objectNode){
            nodeIterator = collideables.erase(nodeIterator);
        }
    }
    
    
    //remove from scene
    objectNode->remove();
    
    //delete pointers
    //delete objectNode;
    //delete objectMesh;
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

void Object::removeFromScene(){
    objectNode->remove();
}

void Object::addCollideable(irr::scene::ISceneNode *collideable){
    collideables.push_back(collideable);
}

bool Object::checkCollision(){
    //if we don't have any collideables then return straight away
    if(collideables.size() <= 0){
        return false;
    }

    //loop through and return true if any object has collided
    for(std::list<irr::scene::ISceneNode*>::iterator nodeIterator = collideables.begin(); nodeIterator != collideables.end(); ++nodeIterator){
        if(*nodeIterator != objectNode){
            if(objectNode->getTransformedBoundingBox().intersectsWithBox((*nodeIterator)->getTransformedBoundingBox())){
                return true;
            } 
        }
    }
    
    return false;
}

void Object::updatePosition(irr::core::vector3df newPosition){
    objectNode->setPosition(getPosition() + newPosition);
}

void Object::updatePosition(float x, float y, float z){
    irr::core::vector3df temp = irr::core::vector3df(x, y, z);
    updatePosition(temp);
}

void Object::changePosition(irr::core::vector3df newPosition){
    objectNode->setPosition(newPosition);
}

void Object::spawnObject(const irr::io::path &pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference){
    //if the object hasn't been 'spawned' then place it into the scene
    if(!objectSpawned){
        //load the mesh
        objectMesh = sceneManagerReference->getMesh(pathOfMesh);
        
        //create the scene node using loaded mesh
        objectNode = sceneManagerReference->addAnimatedMeshSceneNode(objectMesh);
        //objectNode->setMaterialTexture(0, driverReference->getTexture(pathOfTexture));
    
        //create a triangle selector for collision
        irr::scene::ITriangleSelector *selector = sceneManagerReference->createTriangleSelector(objectNode);
        objectNode->setTriangleSelector(selector);
        selector->drop();
        
        //set the object to not need lighting
        objectNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        
        //let other objects collision test against this object
        addCollideable(objectNode);
        
        objectSpawned = true;
    }
}