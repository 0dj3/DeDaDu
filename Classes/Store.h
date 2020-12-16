#pragma once
#include <cocos2d.h>
#include "2d/CCFastTMXLayer.h"
#include "PhysicHelper.h"
#include "Item.h"
USING_NS_CC;

class Store : public Node {
public:
	static Store* createScene(TMXTiledMap* map, int countMap);
	TMXTiledMap* getMap();
	void createTray(TMXTiledMap* storeMap, int count);
private:
	bool init(TMXTiledMap* map, int countMap);
	TMXTiledMap* store;
	TMXTiledMap* MapOne;
	Sprite* sprite;
	Sprite* shopMan;
	Sprite* tray;

	std::vector<b2Body*> allPhysicTray;
	std::vector<Item*> items;
};
