#pragma once
#ifndef __Hands__
#define __Hands__

#include "cocos2d.h"
#include "Item.h"
#include "Attack.h"
#include "Weapon.h"
#include "Potion.h"

class Hands : public cocos2d::Node
{
public:
	Hands(Unit* unit) {
		this->unit = unit;
		handsSprite = new cocos2d::Sprite();
		handsSprite->setScale(2);
		handsSprite->setPosition(cocos2d::Vec2(3 * handsSprite->getScale(), -7 * handsSprite->getScale()));
		handsSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		this->addChild(handsSprite);
	};

	virtual void PutInHands(Weapon* weapon) {
		this->weapon = weapon;
		this->weapon->setName(DEAD_BODY_TAG);
		this->handsSprite->setTexture(weapon->filename);
		this->handsSprite->getTexture()->setAliasTexParameters();
	};

	void UseItem(cocos2d::Vec2 position, float angle) {
		if (isDelay || weapon == NULL)
			return;
		cocos2d::DelayTime* delay = cocos2d::DelayTime::create(weapon->delay / unit->stats->attackSpeed);
		auto startCD = cocos2d::CallFunc::create([this]() {
			isDelay = true;
			});
		auto endCD = cocos2d::CallFunc::create([this]() {
			isDelay = false;
			});
		auto seq = cocos2d::Sequence::create(startCD, delay, endCD, nullptr);
		this->runAction(seq);
		weapon->StartAttack(position, angle, unit);
	};

	Weapon* GetWeapon() { return weapon; };

	bool IsDelay() { return isDelay; };
	cocos2d::Sprite* handsSprite;
protected:
	Unit* unit = NULL;
	bool isDelay = false;
	Weapon* weapon = NULL;

};

#endif // __Hands__
