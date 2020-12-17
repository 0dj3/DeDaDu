#include "Attack.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "InputListener.h"
#include "AudioEngine.h"

USING_NS_CC;

Attack::Attack() {

}

void Attack::CreateProjectile(Vec2 position, Vec2 localTarget, ContactListener::BodyTag creatorTag, Weapon* weapon) {
    Attack* attack = new Attack();
    if (attack && attack->initWithFile(weapon->projectileFilename)) {
        attack->setPosition(position);
        attack->setRotation(CC_RADIANS_TO_DEGREES(-localTarget.getAngle()));
        attack->setTag(ContactListener::ATTACK);
        attack->creatorTag = creatorTag;
        Director::getInstance()->getRunningScene()->addChild(attack);
        attack->weapon = weapon;

        cocos2d::DelayTime* delay;
        if (weapon->weaponType == Weapon::MELEE) {
            delay = cocos2d::DelayTime::create(0.01);
            attack->setScale(2);
        }
        else {
            delay = cocos2d::DelayTime::create(weapon->attackRange / weapon->speed);
        }
        auto startAttack = CallFunc::create([attack, localTarget]() {
            attack->setName("");
            b2Body* body =  attack->CreatePhysicBody();
            b2Vec2 pos = b2Vec2(localTarget.x, localTarget.y);
            pos.Normalize();
            body->ApplyForceToCenter((LINEAR_ACCELERATION) * attack->weapon->speed * PPM * pos, true);
        });
        auto endAttack = CallFunc::create([attack]() {
            attack->setName(DEAD_TAG);
        });

        auto seq = cocos2d::Sequence::create(startAttack, delay, endAttack, nullptr);
        attack->runAction(seq);
        return;
    }
    
    CC_SAFE_DELETE(attack);
}

b2Body* Attack::CreatePhysicBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->getPosition().x / PPM, this->getPosition().y / PPM);
    //bodyDef.angle = CC_DEGREES_TO_RADIANS(sprite->getRotation());
    bodyDef.linearDamping = 0;
    bodyDef.angularDamping = 0;
    bodyDef.userData = this;

    b2Body* body = PhysicHelper::world->CreateBody(&bodyDef);
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
    return body;
}