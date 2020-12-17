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

	virtual void PutInHands(Item* item) {
		this->item = item;
		this->item->setName(DEAD_BODY_TAG);
		this->handsSprite->setTexture(GetItem()->filename);
		this->handsSprite->getTexture()->setAliasTexParameters();
	};

	void UseItem(cocos2d::Vec2 position, cocos2d::Vec2 localTarget, ContactListener::BodyTag creatorTag) {
		if (isDelay || item == NULL)
			return;
		cocos2d::DelayTime* delay = cocos2d::DelayTime::create(item->delay);
		auto startCD = cocos2d::CallFunc::create([this]() {
			isDelay = true;
			});
		auto endCD = cocos2d::CallFunc::create([this]() {
			isDelay = false;
			});
		auto seq = cocos2d::Sequence::create(startCD, delay, endCD, nullptr);
		this->runAction(seq);

		switch (item->type)	
		{
		case Item::WEAPON:
			static_cast<Weapon*>(item)->Attack(position, localTarget, creatorTag);
			break;
		case Item::POTION:
			//static_cast<Potion*>(item)->Drink(unit);
			break;
		default:
			break;
		}
	};

	Item* GetItem() { return item; };

	bool IsDelay() { return isDelay; };

protected:
	Unit* unit = NULL;
	bool isDelay = false;
	cocos2d::Sprite* handsSprite;
	Item* item = NULL;

};

#endif // __Hands__
