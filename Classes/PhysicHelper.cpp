#include "PhysicHelper.h"
#include "Definitions.h"

USING_NS_CC;

PhysicsBody* PhysicHelper::createDynamicPhysicBody(cocos2d::Vec2 size)
{
	auto newBody = cocos2d::PhysicsBody::createCircle(size.y, cocos2d::PhysicsMaterial());
    newBody->setDynamic(true);
    newBody->setContactTestBitmask(true);
    newBody->setLinearDamping(PHYSICS_DAMPING);
    newBody->setMass(1.0f);
    return newBody;
}