#include "SlimeKing.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Attack.h"

int SlimeKing::checkDeath = 0;

USING_NS_CC;
SlimeKing::SlimeKing()
{
    stats = new UnitStats(0.3, 1, 1, 1);
    CheckMaxHP();
    hp = maxHP;
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}

Enemy* SlimeKing::create(const Vec2& position, Player* player, int life)
{
    SlimeKing* newSlimeKing = new SlimeKing();
    if (newSlimeKing && newSlimeKing->sprite->initWithFile("res/enemy/slime/test_slime.png"))
    {
        newSlimeKing->spawnEnemy();
        newSlimeKing->sprite->getTexture()->setAliasTexParameters();
        newSlimeKing->sprite->setScale(life * 2);
        newSlimeKing->setPosition(position);
        newSlimeKing->body = PhysicHelper::createDynamicPhysicBody(newSlimeKing, newSlimeKing->sprite->getContentSize());
        newSlimeKing->setTag(newSlimeKing->tag);
        newSlimeKing->_player = player;
        newSlimeKing->life = life;

        newSlimeKing->scheduleUpdate();
        newSlimeKing->checkDeath++;
        return newSlimeKing;
    }
    CC_SAFE_DELETE(newSlimeKing);
    return NULL;
}

void SlimeKing::update(float dt)
{
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (3) + 1);
        switch (rand() % 3)
        {
        case 0: {
            auto move = CallFunc::create([this]() {
                b2Vec2 toTarget = b2Vec2((double)(rand()) / RAND_MAX * (2) - 1, (double)(rand()) / RAND_MAX * (2) - 1);
                toTarget.Normalize();
                b2Vec2 desiredVel = 50 * toTarget;
                body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
                });
            auto seq = cocos2d::Sequence::create(delay, move, nullptr);
            this->runAction(seq);
            break;

        }
        case 1: {
            cocos2d::DelayTime* attackDelay = cocos2d::DelayTime::create(1);
            auto attack1 = CallFunc::create([this]() {
                double angle = Player::position.getAngle();
                for (int i = -10; i < 10; i++) {
                    Attack::CreateAttack("res/effects/projectile/acid.png", ContactListener::BodyTag::ENEMY,
                        Weapon::RANGE, this->getPosition(), 15 * this->stats->damage, angle + i, 1, 2, 1);
                }
                });
            auto attack2 = CallFunc::create([this]() {
                double angle = Player::position.getAngle();
                for (int i = 10; i > -10; i--) {
                    Attack::CreateAttack("res/effects/projectile/acid.png", ContactListener::BodyTag::ENEMY,
                        Weapon::RANGE, this->getPosition(), 15 * this->stats->damage, angle + i, 1, 2, 1);
                }
                });
            auto seq = cocos2d::Sequence::create(delay, attack1, attackDelay, attack2, nullptr);
            this->runAction(seq);
            break;
        }
        default:
            break;
        }
    }
}

void SlimeKing::DeathRattle() {
    if (life != 1) {
        Enemy* enemy = SlimeKing::create(Vec2(getPosition().x + 10, getPosition().y), _player, life - 1);
        Director::getInstance()->getRunningScene()->addChild(enemy, 2);
        enemy = SlimeKing::create(Vec2(getPosition().x - 10, getPosition().y), _player, life - 1);
        Director::getInstance()->getRunningScene()->addChild(enemy, 2);
    }
    checkDeath--;
}