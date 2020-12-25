#include "BossLocation.h"
#include "Store.h"

BossLocation* BossLocation::createScene(string name, vector<Unit*> enemies, Player* player) {
	BossLocation* location = new BossLocation();
	location->slimeking = new SlimeKing();
	location->name = name;
	location->playerGL = player;
	location->enemies = enemies;
	location->init();
	location->scheduleUpdate();
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
	auto items = store->getItems();
	for (int i = 0; i < items.size(); i++)
		this->addChild(items[i]);


	auto storeMap = store->getMap();
	border(storeMap);

	auto posBoss = Vec2(locIn->getPosition().x + locIn->getMapSize().width * 30, locIn->getPosition().y + locIn->getMapSize().height * 30);
	auto boss = addBoss(posBoss);
	this->addChild(boss);



	return true;
}

void BossLocation::update(float dt) {
	time += dt;
	if (time >= 1) {
		countBoss = slimeking->checkDeath;
		if (countBoss != 0 && checkDoor == false) {
			auto posPX = playerGL->getPosition().x;
			auto posPY = playerGL->getPosition().y;

			auto sizeMap = locIn->getMapSize();
			auto posMap = locIn->getPosition();

			auto posAX = posMap.x + 80;
			auto posAY = posMap.y + ((sizeMap.height - 1) * 60 - 20);
			auto posBX = posMap.x + ((sizeMap.width - 1) * 60 - 20);
			auto posBY = posMap.y + 80;

			if (posPX >= posAX && posPX <= posBX && posPY <= posAY && posPY >= posBY) {
				auto sizeMap = locIn->getMapSize();
				auto posMap = locIn->getPosition();
				createDoor(locIn, 1, false, true);
				checkDoor = true;
			}
		}
		else {
			if (checkDoor == true && countBoss == 0) {

				for (int i = 0; i < PhBoDoorRoom.size(); i++)
					PhysicHelper::world->DestroyBody(PhBoDoorRoom[i]);
				PhBoDoorRoom.clear();

				for (int i = 0; i < childDoorRoom.size(); i++) 
					this->removeChild(childDoorRoom[i], true);
				childDoorRoom.clear();
				bossDeath = true;
				checkDoor = false;
			}
		}
		time = 0;
	}
	
}

Enemy* BossLocation::addBoss(Point pos) {
	boss = slimeking->create(pos, static_cast<Player*>(playerGL), 3);
	return boss;
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

//void BossLocation::cleanScene() {
//	this->removeAllChildren();
//	for (int i = 0; i < Director::getInstance()->getRunningScene()->getChildren().size(); i++) {
//		if (Director::getInstance()->getRunningScene()->getChildren().at(i)->getTag() != ContactListener::PLAYER)
//			Director::getInstance()->getRunningScene()->getChildren().at(i)->setName(DEAD_TAG);
//	}
//}