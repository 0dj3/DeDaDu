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
    this->setName("weapon");
}

void Weapon::CreatePhysicBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->getPosition().x / PPM, this->getPosition().y / PPM);
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
    bodyDef.userData = this;

    b2Body* body = PhysicHelper::world->CreateBody(&bodyDef);
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = this->getContentSize().width * this->getScale() / 2 / PPM;

    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    body->CreateFixture(&shapeDef);
    //log("%f", circle.m_radius);
}

void Weapon::Attack()
{
    /*auto startRotate = cocos2d::RotateBy::create(_speed, 60);
    auto endRotate = cocos2d::RotateBy::create(_speed, 0);

    auto startAttack = CallFunc::create([this]() {
        isActive = true;
        CreatePhysicBody();
    });

    auto endAttack = CallFunc::create([this]() {
        isActive = false;
    });

    auto seq = cocos2d::Sequence::create(startAttack, startRotate, endAttack, endRotate, nullptr);

    this->runAction(seq);*/
}