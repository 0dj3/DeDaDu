#include "Weapon.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "Unit.h"

USING_NS_CC;

Weapon::Weapon(cocos2d::Layer* layer, int damage, float speed)
{
    _layer = layer;
    _damage = damage;
    _speed = speed;
    isActive = false;
}

void Weapon::CreatePhysicBody(Vec2 position)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    Vec2 pos = this->convertToWorldSpace(this->getPosition());
    bodyDef.position.Set(position.x / PPM, position.y / PPM);
    //bodyDef.angle = this->getRotation();
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
    bodyDef.userData = this;

    body = PhysicHelper::world->CreateBody(&bodyDef);
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = this->getContentSize().width * this->getScale() / PPM / 2;
    /*b2PolygonShape box;
    box.SetAsBox(this->getContentSize().width * this->getScale() / PPM / 2, this->getContentSize().width * this->getScale() / PPM / 2);*/
    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    shapeDef.isSensor = true;
    body->CreateFixture(&shapeDef);
    //log("%f %f", this->getContentSize().width * this->getScale() / PPM, this->getContentSize().width * this->getScale() / PPM);
}

void Weapon::Attack(Vec2 position)
{
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.5);

    auto startAttack = CallFunc::create([this, position]() {
        isActive = true;
        this->setName("");
        CreatePhysicBody(position);
    });
    auto endAttack = CallFunc::create([this]() {
        isActive = false;
        this->setName(DEAD_BODY_TAG);
    });

    auto seq = cocos2d::Sequence::create(startAttack, delay, endAttack, nullptr);

    this->runAction(seq);
}