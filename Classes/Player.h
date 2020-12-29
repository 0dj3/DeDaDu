#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#define EXP_UNTIL_LVL_UP 10

#include "cocos2d.h"
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "InputListener.h"
#include "Weapon.h"
#include "Item.h"
#include "Hands.h"

class Player : public Unit
{
public:
    static cocos2d::Vec2 position;

    Hands* hands;
    int gold = 10;
    Item* targetItem = NULL;

    Player();
    static Unit* create(const cocos2d::Vec2& position);
    void setGold(int x);

    static void giveEXP(int value);
    virtual void DeathRattle() override;
private:
    int lvl = 1;
    static int exp;
    bool isDashDelay = false;

    void update(float dt);
    void move();
    void checkLVL();
    void cameraUpdate();
    void checkInteract();
    void idleGoblin(char* path);
    float time = 0;
    int asRun = 1;
    int asIdle = 1;
    Vec2 pastPos = Vec2(0, 0);
};

#endif // __PLAYER_H__
