
#ifndef __DEATH_SCREEN_H__
#define __DEATH_SCREEN_H__

#include "cocos2d.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <include/rapidjson/ostreamwrapper.h>
#include "include/rapidjson/writer.h"
#include <iostream>
#include <fstream>

class DeathScreen : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(DeathScreen);

    void GoToMainMenuScene(float dt);
    rapidjson::Document doc;
    
private:
    int progress;
    char* str;

};

#endif // __DEATH_SCREEN_H__
