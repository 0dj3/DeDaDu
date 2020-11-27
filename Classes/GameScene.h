#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
#include "cocos2d.h"
#include "Player.h"
#include "Slime.h"
#include "InputListener.h"



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

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::TMXTiledMap* tileHall;
    cocos2d::TMXTiledMap* tileMapOne;
    cocos2d::TMXTiledMap* tileMainRoom;
    cocos2d::Node* edgeNode;
    
    void update(float dt);

    cocos2d::PhysicsWorld* sceneWorld;

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };

};

#endif // __GAME_SCENE_H__
