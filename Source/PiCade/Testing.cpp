//see testing.h

#include "Testing.h"

int Testing::runTest(){
    IrrlichtDevice *device = createDevice(EDT_OPENGL, dimension2d<u32>(800, 600), 16, false, false, false, 0);
    if(!device){
        return 1;
    }
    
    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    
    IAnimatedMesh *shipMesh = smgr->getMesh("/home/pi/piCade/Projects/PiCade/Assets/ship 1 obj.obj");
    if(!shipMesh){
        device->drop();
        return 1;
    }
    
    int a = 0;
    int arraySize = 0; //CHANGE THIS TO ADD SHIPS TO THE SCENE
    vector3df shipPosition = vector3df(0, 0, 50);
    IAnimatedMeshSceneNode *shipNodes[arraySize];
    for(int i = 0; i < arraySize; i++){
        shipNodes[i] = smgr->addAnimatedMeshSceneNode(shipMesh);
        shipNodes[i]->setMaterialFlag(EMF_LIGHTING, false);
        if(a > 0){
            shipPosition.X += 80;
            if(a > 7){
                shipPosition.X = 0;
                shipPosition.Z -= 50;
                a = 0;
            }
        }
        shipNodes[i]->setPosition(shipPosition);
        a++;
    }
    
    smgr->addCameraSceneNode(0, vector3df(-100, 50, 0), vector3df(0, -5, 0));
    
    int lastFPS = -1;
    int fps;
    
    while(device->run()){
        driver->beginScene();
        smgr->drawAll();
        driver->endScene();
        
        fps = driver->getFPS();
        if (lastFPS != fps){
            irr::core::stringw tmp(L"testing ");
            tmp += L" FPS: ";
            tmp += fps;
            device->setWindowCaption(tmp.c_str());
            lastFPS = fps;
        }
    }
    
    device->drop();
    
    return 0;
}
