#include "Weapon.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "Unit.h"
#include "InputListener.h"

USING_NS_CC;

Weapon::Weapon(cocos2d::Layer* layer, Item* weapon)
{
    _layer = layer;
    itemWeapon = weapon;
    this->setTexture(weapon->filename);
    this->getTexture()->setAliasTexParameters();
    this->setScale(2.0);
    //this->setTag(ContactListener::WEAPON);
    isActive = false;
}

void Weapon::ChangeWeapon(Item* weapon)
{
    itemWeapon = weapon;
    this->setTexture(weapon->filename);
    this->getTexture()->setAliasTexParameters();
}

void Weapon::CreatePhysicBody(Sprite* sprite)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(sprite->getPosition().x / PPM, sprite->getPosition().y / PPM);
    //bodyDef.angle = CC_DEGREES_TO_RADIANS(sprite->getRotation());
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
    bodyDef.userData = sprite;

    body = PhysicHelper::world->CreateBody(&bodyDef);
    assert(body != NULL);

    b2CircleShape circle;
    circle.m_radius = sprite->getContentSize().width * sprite->getScale() / PPM / 2;
    /*b2PolygonShape box;
    box.SetAsBox(this->getContentSize().width * this->getScale() / PPM / 2, this->getContentSize().width * this->getScale() / PPM / 2);*/
    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    shapeDef.isSensor = true;
    body->CreateFixture(&shapeDef);
}

void Weapon::Attack(Vec2 position)
{
    cocos2d::DelayTime* microDelay = cocos2d::DelayTime::create(0.01);
    //cocos2d::DelayTime* delay = cocos2d::DelayTime::create(5 / itemWeapon->stats.find("speed")->second);
    cocos2d::Sprite* attack = new Sprite();
    attack->initWithFile("res/effects/hit/slash_1.png");
    attack->setPosition(position);
    //attack->setTag(ContactListener::WEAPON);
    attack->setRotation(CC_RADIANS_TO_DEGREES(-InputListener::Instance()->mousePosition.getAngle()));
    attack->setScale(2);
    Director::getInstance()->getRunningScene()->addChild(attack);
    log("%f %f", attack->getPosition().x, attack->getPosition().y);
    auto startAttack = CallFunc::create([this, attack]() {
        isActive = true;
        attack->setName("");
        CreatePhysicBody(attack);
    });
    auto endAttack = CallFunc::create([attack]() {
        attack->setName(DEAD_TAG);
    });
    /*auto endActive = CallFunc::create([this]() {
        isActive = false;
    });*/

    auto seq = cocos2d::Sequence::create(startAttack, microDelay, endAttack, nullptr);

    attack->runAction(seq);
}