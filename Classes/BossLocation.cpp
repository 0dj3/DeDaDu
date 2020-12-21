#include "BossLocation.h"

BossLocation* BossLocation::createScene(string name) {
	BossLocation* location = new BossLocation();
	location->cleanScene();
	location->init();
	location->name = name;
	return location;
}

bool BossLocation::init() {
	locIn->create("maps/boss_location1.tmx");
	locIn->setScale(3.0);
	border(locIn);
	return true;
}