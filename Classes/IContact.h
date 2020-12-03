#pragma once
#ifndef __IContact__
#define __IContact__

#include "cocos2d.h"
#include <Box2d/Box2d.h>

class IContact
{
public:
	virtual void BeginContact(b2Body* body) {};
	virtual void EndContact(b2Body* body) {};
	virtual void PreSolve(b2Body* body) {};
	virtual void PostSolve(b2Body* body) {};
	
};

#endif // __IContact__
