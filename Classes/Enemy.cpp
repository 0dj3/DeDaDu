#include "Enemy.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "Item.h"
#include "Gold.h"
USING_NS_CC;

Enemy::Enemy()
{
	tag = ContactListener::ENEMY;
}

void Enemy::DropItems(Vec2 position) {
    Player::giveEXP(10);
    if (rand() % 2) {
        if (rand() % 10 > 8) {
            Item* item = Potion::create("res/items/red_potion.png", "res/sounds/swoosh.mp3", rand() % 15 - 15);
            item->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
            item->DropItem(position);
            Director::getInstance()->getRunningScene()->addChild(item);
        }
        else {
            Gold* gold = Gold::create(position, 1 + rand() % 5);
            Director::getInstance()->getRunningScene()->addChild(gold);
        }
    }
}

void Enemy::spawnEnemy()
{
    char str1[200] = { 0 };
    auto spritecache1 = SpriteFrameCache::getInstance();
    spritecache1->addSpriteFramesWithFile("res/effects/dead/dead.plist");
    auto spritesheet1 = SpriteBatchNode::create("res/effects/dead/dead.png");
    this->addChild(spritesheet1);

    Vector<SpriteFrame*> idleAnimFrames1(5);
    for (int i = 1; i <= 5; i++) {
        sprintf(str1, "dead_%i.png", i);
        idleAnimFrames1.pushBack(spritecache1->getSpriteFrameByName(str1));
    }
    auto idleAnimation1 = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    auto demo1 = Sprite::createWithSpriteFrameName("dead_1.png");
    demo1->setPosition(Point(this->getPosition().x, this->getPosition().y));
    demo1->setScale(3.0);
    Action* action1 = Repeat::create(Animate::create(idleAnimation1), 1);
    demo1->runAction(action1);
    spritesheet1->addChild(demo1);
}