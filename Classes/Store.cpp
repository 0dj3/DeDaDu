#include "Store.h"
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
		tray = Sprite::create();
		tray->initWithFile("NPC/store/table.png");
		tray->getTexture()->setAliasTexParameters();
		tray->setScale(3.0);
		tray->setPosition(Vec2((posMap.x + i * 120) - 30, posMap.y - 80));
		this->addChild(tray);

		auto edgeNode = Node::create();
		edgeNode->setScale(2.0);
		edgeNode->setAnchorPoint(Vec2(0.5, 0.5));
		edgeNode->setPosition(tray->getPosition());
		auto body = PhysicHelper::createWallPhysicBody(edgeNode, Size(tray->getContentSize()));
		this->addChild(edgeNode);
		allPhysicTray.push_back(body);

		/*Item* item;
		if (rand() % 2) {
			std::map<std::string, int> stats{
			{"healing", -20 + rand() % 40}
			};
			item = Item::create(Item::POTION, "Potion", "Super potion", "res/items/potion.png", stats);
			item->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
		}
		else {
			std::map<std::string, int> stats{
			{"damage", 1 + rand() % 40},
			{"delay", 1 + rand() % 8}
			};
			item = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/sword.png", stats);
		}
		this->addChild(item);
		item->SellShop(Vec2((posMap.x + i * 120) - 30, posMap.y - 80), 8, 1.0f);
		items.push_back(item);*/
	}
}



TMXTiledMap* Store::getMap() {
	return store;
}

std::vector<b2Body*> Store::getTray() {
	return allPhysicTray;
}