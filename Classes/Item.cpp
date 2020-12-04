#include "Item.h"
#include "Definitions.h"
USING_NS_CC;

Item::Item()
{

}

Item* Item::create(ItemType type, std::string title, std::string description, std::string iconPath, std::map<std::string, int> stats)
{
    Item* newItem = new Item();
    if (newItem && !iconPath.empty()) {
        newItem->type = type;
        newItem->title = title;
        newItem->description = description;
        newItem->iconPath = iconPath;
        newItem->stats = stats;
        return newItem;
    }
    CC_SAFE_DELETE(newItem);
    return NULL;
}

Item* Item::create(Item* item)
{
    return create(item->type, item->title, item->description, item->iconPath, item->stats);
}