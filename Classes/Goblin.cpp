#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;
Goblin::Goblin()
{
    dmgsound = "goblin.mp3";
    this->autorelease();
}



Enemy* Goblin::create(cocos2d::Layer* layer)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin->sprite->initWithFile("test_goblin.png")) {
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);

        //newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin->sprite->getContentSize());
        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());
        //newGoblin->addComponent(newGoblin->body);

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
