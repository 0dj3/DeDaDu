#include "Fly.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"

USING_NS_CC;
Fly::Fly()
{
    dmgsound = "res/sounds/hit/hit.mp3";
    this->autorelease();
}

Enemy* Fly::create(cocos2d::Layer* layer, const cocos2d::Vec2& position)
{
    Fly* newFly = new Fly();
    if (newFly && newFly->sprite->initWithFile("res/enemy/fly/idle_1.png"))
    {
        newFly->sprite->getTexture()->setAliasTexParameters();
        newFly->sprite->setScale(3.0);
        newFly->setPosition(position);

        newFly->body = PhysicHelper::createDynamicPhysicBody(newFly, newFly->sprite->getContentSize());

        newFly->setTag(newFly->tag);
        newFly->layer = layer;
        newFly->scheduleUpdate();
        return newFly;
    }
    CC_SAFE_DELETE(newFly);
    return NULL;
}

void Fly::update(float dt)
{   
}

void Fly::move()
{
}   
