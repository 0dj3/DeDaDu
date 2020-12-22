#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Player.h"
#include "Slime.h"
#include "InputListener.h"
#include "HUD.h"
#include "BossLocation.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>

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
    rapidjson::Document doc;
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    void checkEndRoom();
    void portalInit();
private:
    void update(float dt);
    int countLocation = 0;
    bool checkPortal = false;
    bool checkMap = false;
    cocos2d::PhysicsWorld* sceneWorld;
    std::vector<Unit*> enemies;
    
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    Node* layerMiniMap;
    Sprite* portal;

};

#endif // __GAME_SCENE_H__