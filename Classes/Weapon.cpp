#include "Weapon.h"
#include "Definitions.h"
#include "Attack.h"
#include "GameManager.h"

USING_NS_CC;

Weapon::Weapon() {
    type = WEAPON;
}

Weapon* Weapon::create(WeaponType weaponType, std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, double speed)
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
        newWeapon->speed = speed;
        return newWeapon;
    }
    CC_SAFE_DELETE(newWeapon);
    return NULL;
}

Weapon* Weapon::create(Weapon* weapon)
{
    return create(weapon->weaponType, weapon->filename, weapon->projectileFilename, weapon->soundFilename, weapon->damage, weapon->delay, weapon->speed);
}

Weapon* Weapon::createMelee(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay)
{
    return create(MELEE, filename, projectileFilename, soundFilename, damage, delay, 0);
}

Weapon* Weapon::createRange(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, double speed)
{
    return create(RANGE, filename, projectileFilename, soundFilename, damage, delay, speed);
}

void Weapon::StartAttack(cocos2d::Vec2 position, float angle, Unit* unit) {
    Attack::CreateAttack(projectileFilename, (ContactListener::BodyTag)unit->getTag(), weaponType, position,
        damage * unit->stats->damage, angle, speed, 2, 20);
    AudioEngine::preload(soundFilename);
    AudioEngine::play2d(soundFilename, false, GameManager::Instance()->GetSFX());
}

Weapon* Weapon::GetRandomWeapon() {
    Weapon* weapon;
    switch (rand() % 2)
    {
    case 0:
        weapon = Weapon::createRange("res/weapon/staff1.png", "res/effects/projectile/fire.png", "res/sounds/swoosh.mp3", rand() % 5 + 10, 1, 2);
        break;
    case 1:
        weapon = Weapon::createMelee("res/weapon/sword.png", "res/effects/projectile/slash.png", "res/sounds/swoosh.mp3", rand() % 10 + 20, 1);
        break;
    default:
        break;
    }
    return weapon;
}