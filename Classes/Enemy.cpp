#include "Enemy.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "Item.h"
USING_NS_CC;

Enemy::Enemy()
{
	tag = ContactListener::ENEMY;
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