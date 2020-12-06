#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Player.h"
#include "Slime.h"
#include "InputListener.h"
#include "HUD.h"
#include "Generation_map.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    Unit* player;
    HUD* hud;
    Unit* slime;
    Generation_map* generation;

    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Scene* scene;
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void update(float dt);
    bool checkMap = true;
    cocos2d::PhysicsWorld* sceneWorld;
    std::vector<Unit*> enemies;
    
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};

#endif // __GAME_SCENE_H__