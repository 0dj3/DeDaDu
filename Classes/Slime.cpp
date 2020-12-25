#include "Slime.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;

Slime::Slime()
{
    dmgsound = "res/sounds/hit/slime.mp3";
    stats = new UnitStats(0.3, 1, 1, 1);
    CheckMaxHP();
    hp = maxHP;
    this->autorelease();
}

Enemy* Slime::create(const Vec2& position)
{
    Slime* newSlime = new Slime();
    if (newSlime && newSlime->sprite->initWithFile("res/enemy/slime/test_slime.png")) 
    {
        newSlime->spawnEnemy();
        newSlime->sprite->getTexture()->setAliasTexParameters();
        newSlime->sprite->setScale(3.0);
        newSlime->setPosition(position);
        newSlime->body = PhysicHelper::createDynamicPhysicBody(newSlime, newSlime->sprite->getContentSize());
        newSlime->setTag(newSlime->tag);
        newSlime->scheduleUpdate();
        return newSlime;
    }
    CC_SAFE_DELETE(newSlime);
    return NULL;
}

void Slime::update(float dt)
{
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* microDelay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (1) + 2);
        auto move = CallFunc::create([this]() {
            b2Vec2 toTarget = b2Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
            toTarget.Normalize();
            b2Vec2 desiredVel = 50 * toTarget;
            body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
            });
        auto attack = CallFunc::create([this]() {
            for (int i = 0; i < (rand() % 2 + 2); i++) {
                Attack::CreateAttack("res/effects/projectile/acid.png", ContactListener::BodyTag::ENEMY,
                    Weapon::RANGE, this->getPosition(), 15 * this->stats->damage, (Player::position - getPosition()).getAngle(), 1, 2, 40);
            }
            });
        Sequence* seq = cocos2d::Sequence::create(microDelay, move, microDelay, attack, nullptr);
        this->runAction(seq);
    }
}

void Slime::DeathRattle() {
    Enemy::DropItems(this->getPosition());
}
