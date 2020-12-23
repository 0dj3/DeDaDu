#include "Fly.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;

Fly::Fly()
{
    dmgsound = "res/sounds/hit/fly.mp3";
    this->autorelease();
}



Enemy* Fly::create(cocos2d::Layer* layer, const Vec2& position)
{
    Fly* newFly = new Fly();
    if (newFly && newFly->sprite->initWithFile("v1.1 dungeon crawler 16x16 pixel pack/props_itens/barrel.png")) 
    {
        newFly->spawnEnemy();
        newFly->sprite->getTexture()->setAliasTexParameters();
        newFly->sprite->setScale(3.0);
        newFly->setPosition(position);

        newFly->body = PhysicHelper::createDynamicPhysicBody(newFly, newFly->sprite->getContentSize());

        newFly->body->SetType(b2_staticBody);
        newFly->hp = 1;
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
    /*move();*/
}

void Fly::move()
{
    /* Size visibleSize = Director::getInstance()->getVisibleSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     ccBezierConfig bezier;
     bezier.controlPoint_1 = Point(, targetY);
     bezier.controlPoint_2 = Point(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y);
     bezier.endPosition = Point(targetX, targetY);

     auto move = BezierTo::create(100, bezier);
     this->runAction(move);*/
}