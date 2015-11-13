#include <ISceneManager.h>
#include <IAnimatedMeshSceneNode.h>

#include "Object.h"

Object::Object(const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference, bool spawnOnConstruct){
    //default this to false, no object has been spawned yet
    objectSpawned = false;
    
    //if we want the object to be spawned into the scene when the constructor is called (defaulted as true)
    if(spawnOnConstruct){
        spawnObject(pathOfMesh, pathOfTexture, sceneManagerReference, driverReference);
    }
}

Object::~Object(){
    //free memory when the object is deallocated
    clearCollideables();
}

irr::scene::IAnimatedMesh* Object::getMesh(){
    return objectMesh;
}

irr::scene::IAnimatedMeshSceneNode* Object::getSceneNode(){
    return objectNode;
}

void Object::removeFromScene(){
    objectNode->remove();
}

void Object::addCollideable(irr::scene::ISceneNode *collideable){
    collideables.push_back(collideable);
}

void Object::clearCollideables(){
    //make sure the pointers a cleared
    for(int i = 0; i < collideables.size(); i++){
        delete collideables[i];
    }
    
    //then clear the vector
    collideables.clear();
    if(collideables.size() > 0){
        collideables.resize(0);
    }
}

bool Object::checkCollision(){
    if(collideables.size() <= 0){
        return false;
    }
    
    for(int i = 0; i < collideables.size(); i++){
        if(objectNode->getTransformedBoundingBox().intersectsWithBox(collideables[i]->getTransformedBoundingBox())){
            return true;
        }
    }
    
    return false;
}

void Object::updatePosition(irr::core::vector3df newPosition){
    objectNode->setPosition(newPosition);
}

void Object::spawnObject(const irr::io::path &pathOfMesh, const irr::io::path& pathOfTexture, irr::scene::ISceneManager* sceneManagerReference, irr::video::IVideoDriver* driverReference){
    //if the object hasnt been spawned then place it into the scene
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
        
        //set up the object node
        objectPosition = objectNode->getPosition();
        
        objectSpawned = true;
    }
}