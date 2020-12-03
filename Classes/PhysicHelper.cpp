#include "PhysicHelper.h"
#include "Definitions.h"

USING_NS_CC;

b2World* PhysicHelper::world;

b2Body* PhysicHelper::createDynamicPhysicBody(Node* node, const Size& size)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(node->getPosition().x / PPM, node->getPosition().y / PPM);
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
    bodyDef.userData = node;

    b2Body* body = world->CreateBody(&bodyDef); 
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = size.width * node->getScale() / 2 / PPM;

    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    body->CreateFixture(&shapeDef);

    return body;
}

b2Body* PhysicHelper::createWallPhysicBody(Node* node, const Size& size)
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(node->getPosition().x / PPM, node->getPosition().y / PPM);
    //bodyDef.userData = node;

    b2Body* body = world->CreateBody(&bodyDef);
    assert(body != NULL);
    
    b2PolygonShape box;
    box.SetAsBox(size.width * node->getScaleX() / PPM, size.height * node->getScaleY() / PPM);

    b2FixtureDef shapeDef;
    shapeDef.shape = &box;
    body->CreateFixture(&shapeDef);

    return body;
}

void PhysicHelper::CreateWorld()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, 0.0f);
    world = new b2World(gravity);
    world->SetContactListener(new ContactListener());
}