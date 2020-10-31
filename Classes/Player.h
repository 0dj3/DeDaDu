#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Unit.h"
#include <string>

class Player : public Unit
{
public:
    Player();

    static Unit* create(cocos2d::Layer* scene);

private:
    void listenKeyboard(); 
    bool keyStates[4] = {0, 0, 0, 0};

    void update(float dt);

    void move();

};

#endif // __PLAYER_H__
