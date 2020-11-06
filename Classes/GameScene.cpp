#include "GameScene.h"
#include "Definitions.h"
#include "Player.h"
#include "Slime.h"
#include "2d/CCFastTMXLayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    auto layer = GameScene::create();
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

    tileMap = TMXTiledMap::create("maps/main_room.tmx");
    tileMap->setScale(3.0);
    tileMap->setPosition(Point(visibleSize.width / 4 + origin.x + 20, visibleSize.height / 4 - 80));
    this->addChild(tileMap);

    player = Player::create(this);
    player->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(player);

    slime = Slime::create(this);
    slime->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30));
    this->addChild(slime);

   
    auto edgeBody = PhysicsBody::createEdgeBox(Size(580, 700), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    auto closeItem = MenuItemImage::create( "pause_button.png", "pause_button_press.png", CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(visibleSize.width-280, visibleSize.height-60));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    return true;
}

void GameScene::Update()
{

}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
