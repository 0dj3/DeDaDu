#include "BossLocation.h"
#include "Store.h"

BossLocation* BossLocation::createScene(string name) {
	BossLocation* location = new BossLocation();
	location->cleanScene();
	location->init();
	location->name = name;
	return location;
}

bool BossLocation::init() {
	locIn = TMXTiledMap::create("maps/boss_location1.tmx");
	locIn->setScale(3.0);
	border(locIn);
	generMapOne(locIn, 1, false);
	//Store* store = Store::createScene()
	return true;
}