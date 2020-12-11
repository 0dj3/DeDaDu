#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <map>
#include <string>
#include "PhysicHelper.h"

class Item : public cocos2d::Sprite
{
public:
    typedef enum ItemType
    {
        GOLD = 1,
        POTION,
        WEAPON
    };

    ItemType type;
    std::string title;
    std::string description;
    std::string filename;
    std::map<std::string, int> stats;
    int price = 0;

    Item();

    static Item* create(ItemType type, std::string title, std::string description, std::string filename, std::map<std::string, int> stats);
    static Item* create(Item* item);

    void DropItem(cocos2d::Vec2 position);

    void PickUpItem();

    b2Body* CreatePhysicBody();

    void Sell(cocos2d::Vec2 position, int price);

    bool IsForSale() { return isForSale; };

private:
    bool isForSale = false;

};

#endif // __ITEM_H__
