#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Attack.h"

USING_NS_CC;
Goblin::Goblin()
{
    stats = new UnitStats(0.5, 1, 1, 1);
    CheckMaxHP();
    hp = maxHP;
    Goblin::idleGoblin("res/enemy/goblin/goblin.plist");
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}

Enemy* Goblin::create(const Vec2& position, Player* player)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin && newGoblin->sprite->initWithFile("res/enemy/goblin/1.png"))
    {
        newGoblin->spawnEnemy();
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);
        newGoblin->setPosition(position);
        newGoblin->targetPosition = position;

        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());
        newGoblin->setTag(newGoblin->tag);
        newGoblin->_player = player;

        newGoblin->hands = new Hands(newGoblin);
        newGoblin->addChild(newGoblin->hands);
        Weapon* weapon;
        switch (rand() % 2)
        {
        case 0:
            weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/fire.png", "res/sounds/swoosh.mp3", 10, 2, 2);
            break;
        case 1:
            weapon = Weapon::createMelee("res/weapon/knife.png", "res/effects/projectile/slash.png", "res/sounds/swoosh.mp3", 20, 0.5);
            break;
        default:
            break;
        }
        newGoblin->hands->PutInHands(weapon);
        newGoblin->scheduleUpdate();
        return newGoblin;
    }
    CC_SAFE_DELETE(newGoblin);
    return NULL;
}

void Goblin::update(float dt)
{
    if (hands->IsDelay())
        return;
    if (!getNumberOfRunningActions()) {
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)(rand()) / RAND_MAX * (1) + 1);
        switch (rand() % 3)
        {
        case 0:
        case 1: {
            if (hands->GetWeapon()->weaponType == Weapon::MELEE) {
                if (this->getPosition().distance(Player::position) < 50) {
                    hands->UseItem(this->getPosition(), (Player::position - getPosition()).getAngle());
                    this->runAction(delay);
                }
            }
            else {
                hands->UseItem(this->getPosition(), (Player::position - getPosition()).getAngle());
                this->runAction(delay);
            }
            break;
        }
        case 2: { 
            if (static_cast<Weapon*>(hands->GetWeapon())->weaponType == Weapon::MELEE)
                targetPosition = Player::position;
            else
                targetPosition = Vec2(((double)(rand()) / RAND_MAX * (10 * PPM) - (5 * PPM)), ((double)(rand()) / RAND_MAX * (10 * PPM) - (5 * PPM))) + getPosition();
            this->runAction(delay);
            break;
        }
        default:
            break;
        }
    }
    move();
}

void Goblin::move()
{
    if (getPosition().distance(targetPosition) < stats->moveSpeed * PPM) {
        stopAllActions();
        return;
    }
    Vec2 toTarget = targetPosition - this->getPosition();
    toTarget.normalize();
    Vec2 desiredVel = stats->moveSpeed * toTarget;
    b2Vec2 vel = b2Vec2(desiredVel.x, desiredVel.y);
    body->ApplyForceToCenter((LINEAR_ACCELERATION)*vel, true);
}

void Goblin::DeathRattle() {
    Enemy::DropItems(this->getPosition());
}

void Goblin::idleGoblin(char* path)
{
    char goblinStr[200] = { 0 };
    auto goblinSpriteCache = SpriteFrameCache::getInstance();
    goblinSpriteCache->addSpriteFramesWithFile(path);

    Vector<SpriteFrame*> idleAnimFrames1(6);
    for (int i = 1; i <= 6; i++) {
        sprintf(goblinStr, "run_%i.png", i);
        SpriteFrame* spriteF = goblinSpriteCache->getSpriteFrameByName(goblinStr);
        spriteF->getTexture()->setAliasTexParameters();
        idleAnimFrames1.pushBack(spriteF);
    }
    auto goblinIdle = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    /*auto demoGoblin = Sprite::createWithSpriteFrameName("run_1.png");
    demoGoblin->setPosition(Point(this->getPosition().x, this->getPosition().y));
    demoGoblin->setScale(3.0);
    Action* action1 = RepeatForever::create(Animate::create(goblinIdle));*/
    Animate* animate = Animate::create(goblinIdle);
    Goblin::sprite->runAction(RepeatForever::create(animate));
    /*demoGoblin->runAction(action1);
    this->addChild(demoGoblin);*/
}
