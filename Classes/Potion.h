#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Item.h"
#include "ContactListener.h"

USING_NS_CC;

class Potion : public Item
{
public:
    std::string soundFilename;
    int value;

    Potion();

    static Potion* create(std::string filename, std::string soundFilename, int value);

    void Drink(Unit* unit);

private:

};

#endif // __POTION_H__
