#include "GameScene.h"
#include "Definitions.h"
#include "Player.h"
#include "Slime.h"
#include "Goblin.h"
#include "2d/CCFastTMXLayer.h"
#include "AudioEngine.h"
//#include "Generation_map.h"

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
    AudioEngine::play2d("res/sounds/bgsound.mp3", true, 0.1f);
    generation();


    player = Player::create(this, Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(player);
    
    slime = Slime::create(this, Point(player->getPosition().x, player->getPosition().y + 100));
    this->addChild(slime);

    auto goblin = Goblin::create(this, Point(player->getPosition().x + 100, player->getPosition().y + 100));
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

    b2Body* node = PhysicHelper::world->GetBodyList();
    while (node)
    {
        b2Body* b = node;
        node = node->GetNext();

        if (b->GetUserData() == nullptr)
            continue;
            
        Unit* unit = (Unit*)b->GetUserData();
        if (unit->IsDead())
        {
            PhysicHelper::world->DestroyBody(b);
            unit->removeFromParentAndCleanup(true);
        }
    }

    for (b2Body* b = PhysicHelper::world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition(Vec2(b->GetPosition().x * PPM, b->GetPosition().y * PPM));
            myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}


void GameScene::generation() {
    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    tileMap->setAnchorPoint(Point(0, 0));
    this->addChild(tileMap);
    border(tileMap);
    
    //direction = 1;//["down"] 
    //direction = 2;//["up"]
    //direction = 3;//["right"]
    //direction = 4;//["left"] 

    generHall(tileMap, 1);
    //generMainRoom(tileHall, 1);
    generHall(tileMap, 4);
    //generMainRoom(tileHall, 4);
    generHall(tileMap, 3);
    generHall(tileMap, 2);
    //generMainRoom(tileHall, 2);
    
    //generMainRoom(tileHall, 3);
    for (int i = 0; i < 3; i++)
        generMainRoom(tileHall, 2);

    generMapOne(tileHall, 2);
    
}

void GameScene::border(TMXTiledMap* tiled) {
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

void GameScene::generHall(TMXTiledMap* PosMap, int direction) {
    auto MapX = PosMap->getPosition().x;
    auto MapY = PosMap->getPosition().y;
    
    switch (direction)
    {
    case 1://down
        tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
        tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (-tileHall->getMapSize().height) * 60));
        
        generMapOne(tileHall, direction);
        break;
    case 2://up
        tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
        tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (PosMap->getMapSize().height) * 60));
        //player->setPosition(tileHall->getPosition());
        //generMapOne(tileHall, direction);
        break;
    case 3://right
        tileHall = TMXTiledMap::create("maps/hall_horizont.tmx");
        tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height / 6.5) * 60));
        generMapOne(tileHall, direction);
        
        break;
    case 4://left
        tileHall = TMXTiledMap::create("maps/hall_horizont.tmx");
        tileHall->setPosition(Point(MapX + (- tileHall->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height / 6.5) * 60));
        
        generMapOne(tileHall, direction);
        break;
    default:
        break;
    }

    tileHall->setScale(3.0);
    tileHall->setAnchorPoint(Point(0, 0));
    border(tileHall);
    this->addChild(tileHall);
}

void GameScene::generMapOne(TMXTiledMap* PosMap, int direction) {
    auto sizeMapX = PosMap->getPosition().x;
    auto sizeMapY = PosMap->getPosition().y;

    switch (direction)
    {
    case 1://down
        tileMapOne = TMXTiledMap::create("maps/room_down.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (-tileMapOne->getMapSize().height) * 60));
        break;
    case 2://up
        tileMapOne = TMXTiledMap::create("maps/room_up.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (PosMap->getMapSize().height) * 60));
        break;
    case 3://right
        tileMapOne = TMXTiledMap::create("maps/room_right.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 11) * 60));
        //tileMapOne->setPosition(Point(sizeMapX + (tileMapOne->getMapSize().width) * 60, sizeMapX + (PosMap->getMapSize().height - 4) * 60));
        break;
    case 4://left
        tileMapOne = TMXTiledMap::create("maps/room_left.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (-tileMapOne->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height- 11) * 60));
        break;
    default:
        break;
    }
    tileMapOne->setAnchorPoint(Point(0, 0));
    tileMapOne->setScale(3.0);
    border(tileMapOne);
    this->addChild(tileMapOne);
}

void GameScene::generMainRoom(TMXTiledMap* PosMap, int direction) {
    tileMainRoom = TMXTiledMap::create("maps/main_room.tmx");
    auto sizeMapX = PosMap->getPosition().x;
    auto sizeMapY = PosMap->getPosition().y;
    int check;
    switch (direction)
    {
    case 1://down
        tileMainRoom->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 8) * 60, sizeMapY + (-tileMainRoom->getMapSize().height) * 60));
        check = 2;
        break;
    case 2://up
        tileMainRoom->setPosition(Point(0, 5 * 60 + PosMap->getPosition().y));
        check = 1;
        break;
    case 3://right
        tileMainRoom->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));
        check = 4;
        break;
    case 4://left
        tileMainRoom->setPosition(Point(sizeMapX + (-tileMainRoom->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));
        check = 3;
        break;
    default:
        break;
    }


    for (int i = 1; i < 5; i++)
        if (i != check)
            generHall(tileMainRoom, i);
    generHall(tileMainRoom, 2);
    tileMainRoom->setAnchorPoint(Point(0, 0));
    tileMainRoom->setScale(3.0);
    border(tileMainRoom);
    
    this->addChild(tileMainRoom);
}