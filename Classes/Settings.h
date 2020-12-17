#ifndef __SETTINGS_H__
#define __SETTINGS_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "ui/CocosGUI.h"
#include "Unit.h"

USING_NS_CC;

class Settings : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Settings);
    ui::LoadingBar* musicBar;
    ui::LoadingBar* sfxBar;
    double difficult = 1.0;
    double getDifficult();

    float getMusicVolume();
    float getSFXVolume();

private:
    float music = 0.01;
    float sfx = 0.01;
    void musicPlus(cocos2d::Ref* pSender);
    void musicMinus(cocos2d::Ref* pSender);
    void sfxPlus(cocos2d::Ref* pSender);
    void sfxMinus(cocos2d::Ref* pSender);
    void GoToMainMenuScene(cocos2d::Ref* pSender);
    void update(float dt);
};


#endif // __SETTINGS_H__
