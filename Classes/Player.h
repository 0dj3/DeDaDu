#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"

class Player : public Unit
{
public:
    Player();
    static Unit* create(cocos2d::Layer* scene);
    
    void setPos(float x, float y) { xp = x; yp = y; };
    float getX() { return xp; }
    float getY() { return yp; }
private:
    float xp;
    float yp;
    void listenKeyboard(); 
    bool keyStates[4] = {0, 0, 0, 0};

    void update(float dt);

    void move();

};

#endif // __PLAYER_H__
