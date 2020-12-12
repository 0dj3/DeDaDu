#include "Unit.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "InputListener.h"
#include "DeathScreen.h"
#include "HUD.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include <rapidjson/istreamwrapper.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
USING_NS_CC;

Unit::Unit()
{
	layer = new Layer();
    sprite = new Sprite();
	stats = new UnitStats();
	this->addChild(sprite);
	this->setName("unit");
	loadStats();
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

	if (value < 0) {
		HUD::DisplayString(this->getPosition(), std::to_string(-value), 15, Color3B(0, 255, 0));
	}
	else {
		HUD::DisplayString(this->getPosition(), std::to_string(value), 15, Color3B(255, 255, 255));
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
	if (hp - value > maxHp) {
		hp = maxHp;
	} else {
		hp -= value;
	}
}

void Unit::Dead() 
{	
	//this->removeFromParentAndCleanup(true);
	this->setName(DEAD_TAG);
}

void Unit::loadStats() {
	std::ifstream ifs("properties/balance.json");
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document stats;
	stats.ParseStream(isw);
	assert(stats.IsObject());

	assert(stats.HasMember("player_hp"));
	assert(stats["player_hp"].IsInt());

	maxHp = stats["player_hp"].GetInt();
	hp = maxHp;
}