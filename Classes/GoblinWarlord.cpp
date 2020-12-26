#include "GoblinWarlord.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Attack.h"
#include "Goblin.h"

int GoblinWarlord::checkDeath = 0;

USING_NS_CC;

GoblinWarlord::GoblinWarlord()
{
    stats = new UnitStats(6, 2, 1, 1);
    CheckMaxHP();
    hp = maxHP;
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}

Enemy* GoblinWarlord::create(const Vec2& position, Player* player)
{
    GoblinWarlord* newGoblinWarlord = new GoblinWarlord();
    if (newGoblinWarlord && newGoblinWarlord->sprite->initWithFile("res/enemy/goblin/test_goblin.png"))
    {
        newGoblinWarlord->sprite->getTexture()->setAliasTexParameters();
        newGoblinWarlord->sprite->setScale(5);
        newGoblinWarlord->setPosition(position);
        newGoblinWarlord->body = PhysicHelper::createDynamicPhysicBody(newGoblinWarlord, newGoblinWarlord->sprite->getContentSize());
        newGoblinWarlord->setTag(newGoblinWarlord->tag);
        newGoblinWarlord->_player = player;

        newGoblinWarlord->scheduleUpdate();
        newGoblinWarlord->checkDeath++;
        return newGoblinWarlord;
    }
    CC_SAFE_DELETE(newGoblinWarlord);
    return NULL;
}

void GoblinWarlord::update(float dt)
{
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (4) + 1);
        switch (rand() % 2)
        {
        case 0: {
            auto spawn = CallFunc::create([this]() {
                Enemy* enemy = Goblin::create(Vec2(getPosition().x + rand() % 100 - 50, getPosition().y + rand() % 100 - 50), _player);
                Director::getInstance()->getRunningScene()->addChild(enemy, 2);
                });
            auto seq = cocos2d::Sequence::create(delay, spawn, spawn, nullptr);
            this->runAction(seq);
            break;

        }
        case 1: {
            cocos2d::DelayTime* attackDelay = cocos2d::DelayTime::create(0.5);
            auto attack = CallFunc::create([this]() {
                double angle = (Player::position - getPosition()).getAngle();
                for (int i = 0; i < 22; i++) {
                    Attack::CreateAttack("res/effects/projectile/acid.png", ContactListener::BodyTag::ENEMY,
                        Weapon::RANGE, this->getPosition(), 20 * this->stats->damage, angle + CC_DEGREES_TO_RADIANS(i * PPM), 1, 2, 1);
                }
                });
            auto seq = cocos2d::Sequence::create(delay, attack, attackDelay, attack, attackDelay, attack, nullptr);
            this->runAction(seq);
            break;
        }
        default:
            break;
        }
    }
}

void GoblinWarlord::DeathRattle() {
    checkDeath--;
}