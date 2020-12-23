#include "Attack.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "InputListener.h"
#include "AudioEngine.h"

USING_NS_CC;

Attack::Attack() {

}

void Attack::CreateAttack(Vec2 position, Vec2 localTarget, Unit* creator, Weapon* weapon) {
    Attack* attack = new Attack();
    if (attack && attack->initWithFile(weapon->projectileFilename)) {
        attack->getTexture()->setAliasTexParameters();
        attack->setPosition(position);
        attack->setRotation(CC_RADIANS_TO_DEGREES(-localTarget.getAngle()));
        attack->setScale(2);
        attack->setTag(ContactListener::ATTACK);
        attack->creatorTag = (ContactListener::BodyTag)creator->getTag();
        attack->weaponType = weapon->weaponType;
        Director::getInstance()->getRunningScene()->addChild(attack);
        attack->damage = weapon->damage * creator->stats->damage;

        if (weapon->weaponType == Weapon::MELEE) {
            cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.01);
            auto endAttack = CallFunc::create([attack]() {
                attack->setName(DEAD_TAG);
            });
            auto seq = cocos2d::Sequence::create(delay, endAttack, nullptr);
            attack->runAction(seq);
        }

        attack->setName("");
        b2Body* body = attack->CreatePhysicBody();
        b2Vec2 pos = b2Vec2(localTarget.x, localTarget.y);
        pos.Normalize();
        body->ApplyForceToCenter((LINEAR_ACCELERATION) * weapon->speed * PPM * pos, true);
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
    /*b2PolygonShape box;
    box.SetAsBox(this->getContentSize().height * this->getScale() / PPM / 2, this->getContentSize().width * this->getScale() / PPM / 2);*/
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