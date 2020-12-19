#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#define START_HP 100

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
    bool IsDead() { return this->getName() == DEAD_TAG ? true : false; };

    Unit();
    rapidjson::Document doc;
    void Damage(int value);

    void Dead();

    void CheckMaxHP();
    float sfx;
    char* dmgsound;

    int hp;
    int maxHP;
private:
    bool isDelay = false;
    void loadStats();
    void loadSettings();
    //bool isDead = false;

};

#endif // __UNIT_H__
