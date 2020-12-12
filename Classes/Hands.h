#pragma once
#ifndef __Hands__
#define __Hands__

#include "cocos2d.h"
#include "Item.h"

class Hands : public cocos2d::Node
{
public:
	Hands() {
		handsSprite = new cocos2d::Sprite();
		handsSprite->setScale(2);
		handsSprite->setPosition(cocos2d::Vec2(3 * handsSprite->getScale(), -7 * handsSprite->getScale()));
		handsSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
		this->addChild(handsSprite);
	};

	virtual void PutInHands(Item* item) {
		this->item = item;
		this->handsSprite->setTexture(GetItem()->filename);
		this->handsSprite->getTexture()->setAliasTexParameters();
	};

	Item* GetItem() { return item; };

protected:
	cocos2d::Sprite* handsSprite;
	Item* item = NULL;

};

#endif // __Hands__
