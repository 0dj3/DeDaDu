#include "Enemy.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "Item.h"
USING_NS_CC;

Enemy::Enemy()
{
	tag = ContactListener::ENEMY;
    this->maxHp = 100;
}

void Enemy::DropItems(Vec2 position) {
    if (rand() % 2) {
        Item* item;
        if (rand() % 10 > 8) {
            std::map<std::string, int> stats{
            {"healing", -20 + rand() % 40}
            };
            item = Item::create(Item::POTION, "Potion", "Super potion", "res/items/potion.png", stats);
            item->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        }
        else {
            std::map<std::string, int> stats{
                {"value", 1 + rand() % 5},
                {"damage", 100}
            };
            item = Item::create(Item::GOLD, "Gold", "Gold", "res/items/coin.png", stats);
        }
        Director::getInstance()->getRunningScene()->addChild(item);
        item->DropItem(position);
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