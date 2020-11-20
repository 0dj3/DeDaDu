#include "Enemy.h"
#include "Definitions.h"
#include "AudioEngine.h"
USING_NS_CC;

Enemy::Enemy()
{
	layer = new Layer();
	sprite = new Sprite();
	stats = new UnitStats();
	this->addChild(sprite);
}