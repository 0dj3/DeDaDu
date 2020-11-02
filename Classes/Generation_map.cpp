#include "Generation_map.h"
#include "2d/CCFastTMXLayer.h"
#include "Definitions.h"

USING_NS_CC;

bool Generation_map::init() {
	return 1;
}

void Generation_map::create_hall() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));
    this->addChild(tileMap);

    auto layer = tileMap->getLayer("walls");
    auto gid = layer->getTileAt(Vec2(0, 0));
    auto asd = Size(gid->getPosition());


	tileHall = TMXTiledMap::create("maps/hall.tmx");
    tileHall->setScale(3.0);
    tileHall->setPosition(asd);
    this->addChild(tileHall);

    auto size_hall = tileHall->getPosition();
    auto size_map = tileMap->getPosition();

}