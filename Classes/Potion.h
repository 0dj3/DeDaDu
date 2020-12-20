#pragma once
#ifndef __POTION_H__
#define __POTION_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Item.h"
#include "ContactListener.h"

USING_NS_CC;

class Potion : public Item
{
public:
    std::string soundFilename;
    int value;

    Potion() {
        type = POTION;
    };

    static Potion* create(std::string filename, std::string soundFilename, int value) {
        Potion* newPotion = new Potion();
        if (newPotion->initWithFile(filename)) {
            newPotion->getTexture()->setAliasTexParameters();
            newPotion->setScale(2.0);
            newPotion->filename = filename;
            newPotion->soundFilename = soundFilename;
            newPotion->value = value;
            return newPotion;
        }
        CC_SAFE_DELETE(newPotion);
        return NULL;
    };

    void Drink(Unit* unit) {
        unit->Damage(value);
        AudioEngine::preload(soundFilename);
        AudioEngine::play2d(soundFilename, false, GameManager::Instance()->GetSFX());
        removeFromParentAndCleanup(true);
    };

private:

};

#endif // __POTION_H__
