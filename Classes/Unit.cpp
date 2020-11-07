#include "Unit.h"
#include "Definitions.h"

USING_NS_CC;

Unit::Unit()
{
	layer = new Layer();
    sprite = new Sprite();
	stats = new UnitStats();
	this->addChild(sprite);
}

void Unit::Damage(int value) {
	if (hp <= value) {
		Dead();
		return;
	}
	hp -= value;
}

void Unit::Dead() {

}