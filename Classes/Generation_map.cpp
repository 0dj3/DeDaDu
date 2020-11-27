#include "Generation_map.h"
#include "2d/CCFastTMXLayer.h"
#include "GameScene.h"
USING_NS_CC;


Scene* Generation_map::createScene(Scene* scene)
{
    auto map = Generation_map::create();
    return map;
    
}

bool Generation_map::init() {
    if (!Scene::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    tileMap = TMXTiledMap::create("maps/shop_left.tmx");
    tileMap->setScale(3.0);
    
    
    
    
    return true;
}


void Generation_map::create_main_room() {
    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    //tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));
    GameScene* gamescene;
    gamescene->addChild(tileMap);
}


void Generation_map::create_hall() {
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