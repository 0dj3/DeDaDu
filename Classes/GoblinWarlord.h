#pragma once
#ifndef __GOBLIN_WARLORD_H__
#define __GOBLIN_WARLORD_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

class GoblinWarlord : public Enemy
{
public:
    GoblinWarlord();
   
    static Enemy* create(const cocos2d::Vec2& position, Player* player);
    virtual void DeathRattle() override;

    static int checkDeath;
private:
    void update(float dt);
};

#endif // __GOBLIN_WARLORD_H__
