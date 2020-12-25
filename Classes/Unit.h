#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#include "Definitions.h"
#include "cocos2d.h"
#include "UnitStats.h"
#include "Anime.h"
#include <Box2d/Box2d.h>
#include "IContact.h"
#include "ContactListener.h"
#include <cstdlib>
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>

class Unit : public cocos2d::Node
{
public:
    ContactListener::BodyTag tag;
    b2Body* body;
    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;
    UnitStats* stats;
    char* dmgsound;
    int hp;
    int maxHP;
    int startHP;

    Unit();
    void Damage(int value);
    bool IsInvulnerable() { return isInvulnerable; };
    void Dead();
    void SetInvulnerable(double time);
    void CheckMaxHP();
<<<<<<< HEAD
    virtual void DeathRattle() {};
=======

>>>>>>> c9bb108263d6d426a8cfe323525f30d5fde6171c
private:
    bool isInvulnerable = false;
    void loadStats();

};

#endif // __UNIT_H__
