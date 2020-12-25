#include "Unit.h"
#include "AudioEngine.h"
#include "MainMenuScene.h"
#include "InputListener.h"
#include "HUD.h"
#include <string>
#include <cmath>
#include "GameManager.h"
USING_NS_CC;

MainMenuScene* settings = new MainMenuScene;

Unit::Unit()
{
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
		Dead();
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
	this->setName(DEAD_TAG);
}

void Unit::CheckMaxHP() {
	if (maxHP != startHP * stats->hp) {
		maxHP = startHP * stats->hp;
		//hp = maxHP;
	}
}

void Unit::loadStats() {
	std::ifstream ifs("Resources/properties/balance.json");
	rapidjson::IStreamWrapper isw(ifs);

	rapidjson::Document stats;
	stats.ParseStream(isw);
	assert(stats.IsObject());

	assert(stats.HasMember("player_hp"));
	assert(stats["player_hp"].IsInt());

	startHP = stats["player_hp"].GetInt();
	maxHP = startHP;
	hp = maxHP;
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