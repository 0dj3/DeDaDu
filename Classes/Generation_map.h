#ifndef __MAP_H__
#define __MAP_H__
#include "cocos2d.h"
#include "GameScene.h"

class Generation_map: public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene(Scene* scene);
	
	virtual bool init();
	cocos2d::Scene* scene;
	void create_hall();
	void create_main_room();
	void create_shop();
	void create_room();
private:
	
	cocos2d::TMXTiledMap* tileHall;
	cocos2d::TMXTiledMap* tileMap;
	cocos2d::PhysicsWorld* sceneWorld;
	void SetPhysicsWorld1(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
};

#endif 