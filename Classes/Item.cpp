#include "Item.h"
#include "Definitions.h"
USING_NS_CC;

Item::Item()
{
    setTag(ContactListener::ITEM);
}

void Item::DropItem(Vec2 position)
{
    setPosition(position);
    setName("");
    CreatePhysicBody();

    //b2Body* body = PhysicHelper::createDynamicPhysicBody(this, this->getContentSize());
}

void Item::Sell(cocos2d::Vec2 position, int price) {
    setPosition(position);
    isForSale = true;
    this->price = price;
    b2Body* body = CreatePhysicBody();
    body->SetType(b2_staticBody);
    Label* counter = Label::createWithTTF(std::to_string(price), "fonts/Pixel Times.ttf", 20);
    counter->getFontAtlas()->setAliasTexParameters();
    counter->setHorizontalAlignment(TextHAlignment::CENTER);
    counter->setColor(Color3B::YELLOW);
    counter->setPosition(Vec2(this->getContentSize().width / 2, -this->getContentSize().width / 4));
    counter->setScale(0.5);
    this->addChild(counter);
}

void Item::PickUpItem()
{
    this->setName(DEAD_BODY_TAG);
}

b2Body* Item::CreatePhysicBody()
{
    this->getTexture()->setAliasTexParameters();
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
}