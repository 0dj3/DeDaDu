#include "Weapon.h"
#include "Definitions.h"
#include "Attack.h"

USING_NS_CC;

Weapon::Weapon() {
    type = WEAPON;
}

Weapon* Weapon::create(WeaponType weaponType, std::string filename, ContactListener::BodyTag userTag, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed)
{
    Weapon* newWeapon = new Weapon();
    if (newWeapon->initWithFile(filename)) {
        newWeapon->getTexture()->setAliasTexParameters();
        newWeapon->setScale(2.0);
        newWeapon->weaponType = weaponType;
        newWeapon->filename = filename;
        newWeapon->userTag = userTag;
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
    return create(weapon->weaponType, weapon->filename, weapon->userTag, weapon->projectileFilename, weapon->soundFilename, weapon->damage, weapon->delay, weapon->attackRange, weapon->speed);
}

Weapon* Weapon::createMelee(std::string filename, ContactListener::BodyTag userTag, std::string projectileFilename, std::string soundFilename, int damage, double delay)
{
    return create(MELEE, filename, userTag, projectileFilename, soundFilename, damage, delay, 0, 0);
}

Weapon* Weapon::createRange(std::string filename, ContactListener::BodyTag userTag, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed)
{
    return create(RANGE, filename, userTag, projectileFilename, soundFilename, damage, delay, attackRange, speed);
}

void Weapon::Attack(cocos2d::Vec2 position, cocos2d::Vec2 localTarget, ContactListener::BodyTag creatorTag) {
    Attack::CreateProjectile(position, localTarget, creatorTag, this);
    AudioEngine::preload(soundFilename);
    AudioEngine::play2d(soundFilename, false, 0.1);
}