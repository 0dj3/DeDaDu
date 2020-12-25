#include "Attack.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "InputListener.h"
#include "AudioEngine.h"
#include <cmath>

USING_NS_CC;

Attack::Attack() {

}

void Attack::CreateAttack(std::string projectileFilename, ContactListener::BodyTag creatorTag, Weapon::WeaponType weaponType, 
    cocos2d::Vec2 position, int damage, double angle, double speed, double size, int scatter) {
    Attack* attack = new Attack();
    if (attack && attack->initWithFile(projectileFilename)) {
        attack->getTexture()->setAliasTexParameters();
        attack->setPosition(position);
        attack->setRotation(CC_RADIANS_TO_DEGREES(-angle) + (rand() % scatter - (scatter / 2)));
        attack->setScale(size);
        attack->setTag(ContactListener::ATTACK);
        attack->creatorTag = creatorTag;
        attack->weaponType = weaponType;
        Director::getInstance()->getRunningScene()->addChild(attack);
        attack->damage = damage;

        if (weaponType == Weapon::MELEE) {
            speed = 5;
            cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.02);
            auto endAttack = CallFunc::create([attack]() {
                attack->setName(DEAD_TAG);
                });
            auto seq = cocos2d::Sequence::create(delay, endAttack, nullptr);
            attack->runAction(seq);
        }

        attack->setName("");
        b2Body* body = attack->CreatePhysicBody();
        b2Vec2 pos = b2Vec2(cos(body->GetAngle()), -sin(body->GetAngle()));
        pos.Normalize();
        body->ApplyForceToCenter((LINEAR_ACCELERATION) * speed * PPM * pos, true);
        return;
    }
    
    CC_SAFE_DELETE(attack);
}

b2Body* Attack::CreatePhysicBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->getPosition().x / PPM, this->getPosition().y / PPM);
    bodyDef.angle = CC_DEGREES_TO_RADIANS(this->getRotation());
    bodyDef.linearDamping = 0;
    bodyDef.angularDamping = 0;
    bodyDef.userData = this;

    b2Body* body = PhysicHelper::world->CreateBody(&bodyDef);
    assert(body != NULL);

    b2CircleShape circle; 
    if (weaponType == Weapon::MELEE) {
        circle.m_radius = 8 * this->getScale() / PPM;
    }
    else {
        circle.m_radius = this->getScale() / PPM;
    }

    b2FixtureDef shapeDef;
    shapeDef.shape = &circle;
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.0f;
    shapeDef.isSensor = true;
    body->CreateFixture(&shapeDef);
    b2MassData data;
    body->GetMassData(&data);
    data.mass = 2;
    body->SetMassData(&data);
    return body;
}