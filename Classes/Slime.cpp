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
        newSlime->weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/acid.png", "res/sounds/swoosh.mp3", 10, 1, 2);
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
                Vec2 toPlayer = Player::position - this->getPosition();
                Vec2 toTarget = Vec2((double)(rand()) / RAND_MAX * (200) - 100, (double)(rand()) / RAND_MAX * (200) - 100);
                weapon->StartAttack(this->getPosition(), (toPlayer + toTarget).getAngle(), this);
                //attack->setColor(Color3B(0, 255, 0));
            }
            });
        Sequence* seq = cocos2d::Sequence::create(microDelay, move, microDelay, attack, nullptr);
        /*if (rand() % 2) {
            seq = cocos2d::Sequence::create(microDelay, move, nullptr);
        }
        else {
            seq = cocos2d::Sequence::create(microDelay, attack, nullptr);
        }*/

        this->runAction(seq);
    }
}

void Slime::DeathRattle() {
    Enemy::DropItems(this->getPosition());
}
