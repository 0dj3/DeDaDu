#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dt);

    CREATE_FUNC(MainMenuScene);
private:
    void GoToCutScene(cocos2d::Ref* sender);

    void GoToSettings(cocos2d::Ref* sender);

    void Exit(cocos2d::Ref* sender);

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* parallax1;
    cocos2d::Sprite* parallax2;
    cocos2d::Sprite* parallax3;
};

#endif // __MAIN_MENU_SCENE_H__
