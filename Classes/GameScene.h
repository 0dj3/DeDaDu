#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
    Unit* player;

    static cocos2d::Scene* createScene();

    virtual bool init();

    void Update();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::TMXLayer* background;

    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};

#endif // __GAME_SCENE_H__
