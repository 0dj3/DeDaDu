#include "Potion.h"
#include "Definitions.h"
#include "GameManager.h"
USING_NS_CC;

Potion::Potion() {
    type = POTION;
}

Potion* Potion::create(std::string filename, std::string soundFilename, int value) {
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
}

void Potion::Drink(Unit* unit) {
    unit->Damage(value);
    AudioEngine::preload(soundFilename);
    AudioEngine::play2d(soundFilename, false, GameManager::Instance()->GetSFX());
    removeFromParentAndCleanup(true);
}