#include "Store.h"
USING_NS_CC;

Store* Store::createScene(TMXTiledMap* map, int countMap) {
	Store* store = new Store();
	store->init(map, countMap);
	return store;
}

bool Store::init(TMXTiledMap* map, int countMap) {
	auto posMap = map->getPosition();
	auto sizeMap = map->getMapSize();

	store = TMXTiledMap::create("maps/store.tmx");
	store->setScale(3.0);
	store->setAnchorPoint(Vec2(1, 1));
	store->setPosition(Vec2(posMap.x + (sizeMap.width / 2 * 60), posMap.y + (sizeMap.height / 2 * 60)));

	this->addChild(store);
	return true;
}