#pragma pointers_to_members(full_generality, multiple_inheritance)

#include "ContactListener.h"
#include "Definitions.h"
#include "Unit.h"
#include "Player.h"
#include "Attack.h"
#include "HUD.h"
#include "AudioEngine.h"
#include "Gold.h"
#include "GameManager.h"

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
    case GOLD:
        BeginGoldContact(bodyA, bodyB);
        break;
    case ENEMY:
        BeginEnemyContact(bodyA, bodyB);
        break;
    case ATTACK:
        BeginAttackContact(bodyA, bodyB);
        break;
    case ITEM:
        BeginItemContact(bodyA, bodyB);
        break;
    }
}

void ContactListener::BeginPlayerContact(b2Body* player, b2Body* body)
{
    
}

void ContactListener::BeginGoldContact(b2Body* gold, b2Body* body)
{
    Gold* goldNode = static_cast<Gold*>(gold->GetUserData());
    if (static_cast<Node*>(body->GetUserData())->getTag() == PLAYER) {
        Player* player = static_cast<Player*>(body->GetUserData());
        HUD::DisplayString(goldNode->getPosition(), std::to_string(goldNode->value), 15, Color3B(255, 255, 0));
        AudioEngine::preload("res/sounds/coin.mp3");
        AudioEngine::play2d("res/sounds/coin.mp3", false, GameManager::Instance()->GetSFX());
        player->setGold(goldNode->value);
        goldNode->setName(DEAD_TAG);
    }
}

void ContactListener::BeginEnemyContact(b2Body* enemy, b2Body* body)
{
    /*if (static_cast<Unit*>(body->GetUserData())->getName() == "unit") {
        Unit* unit = static_cast<Unit*>(body->GetUserData());
        if (unit->getTag() == PLAYER) {
            b2Vec2 direction = body->GetPosition() - enemy->GetPosition();
            direction.Normalize();
            body->ApplyForceToCenter(10 * (LINEAR_ACCELERATION)*direction, true);
            unit->Damage(5);
        }
    }*/
}

void ContactListener::BeginAttackContact(b2Body* weapon, b2Body* body)
{
    Node* node = static_cast<Node*>(body->GetUserData());
    Attack* attack = static_cast<Attack*>(weapon->GetUserData());
    if (node->getTag() == attack->GetCreatorTag() || node->getTag() == ITEM || attack->getName() == DEAD_TAG || node->getTag() == GOLD)
        return;
    if (node->getTag() == ATTACK) {
        Attack* attackB = static_cast<Attack*>(body->GetUserData());
        if(attackB->GetWeaponType() == Weapon::RANGE)
            return;
    }

    if (node->getName() == "unit") {
        Unit* unit = static_cast<Unit*>(body->GetUserData());
        if (unit->IsInvulnerable())
            return;
        b2Vec2 direction = body->GetPosition() - weapon->GetPosition();
        direction.Normalize();
        body->ApplyForceToCenter(10 * (LINEAR_ACCELERATION)*direction, true);
        unit->Damage(attack->GetDamage());
    }
    if (attack->GetWeaponType() == Weapon::RANGE)
        attack->setName(DEAD_TAG);
}

void ContactListener::BeginItemContact(b2Body* item, b2Body* body)
{
    Node* node = static_cast<Node*>(body->GetUserData());
    Item* itemNode = static_cast<Item*>(item->GetUserData());
    if (node->getTag() == PLAYER) {
        Player* player = static_cast<Player*>(body->GetUserData());
        player->targetItem = static_cast<Item*>(item->GetUserData());
    }
}