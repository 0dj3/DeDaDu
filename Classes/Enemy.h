#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "cocos2d.h"
#include "Player.h"

class Enemy : public Unit
{
public:
    Player* _player;

    Enemy();

private:

};

#endif // __ENEMY_H__
