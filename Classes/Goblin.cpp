#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"

USING_NS_CC;
Goblin::Goblin()
{
    stats->speed = 1;
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}



Enemy* Goblin::create(cocos2d::Layer* layer, const Vec2& position, Player* player)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin && newGoblin->sprite->initWithFile("res/enemy/goblin/test_goblin.png"))
    {
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);
        newGoblin->setPosition(position);

        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());

        newGoblin->setTag(newGoblin->tag);
        newGoblin->layer = layer;
        newGoblin->_player = player;
        newGoblin->scheduleUpdate();
        return newGoblin;
    }
    CC_SAFE_DELETE(newGoblin);
    return NULL;
}

void Goblin::update(float dt)
{   
    Vec2 toTarget = _player->getPosition() - this->getPosition();
    toTarget.normalize();
    Vec2 desiredVel = stats->speed * toTarget;
    b2Vec2 vel = b2Vec2(desiredVel.x, desiredVel.y);
    body->ApplyForceToCenter((LINEAR_ACCELERATION)*vel, true);
}

void Goblin::move()
{
}   
