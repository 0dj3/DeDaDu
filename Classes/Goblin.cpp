#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Attack.h"

USING_NS_CC;
Goblin::Goblin()
{
    stats->speed = 1;
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}

Enemy* Goblin::create(cocos2d::Layer* layer, const Vec2& position, Player* player)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin && newGoblin->sprite->initWithFile("res/enemy/goblin/test_goblin.png"))
    {
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);
        newGoblin->setPosition(position);

        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());
        newGoblin->hp = 50;
        newGoblin->setTag(newGoblin->tag);
        newGoblin->layer = layer;
        newGoblin->_player = player;

        newGoblin->hands = new Hands();
        newGoblin->addChild(newGoblin->hands);
        std::map<std::string, int> stats{
            {"damage", 15},
            {"speed", 5}
        };
        Item* weapon = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/knife.png", stats);
        newGoblin->hands->PutInHands(weapon);

        newGoblin->scheduleUpdate();
        return newGoblin;
    }
    CC_SAFE_DELETE(newGoblin);
    return NULL;
}

void Goblin::update(float dt)
{
    /*if (IsPlayerWithinRange()) {
        Vec2 playerPos = _player->getPosition() - this->getPosition();
        playerPos.normalize();
        Vec2 pos = this->getPosition() + playerPos * this->sprite->getContentSize().height * this->getScale() * 2;
        Attack::StartMeleeAttack(pos, _player->getPosition(), ContactListener::ENEMY, hands->GetItem());
    }*/
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (3) + 1);
        auto startAttack = CallFunc::create([this]() {
            Vec2 toTarget;
            //toTarget = Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
            toTarget = _player->getPosition() - this->getPosition();
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

void Goblin::move()
{
     Vec2 toTarget = _player->getPosition() - this->getPosition();
     toTarget.normalize();
     Vec2 desiredVel = stats->speed * toTarget;
     b2Vec2 vel = b2Vec2(desiredVel.x, desiredVel.y);
     body->ApplyForceToCenter((LINEAR_ACCELERATION)*vel, true);
}
