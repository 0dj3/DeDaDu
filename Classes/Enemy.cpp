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

void Unit::Damage(int value) 
{
	AudioEngine::play2d("hit.mp3", false, 1.0);

	if (hp <= value) {
		Dead();
		return;
	}
	hp -= value;
}

void Unit::Dead()
{
	this->removeFromParentAndCleanup(true);
}