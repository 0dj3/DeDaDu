#pragma once
#ifndef __GOLD_H__
#define __GOLD_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Item.h"
#include "ContactListener.h"

USING_NS_CC;

class Gold : public Sprite
{
public:
    int value;

    Gold() {

    };

    static Gold* create(const Vec2& position, int value) {
        Gold* newGold = new Gold();
        if (newGold->initWithFile("res/items/coin.png")) {
            newGold->getTexture()->setAliasTexParameters();
            newGold->setScale(2.0);
            newGold->setPosition(position);
            newGold->setTag(ContactListener::GOLD);
            newGold->value = value;
            newGold->CreatePhysicBody();
            return newGold;
        }
        CC_SAFE_DELETE(newGold);
        return NULL;
    };


private:
    b2Body* CreatePhysicBody() 
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.fixedRotation = true;
        bodyDef.position.Set(this->getPosition().x / PPM, this->getPosition().y / PPM);
        bodyDef.linearDamping = 10.0f;
        bodyDef.angularDamping = 10.0f;
        bodyDef.userData = this;

        b2Body* body = PhysicHelper::world->CreateBody(&bodyDef);
        assert(body != NULL);

        b2CircleShape circle;
        circle.m_radius = this->getContentSize().width * this->getScale() / PPM / 2;

        b2FixtureDef shapeDef;
        shapeDef.shape = &circle;
        shapeDef.density = 1.0f;
        shapeDef.friction = 0.0f;
        shapeDef.isSensor = true;
        body->CreateFixture(&shapeDef);

        return body;
    };

};

#endif // __GOLD_H__
