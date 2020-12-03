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
    double difficult = 1.0;
    float sounds = 0.1f;

private:
    void GoToMainMenuScene(cocos2d::Ref* sender);
};


#endif // __SETTINGS_H__
