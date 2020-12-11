#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "InputListener.h"
#include "Weapon.h"
#include "Item.h"

class Player : public Unit
{
public:
    Item* targetItem = NULL;
    Player();
    void setGold(int x);
    static Unit* create(cocos2d::Layer* layer, const cocos2d::Vec2& position);
    int gold = 10;
private:
    bool isFighting = false;
    Item* hends = NULL;

    cocos2d::Sprite* handsSprite;

    void PutInHands(Item* item);
    void update(float dt);

    void move();
    void rotate();

};

#endif // __PLAYER_H__
