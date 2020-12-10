#include "Attack.h"
#include "Definitions.h"
#include "PhysicHelper.h"
#include "InputListener.h"

USING_NS_CC;

Attack::Attack() {

}

void Attack::StartMeleeAttack(Vec2 position, Vec2 target, ContactListener::BodyTag creatorTag, Item* weapon) {
    Attack* attack = new Attack();
    if (attack && attack->initWithFile("res/effects/hit/slash_1.png")) {
        attack->setPosition(position);
        attack->setRotation(CC_RADIANS_TO_DEGREES(-InputListener::Instance()->mousePosition.getAngle()));
        attack->setTag(ContactListener::ATTACK);
        attack->tag = creatorTag;
        attack->setScale(2);
        Director::getInstance()->getRunningScene()->addChild(attack);

        if (weapon) {
            attack->weapon = weapon;
        }
        else {
            std::map<std::string, int> stats{
                {"damage", 5},
                {"speed", 5}
            };
            Item* newWeapon = Item::create(Item::WEAPON, "", "", "", stats);
            attack->weapon = newWeapon;
        }

        cocos2d::DelayTime* microDelay = cocos2d::DelayTime::create(0.01);
        auto startAttack = CallFunc::create([attack]() {
            attack->setName("");
            attack->CreatePhysicBody();
        });
        auto endAttack = CallFunc::create([attack]() {
            attack->setName(DEAD_TAG);
        });

        auto seq = cocos2d::Sequence::create(startAttack, microDelay, endAttack, nullptr);

        attack->runAction(seq);
        log("111");
        return;
    }
    CC_SAFE_DELETE(attack);
}

void Attack::CreatePhysicBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(this->getPosition().x / PPM, this->getPosition().y / PPM);
    //bodyDef.angle = CC_DEGREES_TO_RADIANS(sprite->getRotation());
    bodyDef.linearDamping = 10.0f;
    bodyDef.angularDamping = 10.0f;
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
    log("222");
}