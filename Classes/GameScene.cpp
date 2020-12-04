#include "GameScene.h"
#include "Definitions.h"
#include "Player.h"
#include "Slime.h"
#include "Fly.h"
#include "HUD.h"
#include "Goblin.h"
#include "2d/CCFastTMXLayer.h"
#include "AudioEngine.h"
#include <ctime>
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
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    InputListener::Instance()->Init(this);

    PhysicHelper::CreateWorld();
    AudioEngine::play2d("res/sounds/bgsound.mp3", true, 0.1f);
    
    generation = Generation_map::createScene();
    this->addChild(generation);

    player = Player::create(this, Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(player);

    hud = HUD::create();
    this->addChild(hud, 5);

    slime = Slime::create(this, Point(player->getPosition().x, player->getPosition().y + 100));
    this->addChild(slime);

    //
    char str1[200] = { 0 };
    auto spritecache1 = SpriteFrameCache::getInstance();
    spritecache1->addSpriteFramesWithFile("res/enemy/goblin/goblin.plist");
    auto spritesheet1 = SpriteBatchNode::create("res/enemy/goblin/goblin.png");
    this->addChild(spritesheet1);

    Vector<SpriteFrame*> idleAnimFrames1(4);
    for (int i = 1; i <= 6; i++) {
        sprintf(str1, "idle_%i.png", i);
        idleAnimFrames1.pushBack(spritecache1->getSpriteFrameByName(str1));
    }
    auto idleAnimation1 = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    auto demo1 = Sprite::createWithSpriteFrameName("idle_1.png");
    demo1->setPosition(Point(player->getPosition().x + 100, player->getPosition().y - 100)); //Retain to use it later
    demo1->setScale(3.0);
    Action* action1 = RepeatForever::create(Animate::create(idleAnimation1));
    demo1->runAction(action1);
    spritesheet1->addChild(demo1);
    //
    auto fly = Fly::create(this, Point(player->getPosition().x - 100, player->getPosition().y + 100));
    this->addChild(fly);

    auto goblin = Goblin::create(this, Point(player->getPosition().x + 100, player->getPosition().y + 100));
    this->addChild(goblin);

    return true;
}

void GameScene::update(float dt)
{
    hud->updatePos(player);
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

        Weapon* weapon = (Weapon*)b->GetUserData();
        if (weapon->getName() == "weapon" && !weapon->isActive)
        {
            PhysicHelper::world->DestroyBody(b);
            continue;
        }

        Unit* unit = (Unit*)b->GetUserData();
        if (unit->getName() == "unit" && unit->IsDead())
        {
            PhysicHelper::world->DestroyBody(b);
            unit->removeFromParentAndCleanup(true);
        }
    }

    for (b2Body* b = PhysicHelper::world->GetBodyList(); b; b = b->GetNext())
    {
        Node* weapon = (Node*)b->GetUserData();
        if (b->GetUserData() != NULL && weapon->getName() == "weapon")
        {
            continue;
        }
        if (b->GetUserData() != NULL) {
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition(Vec2(b->GetPosition().x * PPM, b->GetPosition().y * PPM));
            //myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
