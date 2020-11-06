#include "Slime.h"
#include "Definitions.h"
#include "Player.h"


USING_NS_CC;

Slime::Slime()
{
    this->autorelease();
}


Unit* Slime::create(cocos2d::Layer* layer)
{
    Slime* newSlime = new Slime();
    if (newSlime->sprite->initWithFile("test_slime.png")) {
        newSlime->sprite->getTexture()->setAliasTexParameters();
        newSlime->sprite->setScale(3.0);

        newSlime->body = PhysicHelper::createDynamicPhysicBody(newSlime->sprite->getContentSize());
        newSlime->addComponent(newSlime->body);

        newSlime->layer = layer;
        newSlime->scheduleUpdate();
        return newSlime;
    }
    CC_SAFE_DELETE(newSlime);
    return NULL;
}

void Slime::update(float dt)
{   
    move();
}

void Slime::move()
{
    //this->body->setVelocity(Vec2(directionX, directionY));
}   
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

