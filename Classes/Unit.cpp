#include "Unit.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "InputListener.h"
#include "DeathScreen.h"
#include "HUD.h"
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
	if (dmgsound != NULL)
	{
		AudioEngine::preload(dmgsound);
		AudioEngine::play2d(dmgsound, false, 0.5);
	}
	else
	{
		CCLOG("Soundless Unit");
	}
	
	if (hp <= value) {
		if (tag == ContactListener::PLAYER)
		{
			AudioEngine::stopAll();
			Node::stopAllActions();
			InputListener::Instance()->ReleaseAllKeys();
			AudioEngine::preload("res/sounds/ds.mp3");
			auto scene = DeathScreen::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		}
		else
		{
			Dead();
		}
		return;
	}
	hp -= value;
}

void Unit::Dead() 
{	
	//this->removeFromParentAndCleanup(true);
	this->setName(DEAD_TAG);
}