#include "Unit.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "InputListener.h"
#include "DeathScreen.h"
#include "HUD.h"
#include <string>
#include <cmath>
#include "GameManager.h"
USING_NS_CC;

MainMenuScene* settings = new MainMenuScene;

Unit::Unit()
{
	maxHP = START_HP;
	hp = maxHP;
	layer = new Layer();
    sprite = new Sprite();
	stats = new UnitStats(1, 1, 1, 1);
	this->addChild(sprite);
	this->setName("unit");
	loadStats();
}

void Unit::Damage(int value) {
	if (value >= 0 && IsInvulnerable())
		return;
	if (dmgsound != nullptr)
	{
		AudioEngine::preload(dmgsound);
		AudioEngine::play2d(dmgsound, false, GameManager::Instance()->GetSFX());
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
	if (hp - value > maxHP) {
		hp = maxHP;
	} else {
		hp -= value;
	}
}

void Unit::Dead() 
{	
	//this->removeFromParentAndCleanup(true);
	this->setName(DEAD_TAG);
}

void Unit::CheckMaxHP() {
	if (maxHP != START_HP * stats->hp) {
		maxHP = START_HP * stats->hp;
		//hp = maxHP;
	}
}

void Unit::loadStats() {
	std::ifstream ifs("properties/balance.json");
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document stats;
	stats.ParseStream(isw);
	assert(stats.IsObject());

	assert(stats.HasMember("player_hp"));
	assert(stats["player_hp"].IsInt());

	/*maxHp = stats["player_hp"].GetInt();
	hp = maxHp;*/

}

void Unit::SetInvulnerable(double time) {
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(time);
	auto startInvulnerable = CallFunc::create([this]() {;
		isInvulnerable = true;
	});
	auto endInvulnerable = CallFunc::create([this]() {;
		isInvulnerable = false;
	});
	auto seq = cocos2d::Sequence::create(startInvulnerable, delay, endInvulnerable, nullptr);
	this->runAction(seq);
}