#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <include/rapidjson/ostreamwrapper.h>
#include "include/rapidjson/writer.h"
#include <iostream>
#include <fstream>

USING_NS_CC;

class MainMenuScene : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(Ref* pSender);
    void update(float dt);

    ui::LoadingBar* musicBar;
    ui::LoadingBar* sfxBar;

    double difficult = 1.0;
    double getDifficult();
    float getMusicVolume();
    float getSFXVolume();

    int musicID;
    rapidjson::Document doc;

    CREATE_FUNC(MainMenuScene);
private:
    float music;
    float sfx;

    void musicPlus(Ref* pSender);
    void musicMinus(Ref* pSender);
    void sfxPlus(Ref* pSender);
    void sfxMinus(Ref* pSender);

    void GoToCutScene(Ref* sender);
    void GoToSettings(Ref* sender);
    void GoToMainMenu(Ref* sender);
    void Exit(Ref* sender);

    Size visibleSize;
    Vec2 origin;

    Sprite* parallax1;
    Sprite* parallax2;
    Sprite* parallax3;
};

#endif // __MAIN_MENU_SCENE_H__
