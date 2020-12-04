#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <map>
#include <string>

class Item
{
public:
    typedef enum ItemType
    {
        POTION = 1,
        WEAPON
    };

    ItemType type;
    std::string title;
    std::string description;
    std::string iconPath;
    std::map<std::string, int> stats;

    Item();

    static Item* create(ItemType type, std::string title, std::string description, std::string iconPath, std::map<std::string, int> stats);
    static Item* create(Item* item);

private:

};

#endif // __ITEM_H__
