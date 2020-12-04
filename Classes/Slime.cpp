#include "Slime.h"
#include "Definitions.h"
#include "Player.h"

USING_NS_CC;

Slime::Slime()
{
    dmgsound = "res/sounds/hit/slime.mp3";
    tag = ContactListener::ENEMY;
    this->autorelease();
}

Enemy* Slime::create(cocos2d::Layer* layer, const Vec2& position)
{
    Slime* newSlime = new Slime();
    if (newSlime && newSlime->sprite->initWithFile("res/enemy/slime/test_slime.png")) {
        newSlime->sprite->getTexture()->setAliasTexParameters();
        newSlime->sprite->setScale(3.0);
        newSlime->setPosition(position);

        newSlime->body = PhysicHelper::createDynamicPhysicBody(newSlime, newSlime->sprite->getContentSize());

        newSlime->setTag(newSlime->tag);
        newSlime->layer = layer;
        newSlime->scheduleUpdate();
        return newSlime;
    }
    CC_SAFE_DELETE(newSlime);
    return NULL;
}

void Slime::update(float dt)
{   
    /*move();*/
}

void Slime::move()
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
