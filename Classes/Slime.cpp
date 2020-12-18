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
        newSlime->weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/fire.png", "res/sounds/swoosh.mp3", 10, 1, 5, 4);
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
        auto move = CallFunc::create([this]() {
            b2Vec2 toTarget = b2Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
            toTarget.Normalize();
            b2Vec2 desiredVel = 50 * toTarget;
            body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
            });
        auto attack = CallFunc::create([this]() {
            for (int i = 0; i < (rand() % 2 + 2); i++) {
                Vec2 toPlayer = Player::position - this->getPosition();
                //toPlayer.normalize();
                Vec2 toTarget = Vec2((double)(rand()) / RAND_MAX * (200) - 100, (double)(rand()) / RAND_MAX * (200) - 100);
                //toTarget.normalize();
                weapon->StartAttack(this->getPosition(), toPlayer + toTarget, ContactListener::ENEMY);
                //attack->setColor(Color3B(0, 255, 0));
            }
            });
        Sequence* seq;
        if (rand() % 2) {
            seq = cocos2d::Sequence::create(microDelay, move, nullptr);
        }
        else {
            seq = cocos2d::Sequence::create(microDelay, attack, nullptr);
        }

        this->runAction(seq);
    }
}  
