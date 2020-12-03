#pragma once
#ifndef __ContactListener__
#define __ContactListener__

#include "cocos2d.h"
#include <Box2d/Box2d.h>

class ContactListener: public b2ContactListener
{
public:
    typedef enum BodyTag
    {
        PLAYER = 1,
        ENEMY,
        WEAPON
    };

private:
	void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact) {};
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {};
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {};

    void SelectReaction(b2Body* bodyA, b2Body* bodyB);
    void BeginPlayerContact(b2Body* bodyA, b2Body* bodyB);
    void BeginEnemyContact(b2Body* bodyA, b2Body* bodyB);
    void BeginWeaponContact(b2Body* bodyA, b2Body* bodyB);

};

#endif // __ContactListener__
