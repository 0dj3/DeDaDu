#include "Weapon.h"
#include "Definitions.h"
#include "Attack.h"

USING_NS_CC;

Weapon::Weapon() {
    type = WEAPON;
    loadSettings();
}

Weapon* Weapon::create(WeaponType weaponType, std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed)
{
    Weapon* newWeapon = new Weapon();
    if (newWeapon->initWithFile(filename)) {
        newWeapon->getTexture()->setAliasTexParameters();
        newWeapon->setScale(2.0);
        newWeapon->weaponType = weaponType;
        newWeapon->filename = filename;
        newWeapon->projectileFilename = projectileFilename;
        newWeapon->soundFilename = soundFilename;
        newWeapon->damage = damage;
        newWeapon->delay = delay;
        newWeapon->attackRange = attackRange;
        newWeapon->speed = speed;
        return newWeapon;
    }
    CC_SAFE_DELETE(newWeapon);
    return NULL;
}

Weapon* Weapon::create(Weapon* weapon)
{
    return create(weapon->weaponType, weapon->filename, weapon->projectileFilename, weapon->soundFilename, weapon->damage, weapon->delay, weapon->attackRange, weapon->speed);
}

Weapon* Weapon::createMelee(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay)
{
    return create(MELEE, filename, projectileFilename, soundFilename, damage, delay, 0, 0);
}

Weapon* Weapon::createRange(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed)
{
    return create(RANGE, filename, projectileFilename, soundFilename, damage, delay, attackRange, speed);
}

void Weapon::StartAttack(cocos2d::Vec2 position, cocos2d::Vec2 localTarget, Unit* unit) {
    Attack::CreateAttack(position, localTarget, unit, this);
    AudioEngine::preload(soundFilename);
    AudioEngine::play2d(soundFilename, false, sfx);
}

Weapon* Weapon::GetRandomWeapon() {
    Weapon* weapon;
    switch (rand() % 2)
    {
    case 0:
        weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/fire.png", "res/sounds/swoosh.mp3", rand() % 5 + 10, 1, 3, 5);
        break;
    case 1:
        weapon = Weapon::createMelee("res/weapon/sword.png", "res/effects/projectile/slash.png", "res/sounds/swoosh.mp3", rand() % 10 + 20, 1);
        break;
    default:
        weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/fire.png", "res/sounds/swoosh.mp3", rand() % 5 + 10, 1, 3, 5);
        break;
    }
    return weapon;
}

void Weapon::loadSettings()
{
    std::ifstream ifs("../Resources/properties/data.json");
    rapidjson::IStreamWrapper isw(ifs);
    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("sfx"));
    assert(doc["sfx"].IsFloat());
    sfx = doc["sfx"].GetFloat();
}