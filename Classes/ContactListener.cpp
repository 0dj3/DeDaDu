#pragma pointers_to_members(full_generality, multiple_inheritance)

#include "ContactListener.h"
#include "Definitions.h"
#include "Unit.h"
#include "Player.h"

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
    case ITEM:
        BeginItemContact(bodyA, bodyB);
        break;
    }
}

void ContactListener::BeginPlayerContact(b2Body* player, b2Body* body)
{
    
}

void ContactListener::BeginEnemyContact(b2Body* enemy, b2Body* body)
{
    if (static_cast<Unit*>(body->GetUserData())->getName() == "unit") {
        Unit* unit = static_cast<Unit*>(body->GetUserData());
        if (unit->getTag() == PLAYER) {
            b2Vec2 direction = body->GetPosition() - enemy->GetPosition();
            direction.Normalize();
            body->ApplyForceToCenter(10 * (LINEAR_ACCELERATION)*direction, true);
            unit->Damage(20);
        }
    }
}

void ContactListener::BeginWeaponContact(b2Body* weapon, b2Body* body)
{
    Node* node = static_cast<Node*>(body->GetUserData());
    if (node->getTag() == PLAYER)
        return;

    b2Vec2 direction = body->GetPosition() - weapon->GetPosition();
    direction.Normalize();
    body->ApplyForceToCenter(10 * (LINEAR_ACCELERATION)*direction, true);

    if (node->getTag() == ENEMY) {
        Unit* unit = static_cast<Unit*>(body->GetUserData());
        unit->Damage(static_cast<Weapon*>(weapon->GetUserData())->GetDamage());
    }
}

void ContactListener::BeginItemContact(b2Body* item, b2Body* body)
{
    Node* node = static_cast<Node*>(body->GetUserData());
    if (node->getTag() == PLAYER) {
        Player* player = static_cast<Player*>(body->GetUserData());
        player->targetItem = static_cast<Item*>(item->GetUserData());
    }
}