#pragma once
#ifndef __ContactListener__
#define __ContactListener__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <iostream>
#include <fstream>

class ContactListener: public b2ContactListener
{
public:
    typedef enum BodyTag
    {
        PLAYER = 1,
        GOLD,
        ENEMY,
        ATTACK,
        ITEM
    };

    rapidjson::Document doc;

private:
    void loadSettings();
    float sfx;

	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact) {};
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

    void SelectReaction(b2Body* bodyA, b2Body* bodyB);
    void BeginPlayerContact(b2Body* bodyA, b2Body* bodyB);
    void BeginGoldContact(b2Body* bodyA, b2Body* bodyB);
    void BeginEnemyContact(b2Body* bodyA, b2Body* bodyB);
    void BeginAttackContact(b2Body* bodyA, b2Body* bodyB);
    void BeginItemContact(b2Body* bodyA, b2Body* bodyB);

};

#endif // __ContactListener__
