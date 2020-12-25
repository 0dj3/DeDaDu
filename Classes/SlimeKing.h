#pragma once
#ifndef __SLIME_KING_H__
#define __SLIME_KING_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

class SlimeKing : public Enemy
{
public:
    SlimeKing();
   
    static Enemy* create(const cocos2d::Vec2& position, Player* player, int lives);
    virtual void DeathRattle() override;
private:
    int lives;
    void update(float dt);
    void move();
};

#endif // __SLIME_KING_H__
