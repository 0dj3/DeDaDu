#ifndef __CUT_SCENE_H__
#define __CUT_SCENE_H__

#include "cocos2d.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <include/rapidjson/ostreamwrapper.h>
#include "include/rapidjson/writer.h"
#include <iostream>
#include <fstream>

class CutScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CutScene);
    rapidjson::Document doc;
private:
    void GoToGameScene(float dt);
    int progress;
    char* str;
    
};

#endif // __CUT_SCENE_H__
