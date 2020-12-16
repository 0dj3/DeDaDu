#pragma once
#ifndef __ATTACK_H__
#define __ATTACK_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Unit.h"
#include "Item.h"

class Attack : public cocos2d::Sprite
{
public:
	Attack();

	static void StartMeleeAttack(cocos2d::Vec2 position, cocos2d::Vec2 localTarget, ContactListener::BodyTag creatorTag, Item* weapon);

	ContactListener::BodyTag GetCreatorTag() { return tag; };
	int GetDamage() { return weapon->stats.find("damage")->second; };

private:
	Item* weapon;
	ContactListener::BodyTag tag;

	void CreatePhysicBody();

};

#endif // __ATTACK_H__
