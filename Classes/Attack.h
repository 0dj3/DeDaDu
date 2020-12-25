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

	static void CreateAttack(cocos2d::Vec2 position, float angle, Unit* creator, Weapon* weapon);

	ContactListener::BodyTag GetCreatorTag() { return creatorTag; };
	int GetDamage() { return damage; };
	Weapon::WeaponType GetWeaponType() { return weaponType; };

private:
	Weapon::WeaponType weaponType;
	int damage;
	ContactListener::BodyTag creatorTag;

	b2Body* CreatePhysicBody();

};

#endif // __ATTACK_H__
