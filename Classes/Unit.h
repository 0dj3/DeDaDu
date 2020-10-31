#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"
#include "UnitStats.h"

class Unit : public cocos2d::Node
{
public:
    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;
    UnitStats* stats;

    Unit();

private:

};

#endif // __UNIT_H__
