#include "Goblin.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"

USING_NS_CC;
Goblin::Goblin()
{
    dmgsound = "res/sounds/hit/goblin.mp3";
    this->autorelease();
}



Enemy* Goblin::create(cocos2d::Layer* layer, const Vec2& position)
{
    Goblin* newGoblin = new Goblin();
    if (newGoblin && newGoblin->sprite->initWithFile("res/enemy/goblin/test_goblin.png"))
    {
        newGoblin->sprite->getTexture()->setAliasTexParameters();
        newGoblin->sprite->setScale(3.0);
        newGoblin->setPosition(position);

        newGoblin->body = PhysicHelper::createDynamicPhysicBody(newGoblin, newGoblin->sprite->getContentSize());

        newGoblin->setTag(newGoblin->tag);
        newGoblin->layer = layer;
        newGoblin->scheduleUpdate();
        return newGoblin;
    }
    CC_SAFE_DELETE(newGoblin);
    return NULL;
}

void Goblin::update(float dt)
{   

}

void Goblin::move()
{
}   
