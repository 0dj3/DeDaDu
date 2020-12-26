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
        scene->addChild(barrels[i], 3);

    this->addChild(player, 4);
    
    portalInit();

    hud = HUD::create(static_cast<Player*>(player));
    this->addChild(hud, 5);

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

        if (n->getName() == DEAD_TAG)
        {
            if ((n->getTag() == ContactListener::ENEMY) || (n->getTag() == ContactListener::PLAYER))
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
        if (bosL->countBoss == 0 && bosL->bossDeath == true ) {
            if (checkPortalBoss == false) {
                if (bosL->name == "Goblin") {
                    this->scheduleOnce(CC_SCHEDULE_SELECTOR(DeathScreen::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
                }
                else {
                    portal = new Sprite();
                    portal->initWithFile("portal/portal.png");
                    auto allMapOne = bosL->getlocIn();
                    posRoomPortal = allMapOne->getPosition();
                    sizeRoomPortal = allMapOne->getMapSize();
                    portal->setScale(2.0);
                    portal->setPosition(Vec2(posRoomPortal.x + sizeRoomPortal.width * 30, posRoomPortal.y + sizeRoomPortal.height * 30));
                    this->addChild(portal, 2);
                    checkPortalBoss = true;
                }
            }
            checkPortalF();
        }
    }
}

void GameScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
}

void GameScene::checkEndRoom() {
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
    auto idR = 0 + rand() % (allMainRoom.size() - 1);
    idRoom = (allMainRoom.size() - 1) - idR;
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

        

        auto lvlBoss1 = 2;
        auto lvlBoss2 = 5;
        //enemy->statsScale(countLocation);

        if (countLocation == (lvlBoss1 + 1) || countLocation == (lvlBoss2 + 1)) {
            checkBoss = false;
            checkPortalBoss = false;
            bosL->unscheduleUpdate();
            bosL->cleanScene();
            bosL->stopAllActions();
        }
            
        if (countLocation >= (lvlBoss1 + 1)) {
            checkMap = true;
        }

        if (countLocation == lvlBoss1) {
            generation->cleanScene();
            bosL = new BossLocation();
            bosL = BossLocation::createScene("slime", enemies, static_cast<Player*>(this->player));
            checkBoss = true;
            this->addChild(bosL, 1);
            player->body->SetTransform(b2Vec2(20.f, -39.f), player->body->GetAngle());
        }
        else {
            if (countLocation == lvlBoss2) {
                generation->cleanScene();
                bosL = new BossLocation();
                bosL = BossLocation::createScene("Goblin", enemies, static_cast<Player*>(this->player));
                checkBoss = true;
                this->addChild(bosL, 1);
                player->body->SetTransform(b2Vec2(20.f, -39.f), player->body->GetAngle());
            }
            else {
                generation->generation(checkMap, countLocation);
                portalInit();

                barrels = generation->getBarrel();
                for (int i = 0; i < barrels.size(); i++)
                    scene->addChild(barrels[i], 3);

                setPosPlayerMiniMap();
                generation->addMiniMap(static_cast<Player*>(player), player->getPosition(), idRoom);
            }
        }
        countLocation += 1;
    }
}