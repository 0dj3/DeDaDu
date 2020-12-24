#include "Store.h"
#include <Weapon.h>
#include <Potion.h>
USING_NS_CC;

Store* Store::createScene(TMXTiledMap* map) {
	Store* store = new Store();
	store->init(map);
	return store;
}

bool Store::init(TMXTiledMap* map) {
	auto posMap = map->getPosition();
	auto sizeMap = map->getMapSize();

	store = TMXTiledMap::create("maps/store.tmx");
	store->setScale(3.0);
	store->setPosition(Vec2(posMap.x + ((sizeMap.width / 2 - 2) * 60), posMap.y + ((sizeMap.height / 2 + 1) * 60)));

	this->addChild(store);

	shopMan = new Sprite();
	shopMan->initWithFile("NPC/store/shopMan.png");
	shopMan->getTexture()->setAliasTexParameters();
	shopMan->setPosition(Vec2(store->getPosition().x + 100, store->getPosition().y + 100));
	shopMan->setScale(2.5);
	this->addChild(shopMan);

	createTray(store, 3);

	return true;
}

void Store::createTray(TMXTiledMap* storeMap, int count) {
	auto posMap = storeMap->getPosition();
	
	for (int i = 0; i < count; i++) {
		Item* item;
		if (rand() % 2) {
			item = Weapon::GetRandomWeapon();
		}
		else {
			item = Potion::create("res/items/red_potion.png", "res/sounds/swoosh.mp3", rand() % 30 - 30);
		}
		Director::getInstance()->getRunningScene()->addChild(item);
		item->Sell(Vec2((posMap.x + i * 120) - 30, posMap.y - 80), rand() % 5 + 10);
	}
}



TMXTiledMap* Store::getMap() {
	return store;
}

std::vector<b2Body*> Store::getTray() {
	return allPhysicTray;
}