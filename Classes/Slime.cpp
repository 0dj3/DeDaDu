#include "Slime.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;

Slime::Slime()
{
    dmgsound = "res/sounds/hit/slime.mp3";
    tag = ContactListener::ENEMY;
    this->autorelease();
}

Enemy* Slime::create(cocos2d::Layer* layer, const Vec2& position)
{
    Slime* newSlime = new Slime();
    if (newSlime && newSlime->sprite->initWithFile("res/enemy/slime/test_slime.png")) 
    {
        newSlime->spawnEnemy();
        newSlime->sprite->getTexture()->setAliasTexParameters();
        newSlime->sprite->setScale(3.0);
        newSlime->setPosition(position);
        newSlime->hp = 30;
        newSlime->body = PhysicHelper::createDynamicPhysicBody(newSlime, newSlime->sprite->getContentSize());

        newSlime->setTag(newSlime->tag);
        newSlime->layer = layer;
        newSlime->scheduleUpdate();
        return newSlime;
    }
    CC_SAFE_DELETE(newSlime);
    return NULL;
}

void Slime::update(float dt)
{
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* microDelay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (1) + 1);
        auto startAttack = CallFunc::create([this]() {
            b2Vec2 toTarget = b2Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
            toTarget.Normalize();
            b2Vec2 desiredVel = 50 * toTarget;
            body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
        });

        auto seq = cocos2d::Sequence::create(microDelay, startAttack, nullptr);

        this->runAction(seq);
    }
}  
