
#ifndef __DEATH_SCREEN_H__
#define __DEATH_SCREEN_H__

#include "cocos2d.h"

class DeathScreen : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(DeathScreen);

private:
    void GoToMainMenuScene(float dt);

};

#endif // __DEATH_SCREEN_H__
