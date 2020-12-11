#include "Store.h"
#include <ctime>
USING_NS_CC;

Store* Store::createScene() {
	Store* store = new Store();
	store->init();
	return store;
}

bool Store::init() {
	Generation_map* gener = new Generation_map();
	allMapOne = gener->getAllMainMap();
	int storeLoc = 2 + rand() % (allMapOne.size() - 2);
	auto posMap = allMapOne[storeLoc]->getPosition();
	auto sizeMap = allMapOne[storeLoc]->getMapSize();

	store = TMXTiledMap::create("maps/store.tmx");
	store->setScale(3.0);
	store->setAnchorPoint(Vec2(1, 1));
	store->setPosition(Vec2(posMap.x + (sizeMap.width / 2 * 60), posMap.y + (sizeMap.height / 2 * 60)));

	this->addChild(store);
	return true;
}