#include "GameScene.h"
#include "Definitions.h"
#include "Player.h"
#include "Slime.h"
#include "2d/CCFastTMXLayer.h"
#include "Generation_map.h"

USING_NS_CC;
CC_DLL;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    auto layer = GameScene::create();
    layer->scene = scene;
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    generation();
    

    player = Player::create(this);
    //player->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(player);

    slime = Slime::create(this, player);
    slime->setTag(2);
    //slime->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100));
    this->addChild(slime);

    //----Close button
    /*auto closeItem = MenuItemImage::create( "pause_button.png", "pause_button_press.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(visibleSize.width, visibleSize.height));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


void GameScene::generation() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    tileMap->setAnchorPoint(Point(0.5, 0.5));
    //tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));


    tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
    tileHall->setScale(3.0);
    auto sizeMapX = tileMap->getPositionX();
    auto sizeMapY = tileMap->getPositionY();
    tileHall->setAnchorPoint(Point(0.5, 0.5));
    tileHall->setPosition(Point(sizeMapX, +sizeMapY  - tileMap->getMapSize().height * 41.5));
    

    tileHallHor = TMXTiledMap::create("maps/hall_horizont.tmx");
    tileHallHor->setAnchorPoint(Point(0.5, 0.5));
    tileHallHor->setPosition(Point(sizeMapX + tileMap->getMapSize().width * 45, sizeMapY - (tileMap->getMapSize().height / 20 * 45)));
    tileHallHor->setScale(3.0);




    auto kol = 0;
    Sprite* kol1;

    auto layerCheck = tileMap->getLayer("check");
    int sizeXMap = tileMap->getMapSize().width / 2;
    auto ID = layerCheck->getTileGIDAt(Vec2(0, 7));


    auto layerHall = tileHall->getLayer("background");


    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) == 125) {
                kol++;
                kol1 = layerCheck->getTileAt(Vec2(i, j));
                auto sizeHallll = kol1->getTextureRect();

                auto edgeBody = PhysicsBody::createEdgeBox(Size(sizeHallll.size * 3), PHYSICSBODY_MATERIAL_DEFAULT, 3);
                auto edgeNode = Node::create();
                edgeNode->setAnchorPoint(Point(0.5, 0.5));
                edgeNode->setPosition(kol1->getPosition());
                edgeNode->setPhysicsBody(edgeBody);
                this->addChild(edgeNode);
            }
        }
    }

    auto sizeasd = tileHall->getPosition();
    

    

   
    this->addChild(tileMap);
    this->addChild(tileHall);
    this->addChild(tileHallHor);

   /* border(tileHall);
    border(tileMap);
    border(tileHallHor);*/

}


void GameScene::border(TMXTiledMap* tiled) {
    //auto layerCheck = tiled->getLayer("walls");
    auto layerCheck = tiled->getLayer("walls");
    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                /*auto X = layerCheck->getTileAt(Vec2(i, j))->getPosition().x;*/
                auto PositionTile = layerCheck->getTileAt(Vec2(i, j))->getPosition();
                auto Y = layerCheck->getTileAt(Vec2(i, j))->getPosition();
                auto edgeBody = PhysicsBody::createEdgeBox(Size(Y), PHYSICSBODY_MATERIAL_DEFAULT, 3);
                
                auto edgeNode = Node::create();
               
                edgeNode->setPosition(tiled->getPosition() + PositionTile * 3);
                edgeNode->setPhysicsBody(edgeBody);
                edgeNode->setScale(3.0);
                edgeNode->setAnchorPoint(Point(0.5, 0.5));
                this->addChild(edgeNode);
            }
        }
    }
}
