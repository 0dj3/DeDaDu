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
    Vec2 pos = this->convertToWorldSpace(this->getPosition());
    bodyDef.position.Set(pos.x / PPM, pos.y / PPM);
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
    bodyDef.userData = this;

    body = PhysicHelper::world->CreateBody(&bodyDef);
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = this->getContentSize().width * this->getScale() / 2 / PPM;

    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    body->CreateFixture(&shapeDef);    
    //log("%f %f", body->GetPosition().x, body->GetPosition().y);
}

void Weapon::Attack()
{
    cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.1);

    auto startAttack = CallFunc::create([this]() {
        isActive = true;
        CreatePhysicBody();
    });
    auto endAttack = CallFunc::create([this]() {
        log("weapon");
        isActive = false;
    });

    auto seq = cocos2d::Sequence::create(startAttack, delay, endAttack, nullptr);

    this->runAction(seq);
}