#pragma once
#ifndef __PHYSIC_HELPER_H__
#define __PHYSIC_HELPER_H__

#define PHYSICS_DAMPING 0.0f

#include "cocos2d.h"
#include <Box2d/Box2d.h>

class PhysicHelper: public b2ContactListener
{
public:
	static b2World* world;
	static void CreateWorld();
	static b2Body* createDynamicPhysicBody(cocos2d::Node* node, const cocos2d::Size& size);
	static b2Body* createWallPhysicBody(cocos2d::Node* node, const cocos2d::Size& size);

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

#endif // __PHYSIC_HELPER_H__
