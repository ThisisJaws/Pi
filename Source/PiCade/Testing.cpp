//see testing.h

#include "Testing.h"

int Testing::runTest(){
    IrrlichtDevice *device = createDevice(EDT_BURNINGSVIDEO, dimension2d<u32>(800, 600), 16, false, false, false, 0);
    if(!device){
        return 1;
    }
    
    IVideoDriver *driver = device->getVideoDriver();
    ISceneManager *smgr = device->getSceneManager();
    
    IAnimatedMesh *testMesh = smgr->getMesh("Assets/Ships/PlayerShip.obj");
    if(!testMesh){
        device->drop();
        return 1;
    }
        
    int arraySize = 1;      //CHANGE THIS TO ADD SHIPS TO THE SCENE
    int xOffSet = 0;       //CHANGE THIS TO THE LENGTH OF THE SHIPS
    int zOffSet = 0;       //CHNAGE THIS TO THE WIDTH OF THE SHIPS
    
    int a = 0;
    vector3df nodePosition = vector3df(0, 0, zOffSet);
    IAnimatedMeshSceneNode *testMeshNodes[arraySize];
    for(int i = 0; i < arraySize; i++){
        testMeshNodes[i] = smgr->addAnimatedMeshSceneNode(testMesh);
        testMeshNodes[i]->setMaterialTexture(0, driver->getTexture("Assets/Ships/PlayerShipTexture.bmp"));
        testMeshNodes[i]->setMaterialFlag(EMF_LIGHTING, false);
        if(a > 0){
            nodePosition.X += xOffSet;
            if(a > 7){
                nodePosition.X = 0;
                nodePosition.Z -= zOffSet;
                a = 0;
            }
        }
        testMeshNodes[i]->setPosition(nodePosition);
        a++;
    }
    
    smgr->addCameraSceneNode(0, vector3df(-130, 50, 0), vector3df(0, 0, 0));
    
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
