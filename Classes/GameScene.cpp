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
    /*Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();*/

    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    tileMap->setAnchorPoint(Point(0.5, 0.5));
    //tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));
    
    int direction;
    direction = 1;//["down"] 
    direction = 2;//["up"]
    direction = 3;//["right"]
    direction = 4;//["left"] 

    generHall(tileMap->getPosition(), 0.0f, 1);
    generHall(tileMap->getPosition(), 0.0f, 2);
    generHall(tileMap->getPosition(), 90.0f, 3);
    generHall(tileMap->getPosition(), 90.0f, 4);


    auto sizeMapXA = tileHallHor->getPositionX();
    auto sizeMapYA = tileHallHor->getPositionY();

    tileMapRight= TMXTiledMap::create("maps/room_right.tmx");
    tileMapRight->setAnchorPoint(Point(0.5, 0.5));
    tileMapRight->setPosition(Point(sizeMapXA + tileMap->getMapSize().width * 45, sizeMapYA - (tileMap->getMapSize().height)));
    tileMapRight->setScale(3.0);


    auto kol = 0;
    Sprite* kol1;

    auto layerCheck = tileMap->getLayer("check");
    int sizeXMap = tileMap->getMapSize().width / 2;
    auto ID = layerCheck->getTileGIDAt(Vec2(0, 7));
       

    this->addChild(tileMap);
    //this->addChild(tileMapRight);

    /*border(tileHall);
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
                auto Y = layerCheck->getTileAt(Vec2(i, j))->getTextureRect();
                auto edgeBody = PhysicsBody::createEdgeBox(Size(Y.size), PHYSICSBODY_MATERIAL_DEFAULT, 3);
                
                auto edgeNode = Node::create();
               
                edgeNode->setPosition(PositionTile * 3);
                edgeNode->setPhysicsBody(edgeBody);
                edgeNode->setScale(3.0);
                edgeNode->setAnchorPoint(Point(0.5, 0.5));
                this->addChild(edgeNode);
            }
        }
    }
}

void GameScene::generHall(Vec2 sizeMap, float rotation, int direction) {
    auto sizeMapX = sizeMap.x;
    auto sizeMapY = sizeMap.y;
    tileHallHor = TMXTiledMap::create("maps/hall_vertical.tmx");
    tileHallHor->setAnchorPoint(Point(0.5, 0.5));
    
    switch (direction)
    {
    case 1://down
        tileHallHor->setPosition(Point(sizeMapX, +sizeMapY - tileMap->getMapSize().height * 41.5));
        break;
    case 2://up
        tileHallHor->setPosition(Point(sizeMapX, +sizeMapY + tileMap->getMapSize().height * 41.5));
        break;
    case 3://right
        tileHallHor->setPosition(Point(sizeMapX + tileMap->getMapSize().width * 45, sizeMapY - (tileMap->getMapSize().height / 20 * 45)));
        break;
    case 4://left
        tileHallHor->setPosition(Point(sizeMapX - tileMap->getMapSize().width * 45, sizeMapY - (tileMap->getMapSize().height / 20 * 45)));
        break;
    default:
        break;
    }
    tileHallHor->setScale(3.0);
    tileHallHor->setRotation(rotation);
    this->addChild(tileHallHor);
}