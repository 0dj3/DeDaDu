#include "BossLocation.h"
#include "Store.h"

BossLocation* BossLocation::createScene(string name, vector<Unit*> enemies) {
	BossLocation* location = new BossLocation();
	location->cleanScene();
	location->init();
	location->scheduleUpdate();
	location->name = name;
	location->enemies = enemies;
	return location;
}

bool BossLocation::init() {
	locIn = TMXTiledMap::create("maps/boss_location1.tmx");
	mapMain = TMXTiledMap::create("maps/main_room.tmx");
	hallUp = TMXTiledMap::create("maps/hall_vertical.tmx");
	hallRight = TMXTiledMap::create("maps/hall_horizont.tmx");
	mapOne = TMXTiledMap::create("maps/room_right.tmx");

	locIn->setScale(3.0);
	mapMain->setScale(3.0);
	hallUp->setScale(3.0);
	hallRight->setScale(3.0);
	mapOne->setScale(3.0);

	locIn->setPosition(Vec2(-300, 0));
	hallUp->setPosition(Vec2(locIn->getPosition().x + (locIn->getMapSize().width / 2 - hallUp->getMapSize().width / 2) * 60, locIn->getPosition().y - hallUp->getMapSize().height * 60));
	mapMain->setPosition(Vec2(hallUp->getPosition().x + (hallUp->getMapSize().width / 2 - mapMain->getMapSize().width / 2) * 60, hallUp->getPosition().y - mapMain->getMapSize().height * 60));
	hallRight->setPosition(Vec2(mapMain->getPosition().x + mapMain->getMapSize().width * 60, mapMain->getPosition().y + (mapMain->getMapSize().height / 2 - hallRight->getMapSize().height / 2) * 60));
	mapOne->setPosition(Vec2(hallRight->getPosition().x + hallRight->getMapSize().width * 60, hallRight->getPosition().y + (hallRight->getMapSize().height / 2 - mapOne->getMapSize().height / 2) * 60));

	border(locIn);
	border(mapMain);
	border(hallUp);
	border(hallRight);
	border(mapOne);

	this->addChild(locIn);
	this->addChild(mapMain);
	this->addChild(hallUp);
	this->addChild(hallRight);
	this->addChild(mapOne);

	createDoor(mapMain, 1, false, false);
	createDoor(mapMain, 3, false, false);

	Store* store = Store::createScene(mapOne);
	this->addChild(store);
	auto storeMap = store->getMap();
	border(storeMap);

	auto posBoss = Vec2(locIn->getPosition().x + locIn->getMapSize().width * 30, locIn->getPosition().y + locIn->getMapSize().height * 30);
	auto boss = addBoss(posBoss);
	this->addChild(boss);

	return true;
}

void BossLocation::update(float dt) {
	time += dt;

	/*log("time=%f", time);
	if (time >= 5) {
		if (enemies.size() != 0) {
			time = 0;
			int rX = ((locIn->getMapSize().width - 3) * 60);
			int rY = ((locIn->getMapSize().height - 3) * 60);

			int randomX = (locIn->getPosition().x + 100) + rand() % rX;
			int randomY = (locIn->getPosition().y + 80) + rand() % rY;
			addBoss(Point(randomX, randomY));
		}
	}*/
}

Enemy* BossLocation::addBoss(Point pos) {
	auto enemy = Slime::create(this, pos);
	enemies.push_back(enemy);
	return enemy;
}

TMXTiledMap* BossLocation::getPosRoom() {
	return BossLocation::mapMain;
}

vector<Unit*> BossLocation::getEnemies() {
	return enemies;
}

TMXTiledMap* BossLocation::getlocIn() {
	return 	locIn;
}