#include "SlimeKing.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Attack.h"

USING_NS_CC;
SlimeKing::SlimeKing()
{
    stats = new UnitStats(0.5, 1, 1, 1);
    CheckMaxHP();
    hp = maxHP;
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}

Enemy* SlimeKing::create(cocos2d::Layer* layer, const Vec2& position, Player* player)
{
    SlimeKing* newSlimeKing = new SlimeKing();
    if (newSlimeKing && newSlimeKing->sprite->initWithFile("res/enemy/goblin/test_goblin.png"))
    {
        newSlimeKing->spawnEnemy();
        newSlimeKing->sprite->getTexture()->setAliasTexParameters();
        newSlimeKing->sprite->setScale(3.0);
        newSlimeKing->setPosition(position);

        newSlimeKing->body = PhysicHelper::createDynamicPhysicBody(newSlimeKing, newSlimeKing->sprite->getContentSize());
        newSlimeKing->setTag(newSlimeKing->tag);
        newSlimeKing->layer = layer;
        newSlimeKing->_player = player;

        newSlimeKing->scheduleUpdate();
        return newSlimeKing;
    }
    CC_SAFE_DELETE(newSlimeKing);
    return NULL;
}

void SlimeKing::update(float dt)
{
    if (IsPlayerWithinRange()) {
        Vec2 playerPos = Player::position - this->getPosition();
        playerPos.normalize();
        Vec2 pos = this->getPosition() + playerPos * this->sprite->getContentSize().height * this->getScale() * 2;
    }
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (3) + 1);
        auto startAttack = CallFunc::create([this]() {
            Vec2 toTarget;
            //toTarget = Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
            toTarget = Player::position - this->getPosition();
            toTarget.normalize();
            Vec2 desiredVel = 50 * toTarget * (rand() % 2);
            b2Vec2 vel = b2Vec2(desiredVel.x, desiredVel.y);
            body->ApplyForceToCenter((LINEAR_ACCELERATION)*vel, true);
        });

        auto seq = cocos2d::Sequence::create(delay, startAttack, nullptr);

        this->runAction(seq);
    }
    move();
}

void SlimeKing::move()
{
     Vec2 toTarget = Player::position - this->getPosition();
     toTarget.normalize();
     Vec2 desiredVel = stats->moveSpeed * toTarget;
     b2Vec2 vel = b2Vec2(desiredVel.x, desiredVel.y);
     body->ApplyForceToCenter((LINEAR_ACCELERATION)*vel, true);
}
