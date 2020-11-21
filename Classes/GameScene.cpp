#include "GameScene.h"
#include "Definitions.h"
#include "Player.h"
#include "Slime.h"
#include "Goblin.h"
#include "2d/CCFastTMXLayer.h"
#include "Generation_map.h"
#include "AudioEngine.h"

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
    layer->scheduleUpdate();
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

    InputListener::Instance()->Init(this);

    PhysicHelper::CreateWorld();
    AudioEngine::play2d("bgsound.mp3", true, 0.1f);
    generation();
    

    player = Player::create(this, Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    //player->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(player);

    slime = Slime::create(this, Point(player->getPosition().x, player->getPosition().y + 100));
    slime->setTag(2);
    this->addChild(slime);

    auto goblin = Goblin::create(this, Point(player->getPosition().x + 100, player->getPosition().y + 100));
    goblin->setTag(2);
    this->addChild(goblin);


    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
            CC_CALLBACK_1(GameScene::menuCloseCallback, this);
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
    //----Close button
    /*auto closeItem = MenuItemImage::create( "pause_button.png", "pause_button_press.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(visibleSize.width, visibleSize.height));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    return true;
}

void GameScene::update(float dt)
{
    int velocityIterations = 6;
    int positionIterations = 2;

    PhysicHelper::world->Step(dt, velocityIterations, positionIterations);

    for (b2Body* b = PhysicHelper::world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition(Vec2(b->GetPosition().x, b->GetPosition().y));
            myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
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
    tileMap->setAnchorPoint(Point(0, 0));
    //tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));
    this->addChild(tileMap);
    border(tileMap);
    
    //direction = 1;//["down"] 
    //direction = 2;//["up"]
    //direction = 3;//["right"]
    //direction = 4;//["left"] 

    generHall(tileMap->getPosition(), 0.0f, 1);
    generHall(tileMap->getPosition(), 0.0f, 2);
    generHall(tileMap->getPosition(), 90.0f, 4);
    generHall(tileMap->getPosition(), 90.0f, 3);
    

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
                edgeNode = Node::create();
                /*auto edgeBody = PhysicsBody::createBox(Size(Y.size), PHYSICSBODY_MATERIAL_DEFAULT);
                edgeBody->setDynamic(false);
                edgeNode->setPhysicsBody(edgeBody);*/
                edgeNode->setScale(2.0);
                edgeNode->setAnchorPoint(Vec2(0.5, 0.5));
                edgeNode->setPosition((PositionTile + Vec2(10, 10)) * 3 + tiled->getPosition());
                log("%f %f", edgeNode->getContentSize().width, edgeNode->getContentSize().height);
                PhysicHelper::createWallPhysicBody(edgeNode, Size(Y.size));
                this->addChild(edgeNode);
            }
        }
    }
}

void GameScene::generHall(Vec2 PosMap, float rotation, int direction) {
    auto MapX = PosMap.x;
    auto MapY = PosMap.y;
    if (rotation == 0.0f)
        tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
    else tileHall = TMXTiledMap::create("maps/hall_horizont.tmx");
    
    tileHall->setAnchorPoint(Point(0, 0));
    
    switch (direction)
    {
    case 1://down
        tileHall->setPosition(Point((MapX + tileMap->getMapSize().width / 5) * 60, (MapY - tileHall->getMapSize().height) * 60) /*+ Vec2(100, 200)*/);
        break;
    case 2://up
        tileHall->setPosition(Point((MapX + tileMap->getMapSize().width / 5) * 60, (MapY + tileMap->getMapSize().height) * 60) /*+ Vec2(100, 200)*/);
        break;
    case 3://right
        tileHall->setPosition(Point((MapX + tileMap->getMapSize().width) * 60, (MapY + tileMap->getMapSize().height / 6.5) * 60));
        break;
    case 4://left
        tileHall->setPosition(Point((MapX - tileHall->getMapSize().width) * 60, (MapY + tileMap->getMapSize().height / 6.5) * 60));
        break;
    default:
        break;
    }

    tileHall->setScale(3.0);
    generMapOne(tileHall, rotation - 90.0f, direction);
    border(tileHall);
    this->addChild(tileHall);
}

void GameScene::generMapOne(TMXTiledMap* PosMap, float rotation, int direction) {
    auto sizeMapX = PosMap->getMapSize().width;
    auto sizeMapY = PosMap->getMapSize().height;
    tileMapOne = TMXTiledMap::create("maps/room_right.tmx");
    tileMapOne->setAnchorPoint(Point(0, 0));

    switch (direction)
    {
    case 1://down
        tileMapOne->setPosition(Point(sizeMapX, +sizeMapY - tileMap->getMapSize().height * 41.5));
        break;
    case 2://up
        tileMapOne->setPosition(Point(sizeMapX, +sizeMapY + tileMap->getMapSize().height * 41.5));
        break;
    case 3://right
        tileMapOne->setPosition(Point(sizeMapX * 60 + PosMap->getPosition().x, -3 * 60 + PosMap->getPosition().y));
        tileMapOne->setRotation(rotation);
        tileMapOne->setScale(3.0);
        border(tileMapOne);
        this->addChild(tileMapOne);
        break;
    case 4://left
        tileMapOne->setPosition(Point(PosMap->getPosition().x, +11 * 60 + PosMap->getPosition().y));
        tileMapOne->setRotation(rotation - 180.0f);
        tileMapOne->setScale(3.0);
        border(tileMapOne);
        this->addChild(tileMapOne);
        break;
    default:
        break;
    }

    
}