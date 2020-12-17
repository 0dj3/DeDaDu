#include "Enemy.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "Item.h"
#include "Gold.h"
USING_NS_CC;

Enemy::Enemy()
{
	tag = ContactListener::ENEMY;
    this->maxHp = 100;
}

void Enemy::DropItems(Vec2 position) {
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