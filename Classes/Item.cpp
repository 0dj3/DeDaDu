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
    this->setPosition(position);
    this->setName("");
    b2Body* body = PhysicHelper::createDynamicPhysicBody(this, this->getContentSize());
}

void Item::PickUpItem()
{
    this->setName(DEAD_BODY_TAG);
}

void Item::CreatePhysicBody(Vec2 position)
{
    
}