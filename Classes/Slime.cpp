#include "Slime.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;

Slime::Slime()
{
    //idleSlime("res/enemy/slime/slime.plist");
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
    //idleSLime();
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

void Slime::idleSlime(char* path)
{
    char slimeSrt[200] = { 0 };
    auto slimeCache = SpriteFrameCache::getInstance();
    slimeCache->addSpriteFramesWithFile(path);

    Vector<SpriteFrame*> slimeAnimFrames(6);
    for (int i = 1; i <= 6; i++) {
        sprintf(slimeSrt, "run_%i.png", i);
        SpriteFrame* spriteF = slimeCache->getSpriteFrameByName(slimeSrt);
        spriteF->getTexture()->setAliasTexParameters();
        slimeAnimFrames.pushBack(spriteF);
    }
    auto slimeidle = Animation::createWithSpriteFrames(slimeAnimFrames, 0.1f);
    auto slimeAnimation = Sprite::createWithSpriteFrameName("run_1.png");
    slimeAnimation->setPosition(Point(this->getPosition().x, this->getPosition().y));
    slimeAnimation->setScale(3.0);
    Action* action1 = RepeatForever::create(Animate::create(slimeidle));
    slimeAnimation->runAction(action1);
    this->addChild(slimeAnimation);
}