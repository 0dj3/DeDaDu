#include "Unit.h"
#include "Definitions.h"
#include "Anime.h"
#include "AudioEngine.h"
USING_NS_CC;

Unit::Unit()
{
	layer = new Layer();
    sprite = new Sprite();
	stats = new UnitStats();
	this->addChild(sprite);
	this->setName("unit");
}

void Unit::Damage(int value) {
	AudioEngine::preload(dmgsound);
	AudioEngine::play2d(dmgsound, false, 0.5);
	
	if (hp <= value) {
		Dead();
		return;
	}
	hp -= value;
}

void Unit::Dead() 
{	
	//this->removeFromParentAndCleanup(true);
	isDead = true;
}