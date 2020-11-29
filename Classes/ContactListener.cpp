#include "ContactListener.h"
#include "Definitions.h"
#include "Unit.h"

USING_NS_CC;

void ContactListener::BeginContact(b2Contact* contact)
{
    auto a = contact->GetFixtureA()->GetBody()->GetUserData();
    auto b = contact->GetFixtureB()->GetBody()->GetUserData();
    //PhysicsBody* playerBody = (bodyA->getTag() == 4) ? bodyA : bodyB;
    if (static_cast<Node*>(b)->getTag() == Unit::ENEMY) {
        static_cast<Unit*> (b)->Damage(20);
    }
}

void ContactListener::EndContact(b2Contact* contact)
{

}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}