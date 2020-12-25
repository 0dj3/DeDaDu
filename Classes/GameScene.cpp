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
#include "2d/CCFastTMXLayer.h"
#include "MainMenuScene.h"

USING_NS_CC;
CC_DLL;

Scene* GameScene::createScene()
{
    auto layer = GameScene::create();
    layer->scheduleUpdate();
    layer->scene->addChild(layer);
    return layer->scene;
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

    auto scene = Scene::create();
    this->scene = scene;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    InputListener::Instance()->Init(this);
    GameManager::Instance()->Init();

    PhysicHelper::CreateWorld();

    /*std::ifstream ifs("../Resources/properties/data.json");
    rapidjson::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
    auto music = doc["music"].GetFloat();*/
    AudioEngine::play2d("res/sounds/bgsound.mp3", true, GameManager::Instance()->GetMusicVolume());

    visibleSize.height = -1250;
    player = Player::create(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
    /*log("x=%f y=%f", player->body->GetPosition().x, player->body->GetPosition().y);*/

    generation = Generation_map::createScene(checkMap, static_cast<Player*>(player), player->getPosition());
    this->addChild(generation);
    allMainRoom = generation->getAllMapMain();
    setPosPlayerMiniMap();
    barrels = generation->getBarrel();
    for (int i = 0; i < barrels.size(); i++)
        this->addChild(barrels[i]);

    this->addChild(player, 4);
    
    portalInit();

    hud = HUD::create(static_cast<Player*>(player));
    this->addChild(hud, 5);

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
            if (n->getTag() == ContactListener::ENEMY || ContactListener::PLAYER)
                static_cast<Unit*>(b->GetUserData())->DeathRattle();
            if (n->getTag() == ContactListener::PLAYER)
                continue;
            PhysicHelper::world->DestroyBody(b);
            if (n->getTag() == ContactListener::ENEMY) {
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
    if (checkBoss == false) {
        generation->addMiniMap(static_cast<Player*>(player), player->getPosition(), idRoom);
        enemies = generation->checkRoom(player, enemies, checkMap);
        checkEndRoom();
    }if (checkBoss == true) {
        auto enemiesBoss = bosL->getEnemies();
        if (enemiesBoss.size() == 0) {
            /*portal = new Sprite();
            portal->initWithFile("portal/portal.png");

            auto allMapOne = bosL->getlocIn();

            posRoomPortal = allMapOne->getPosition();
            sizeRoomPortal = allMapOne->getMapSize();
            portal->setScale(2.0);
            portal->setPosition(Vec2(posRoomPortal.x + sizeRoomPortal.width * 30, posRoomPortal.y + sizeRoomPortal.height * 30));
            this->addChild(portal);
            checkBoss = false;
            checkPortalF();*/
        }
    }
    /*auto pos = generation->getPosTileMapOneEnd();
    auto sizeEnd = generation->getSizeTileMapOneEnd();
    auto posAX = pos.x + 80;
    auto posAY = pos.y + ((sizeEnd.height - 1) * 60 - 20);
    auto posBX = pos.x + ((sizeEnd.width - 1) * 60 - 20);
    auto posBY = pos.y + 80;
    if (player->getPosition().x >= posAX && player->getPosition().x <= posBX && player->getPosition().y <= posAY && player->getPosition().y >= posBY && checkMap == false && enemies.size() == 0) {
        checkMap = true;
        generation->generation(checkMap);
        player->body->SetTransform(b2Vec2(20.f, -39.f), player->body->GetAngle());
    }*/
    
}

void GameScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
}

void GameScene::checkEndRoom() {
    //testMap
    /*auto posM = generation->getPosTileMapOneEnd();
    auto sizeEndM = generation->getSizeTileMapOneEnd();*/
    auto posM = posRoomPortal;
    auto sizeEndM = sizeRoomPortal;
    auto posAXM = posM.x + 80;
    auto posAYM = posM.y + ((sizeEndM.height - 1) * 60 - 20);
    auto posBXM = posM.x + ((sizeEndM.width - 1) * 60 - 20);
    auto posBYM = posM.y + 80;
    
    if (player->getPosition().x >= posAXM && player->getPosition().x <= posBXM && player->getPosition().y <= posAYM && player->getPosition().y >= posBYM && enemies.size() == 0) {
        
        if (checkPortal == false) {
            portal->setVisible(true);
            checkPortal = true;
        }
        checkPortalF();
        
    }
}

void GameScene::portalInit() {
    portal = new Sprite();
    portal->initWithFile("portal/portal.png");

    auto allMapOne = generation->getAllMapOne();
    int idMap = 0 + rand() % (allMapOne.size() - 1);

    posRoomPortal = allMapOne[idMap]->getPosition();
    sizeRoomPortal = allMapOne[idMap]->getMapSize();
    portal->setScale(2.0);
    portal->setPosition(Vec2(posRoomPortal.x + sizeRoomPortal.width * 30, posRoomPortal.y + sizeRoomPortal.height * 30));
    this->addChild(portal);
    portal->setVisible(false);
}

void GameScene::setPosPlayerMiniMap() {
    allMainRoom = generation->getAllMapMain();
    idRoom = 0 + rand() % (allMainRoom.size() - 1);
    auto roomMainPos = allMainRoom[idRoom]->getPosition();
    auto roomMainSize = allMainRoom[idRoom]->getMapSize() * 30;

    player->body->SetTransform(b2Vec2((roomMainPos.x + roomMainSize.width) / PPM, (roomMainPos.y + roomMainSize.height) / PPM), player->body->GetAngle());
    generation->playerMiniMap = static_cast<Player*>(player);

    generation->miniMap(idRoom);
}

vector<Unit*> GameScene::getEnemies() {
    return enemies;
}

void GameScene::setEnemies(vector<Unit*> enemies) {
    this->enemies = enemies;
}

void GameScene::checkPortalF() {
    auto pos = portal->getPosition();
    auto size = portal->getContentSize();
    auto posAX = pos.x - size.width;
    auto posAY = pos.y + size.height;
    auto posBX = pos.x + size.width;
    auto posBY = pos.y - size.height;
    if (player->getPosition().x >= posAX && player->getPosition().x <= posBX && player->getPosition().y <= posAY && player->getPosition().y >= posBY) {
        checkPortal = false;
        portal->setVisible(false);

        this->removeChild(portal);
        if (countLocation >= 3)
            checkMap = true;
        if (countLocation == 2) {
            BossLocation* bossLoc = new BossLocation();
            generation->cleanScene();
            bosL = bossLoc->createScene("slime", enemies);
            checkBoss = true;
            this->addChild(bosL, 1);
            player->body->SetTransform(b2Vec2(20.f, -39.f), player->body->GetAngle());
        }
        else {
            barrels = generation->getBarrel();
            for (int i = 0; i < barrels.size(); i++)
                    barrels[i]->setName(DEAD_TAG);
            generation->generation(checkMap);
            portalInit();
            setPosPlayerMiniMap();
            barrels = generation->getBarrel();
            for (int i = 0; i < barrels.size(); i++)
                this->addChild(barrels[i]);
        }
        countLocation += 1;
    }
}