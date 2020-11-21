#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;
Goblin::Goblin()
{
    dmgsound = "goblin.mp3";
    this->autorelease();
}



Enemy* Goblin::create(cocos2d::Layer* layer, const Vec2& position)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin && newGoblin->sprite->initWithFile("test_goblin.png"))
    {
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);
        newGoblin->setPosition(position);

        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());

        newGoblin->layer = layer;
        newGoblin->scheduleUpdate();
        return newGoblin;
    }
    CC_SAFE_DELETE(newGoblin);
    return NULL;
}

void Goblin::update(float dt)
{   
}

void Goblin::move()
{
}   
