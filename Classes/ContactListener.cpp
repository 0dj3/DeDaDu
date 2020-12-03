#pragma pointers_to_members(full_generality, multiple_inheritance)

#include "ContactListener.h"
#include "Definitions.h"
#include "Unit.h"

USING_NS_CC;

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Body* a = contact->GetFixtureA()->GetBody();
    b2Body* b = contact->GetFixtureB()->GetBody(); 
    if (b->GetUserData() != NULL && a->GetUserData() != NULL)
    {
        SelectReaction(a, b);
        SelectReaction(b, a);
        /*static_cast<Unit*>(a->GetUserData())->BeginContact(b);
        static_cast<Unit*>(b->GetUserData())->BeginContact(a);*/
    }
}

void ContactListener::SelectReaction(b2Body* bodyA, b2Body* bodyB)
{
    switch(static_cast<Node*>(bodyA->GetUserData())->getTag())
    {
    case PLAYER:
        BeginPlayerContact(bodyA, bodyB);
        break;
    case ENEMY:
        BeginEnemyContact(bodyA, bodyB);
        break;
    case WEAPON:
        BeginWeaponContact(bodyA, bodyB);
        break;
    }
}
void ContactListener::BeginPlayerContact(b2Body* player, b2Body* body)
{
    
}
void ContactListener::BeginEnemyContact(b2Body* enemy, b2Body* body)
{

}
void ContactListener::BeginWeaponContact(b2Body* weapon, b2Body* body)
{
    if (static_cast<Unit*>(body->GetUserData())->getName() == "unit") {
        Unit* unit = static_cast<Unit*>(body->GetUserData());
        if (unit->getTag() == ENEMY) {
            unit->Damage(20);
        }
    }
}