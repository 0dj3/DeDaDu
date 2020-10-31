#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

class Unit : public cocos2d::Node
{
public:
    cocos2d::Sprite* sprite;
    cocos2d::Layer* scene;
    float speed;

    Unit();

private:

};

#endif // __UNIT_H__
