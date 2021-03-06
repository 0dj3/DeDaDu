#pragma once
#include <cocos2d.h>
#include "2d/CCFastTMXLayer.h"
#include "PhysicHelper.h"
#include "Item.h"
USING_NS_CC;

class Store : public Node {
public:
	static Store* createScene(TMXTiledMap* map);
	TMXTiledMap* getMap();
	std::vector<b2Body*> getTray();
	void createTray(TMXTiledMap* storeMap, int count);
	std::vector<Item*> getItems();
private:
	bool init(TMXTiledMap* map);
	TMXTiledMap* store;
	TMXTiledMap* MapOne;
	Sprite* sprite;
	Sprite* shopMan;
	Sprite* tray;

	std::vector<b2Body*> allPhysicTray;
	std::vector<Item*> items;
};
