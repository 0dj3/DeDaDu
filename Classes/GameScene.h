#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Player.h"
#include "Slime.h"
#include "InputListener.h"

USING_NS_CC;
#define SIZE_MAP 5;

class GameScene : public cocos2d::Layer
{
public:
    Unit* player;

    Unit* slime;

    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Scene* scene;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void generation();
    void border(cocos2d::TMXTiledMap* tiled);
    void generHall(cocos2d::TMXTiledMap* sizeMap, int direction);
    void generMapOne(cocos2d::TMXTiledMap* sizeMap, int direction);
    void generMainRoom(cocos2d::TMXTiledMap* tiled, int direction);
    void createDoor(cocos2d::TMXTiledMap* tiled, int direction);
    int** generationArrayMap(int sizeMap);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    TMXTiledMap* tileMap;
    TMXTiledMap* tileHallML;
    TMXTiledMap* tileHallMR;
    TMXTiledMap* tileHallMU;
    TMXTiledMap* tileHall;
    TMXTiledMap* tileMapOne;
    TMXTiledMap* tileMainRoom;
    Node* edgeNode;
    int** arrayMap;
    int checkI = 1, sizeMap = 5;
    int checkj;
    void update(float dt);

    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};

#endif // __GAME_SCENE_H__