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
    
    void generation();
    void border(cocos2d::TMXTiledMap* tiled);
    void generHall(cocos2d::TMXTiledMap* sizeMap, int direction);
    void generMapOne(cocos2d::TMXTiledMap* sizeMap, int direction);
    void generMainRoom(cocos2d::TMXTiledMap* tiled, int direction);
    void createDoor(cocos2d::TMXTiledMap* tiled, int direction);
    int** generationArrayMap(int sizeMap);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void update(float dt);

    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};

#endif // __GAME_SCENE_H__