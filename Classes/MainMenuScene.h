#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dt);

    ui::LoadingBar* musicBar;
    ui::LoadingBar* sfxBar;

    double difficult = 1.0;
    double getDifficult();
    float getMusicVolume();
    float getSFXVolume();

    CREATE_FUNC(MainMenuScene);
private:
    float music = 0.01;
    float sfx = 0.01;

    void musicPlus(cocos2d::Ref* pSender);
    void musicMinus(cocos2d::Ref* pSender);
    void sfxPlus(cocos2d::Ref* pSender);
    void sfxMinus(cocos2d::Ref* pSender);

    void GoToCutScene(cocos2d::Ref* sender);
    void GoToSettings(cocos2d::Ref* sender);
    void GoToMainMenu(cocos2d::Ref* sender);
    void Exit(cocos2d::Ref* sender);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* parallax1;
    cocos2d::Sprite* parallax2;
    cocos2d::Sprite* parallax3;
};

#endif // __MAIN_MENU_SCENE_H__
