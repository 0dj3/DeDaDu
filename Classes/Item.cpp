#include "Item.h"
#include "Definitions.h"
#include "PhysicHelper.h"
USING_NS_CC;

Item::Item()
{

}

Item* Item::create(ItemType type, std::string title, std::string description, std::string filename, std::map<std::string, int> stats)
{
    Item* newItem = new Item();
    if (newItem->initWithFile(filename)) {
        newItem->getTexture()->setAliasTexParameters();
        newItem->setScale(2.0);
        newItem->type = type;
        newItem->title = title;
        newItem->description = description;
        newItem->filename = filename;
        newItem->stats = stats;
        newItem->setTag(ContactListener::ITEM);
        return newItem;
    }
    CC_SAFE_DELETE(newItem);
    return NULL;
}

Item* Item::create(Item* item)
{
    return create(item->type, item->title, item->description, item->filename, item->stats);
}

void Item::DropItem(Vec2 position)
{
    setPosition(position);
    setName("");
    CreatePhysicBody();

    //b2Body* body = PhysicHelper::createDynamicPhysicBody(this, this->getContentSize());
}

void Item::PickUpItem()
{
    this->setName(DEAD_BODY_TAG);
}

void Item::CreatePhysicBody()
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
    body->CreateFixture(&shapeDef);
}