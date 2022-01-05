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
#include <DeathScreen.h>

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    Unit* player;
    HUD* hud;
    Unit* slime;
    Generation_map* generation;
    BossLocation* bosL;
    Enemy* enemy;

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
    std::vector<Unit*> getEnemies();
    void setEnemies(std::vector<Unit*> enemies);
    void checkPortalF();
private:
    void update(float dt);
    int countLocation = 1;
    bool checkPortal = false;
    bool checkMap = false;
    bool checkBoss = false;
    bool checkPortalBoss = false;
    cocos2d::PhysicsWorld* sceneWorld;
    std::vector<Unit*> enemies;
    vector<Unit*> barrels;
    int asPortal = 1;
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    Node* layerMiniMap;
    Sprite* portal;
    Vec2 posRoomPortal;
    Size sizeRoomPortal;
    std::vector<TMXTiledMap*> allMainRoom;
    int idRoom = 0;

    void setPosPlayerMiniMap();
};

#endif // __GAME_SCENE_H__