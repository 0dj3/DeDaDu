#include "Unit.h"
#include "Definitions.h"

USING_NS_CC;

Unit::Unit()
{
	scene = new Layer();
    sprite = new Sprite();
	this->addChild(sprite);
}