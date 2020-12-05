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
    static Unit* create(cocos2d::Layer* layer, const cocos2d::Vec2& position);
private:
    bool isFighting = false;
    Weapon* _weapon = NULL;

    void CreateWeapon(Item* weapon);

    void update(float dt);

    void move();
    void rotate();

};

#endif // __PLAYER_H__
