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
#include "MainMenuScene.h"
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

    MainMenuScene* settings = new MainMenuScene;
    AudioEngine::play2d("res/sounds/bgsound.mp3", true, settings->getMusicVolume());
    
    

    visibleSize.height = -1250;
    player = Player::create(this, Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    
    /*log("x=%f y=%f", player->body->GetPosition().x, player->body->GetPosition().y);*/

    generation = Generation_map::createScene(checkMap, static_cast<Player*>(player), player->getPosition());
    this->addChild(generation);
    this->addChild(player);

   /* hud = HUD::create(static_cast<Player*>(player));
    this->addChild(hud, 5);

    slime = Slime::create(this, Point(player->getPosition().x, player->getPosition().y + 100));
    this->addChild(slime, 2);
    enemies.push_back(slime);*/

    //
    //char str1[200] = { 0 };
    //auto spritecache1 = SpriteFrameCache::getInstance();
    //spritecache1->addSpriteFramesWithFile("res/enemy/goblin/goblin.plist");
    //auto spritesheet1 = SpriteBatchNode::create("res/enemy/goblin/goblin.png");
    //this->addChild(spritesheet1);

    //Vector<SpriteFrame*> idleAnimFrames1(4);
    //for (int i = 1; i <= 6; i++) {
    //    sprintf(str1, "idle_%i.png", i);
    //    idleAnimFrames1.pushBack(spritecache1->getSpriteFrameByName(str1));
    //}
    //auto idleAnimation1 = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    //auto demo1 = Sprite::createWithSpriteFrameName("idle_1.png");
    //demo1->setPosition(Point(player->getPosition().x + 100, player->getPosition().y - 100)); //Retain to use it later
    //demo1->setScale(3.0);
    //Action* action1 = RepeatForever::create(Animate::create(idleAnimation1));
    //demo1->runAction(action1);
    //spritesheet1->addChild(demo1);
    //
    /*auto fly = Fly::create(this, Point(player->getPosition().x - 100, player->getPosition().y + 100));
    this->addChild(fly, 2);
    enemies.push_back(fly);

    auto goblin = Goblin::create(this, Point(player->getPosition().x + 100, player->getPosition().y + 100), static_cast<Player*>(player));
    this->addChild(goblin, 2);
    enemies.push_back(goblin);*/

    /*auto portalEnd = Portal::create();
    portalEnd->setPosition(player->getPosition());
    portalEnd->setScale(0.1);
    this->addChild(portalEnd);*/

    //removeChild(layerMiniMap, true);

    /*layerMiniMap = generation->miniMap(static_cast<Player*>(player), player->getPosition());
    this->addChild(layerMiniMap);*/

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

        Node* n = (Node*)b->GetUserData();
        if (n->getName() == DEAD_BODY_TAG)
        {
            PhysicHelper::world->DestroyBody(b);
            continue;
        }

        //Unit* unit = (Unit*)b->GetUserData();
        if (n->getName() == DEAD_TAG)
        {
            PhysicHelper::world->DestroyBody(b);
            if (n->getTag() == ContactListener::ENEMY) {
                Enemy::DropItems(n->getPosition());
                for (int i = 0; i < enemies.size(); i++) {
                    if (enemies[i] == n) {
                        enemies.erase(enemies.begin() + i);
                        break;
                    }
                }
            }
            
            n->removeFromParentAndCleanup(true);
        }
    }

    for (b2Body* b = PhysicHelper::world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            Sprite* myActor = (Sprite*)b->GetUserData();
            myActor->setPosition(Vec2(b->GetPosition().x * PPM, b->GetPosition().y * PPM));
        }
    }
    enemies = generation->checkRoom(player, enemies, checkMap);
    //testMap
    auto pos = generation->getPosTileMapOneEnd();
    auto sizeEnd = generation->getSizeTileMapOneEnd();
    auto posAX = pos.x + 80;
    auto posAY = pos.y + ((sizeEnd.height - 1) * 60 - 20);
    auto posBX = pos.x + ((sizeEnd.width - 1) * 60 - 20);
    auto posBY = pos.y + 80;
    if (player->getPosition().x >= posAX && player->getPosition().x <= posBX && player->getPosition().y <= posAY && player->getPosition().y >= posBY && checkMap == false && enemies.size() == 0) {
        checkMap = true;
        generation->generation(checkMap);
        player->body->SetTransform(b2Vec2(20.f, -39.f), player->body->GetAngle());
    }

    generation->addMiniMap(static_cast<Player*>(player), player->getPosition());
}

void GameScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
}
