#pragma once
#ifndef __ContactListener__
#define __ContactListener__

#include "cocos2d.h"
#include <Box2d/Box2d.h>

class ContactListener: public b2ContactListener
{
public:

private:
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

};

#endif // __ContactListener__
