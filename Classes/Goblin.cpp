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
    idle();
    hp = maxHP;
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
        Item* weapon = Weapon::GetRandomWeapon();
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
            if (hands->GetItem()->type == Item::WEAPON) {
                if (static_cast<Weapon*>(hands->GetItem())->weaponType == Weapon::MELEE) {
                    if (this->getPosition().distance(Player::position) < 50) {
                        hands->UseItem(this->getPosition(), (Player::position - getPosition()).getAngle());
                        this->runAction(delay);
                    }
                }
                else {
                    hands->UseItem(this->getPosition(), (Player::position - getPosition()).getAngle());
                    this->runAction(delay);
                }
            }
            break;
        }
        case 2: { 
            if (hands->GetItem()->type == Item::WEAPON)
                if (static_cast<Weapon*>(hands->GetItem())->weaponType == Weapon::MELEE)
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

void Goblin::idle()
{
    char str1[200] = { 0 };
    auto spritecache1 = SpriteFrameCache::getInstance();
    spritecache1->addSpriteFramesWithFile("res/enemy/goblin/goblin.plist");

    Vector<SpriteFrame*> idleAnimFrames1(6);
    for (int i = 1; i <= 6; i++) {
        sprintf(str1, "run_%i.png", i);
        SpriteFrame* spriteF = spritecache1->getSpriteFrameByName(str1);
        spriteF->getTexture()->setAliasTexParameters();
        idleAnimFrames1.pushBack(spriteF);
    }
    idleAnimate = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    auto demo1 = Sprite::createWithSpriteFrameName("run_1.png");
    demo1->setPosition(Point(this->getPosition().x, this->getPosition().y));
    demo1->setScale(3.0);
    Action* action1 = RepeatForever::create(Animate::create(idleAnimate));
    demo1->runAction(action1);
    this->addChild(demo1);
}
