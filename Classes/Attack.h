#pragma once
#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Unit.h"
#include "Weapon.h"
#include "Item.h"
#include "ContactListener.h"

class Attack : public cocos2d::Sprite
{
public:
	Attack();

	static void CreateAttack(std::string projectileFilename, ContactListener::BodyTag creatorTag, Weapon::WeaponType weaponType, 
		cocos2d::Vec2 position, int damage, double angle, double speed, double size, int scatter);

	ContactListener::BodyTag GetCreatorTag() { return creatorTag; };
	int GetDamage() { return damage; };
	Weapon::WeaponType GetWeaponType() { return weaponType; };

private:
	int damage;
	ContactListener::BodyTag creatorTag;
	Weapon::WeaponType weaponType;

	b2Body* CreatePhysicBody();

};

#endif // __ATTACK_H__
