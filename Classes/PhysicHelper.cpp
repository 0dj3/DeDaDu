#include "PhysicHelper.h"
#include "Definitions.h"

USING_NS_CC;

b2World* PhysicHelper::world;

b2Body* PhysicHelper::createDynamicPhysicBody(Node* node, const Size& size)
{
	/*auto newBody = cocos2d::PhysicsBody::createCircle(size.x / 2, cocos2d::PhysicsMaterial(0, 0, 0));
    newBody->setDynamic(true);
    newBody->setContactTestBitmask(true);
    newBody->setLinearDamping(PHYSICS_DAMPING);
    newBody->setMass(1.0f);
    return newBody;*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(node->getPosition().x, node->getPosition().y);
    bodyDef.linearDamping = 4.0f;
    bodyDef.angularDamping = 4.0f;
    bodyDef.userData = node;

    b2Body* body = world->CreateBody(&bodyDef); 
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = size.width * node->getScale() / 2;

    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    b2Fixture* ballFixture = body->CreateFixture(&shapeDef);

    return body;
}

b2Body* PhysicHelper::createWallPhysicBody(Node* node, const Size& size)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(node->getPosition().x, node->getPosition().y);
    bodyDef.userData = node;

    b2Body* body = world->CreateBody(&bodyDef);
    assert(body != NULL);
    
    b2PolygonShape box;
    box.SetAsBox(size.width * node->getScaleX(), size.height * node->getScaleY());

    b2FixtureDef shapeDef;
    shapeDef.shape = &box;
    b2Fixture* boxFixture = body->CreateFixture(&shapeDef);

    return body;
}

void PhysicHelper::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    world = new b2World(gravity);
}