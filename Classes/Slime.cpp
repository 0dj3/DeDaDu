#include "Slime.h"
#include "Definitions.h"
#include "Player.h"


float targetX;
float targetY;

USING_NS_CC;
Slime::Slime()
{
    this->autorelease();
}


Unit* Slime::create(cocos2d::Layer* layer, Unit* player)
{
    targetX = player->getPosition().x;
    targetY = player->getPosition().y;
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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    ccBezierConfig bezier;
    bezier.controlPoint_1 = Point(targetX, targetY);
    bezier.controlPoint_2 = Point(visibleSize.width / 2 + origin.x - 100, visibleSize.height / 2 + origin.y);
    bezier.endPosition = Point(targetX, targetY);

    auto move = BezierTo::create(100, bezier);
    this->runAction(move);
}   
