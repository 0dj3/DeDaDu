
#ifndef __CUT_SCENE_H__
#define __CUT_SCENE_H__

#include "cocos2d.h"

class CutScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CutScene);

private:
    void GoToGameScene(float dt);

};

#endif // __CUT_SCENE_H__
