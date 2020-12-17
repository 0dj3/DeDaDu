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
};

#endif // __MAIN_MENU_SCENE_H__
