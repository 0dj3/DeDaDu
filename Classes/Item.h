#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <map>
#include <string>
#include "PhysicHelper.h"
#include "AudioEngine.h"

class Item : public cocos2d::Sprite
{
protected:
    Item();

public:
    typedef enum ItemType
    {
        POTION,
        WEAPON
    };

    ItemType type;
    //std::string title;
    //std::string description;
    std::string filename;
    double delay;
    int price = 0;

    void DropItem(cocos2d::Vec2 position);

    void PickUpItem();

    b2Body* CreatePhysicBody();

    void Sell(cocos2d::Vec2 position, int price);

    void SellShop(cocos2d::Vec2 position, int price, float circleSize);

    bool IsForSale() { return isForSale; };

private:
    bool isForSale = false;

};

#endif // __ITEM_H__
