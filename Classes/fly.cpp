#include "Fly.h"
#include "Definitions.h"
#include "Player.h"
#include "Anime.h"
#include "Windows.h"

USING_NS_CC;
Fly::Fly()
{
    dmgsound = "res/sounds/hit/hit.mp3";
}

Enemy* Fly::create(cocos2d::Layer* layer, const cocos2d::Vec2& position)
{
	Fly* fly = new Fly();
	if (fly->init())
	{
		fly->autorelease();
		fly->initFly();
		//fly->body = PhysicHelper::createDynamicPhysicBody(fly, fly->sprite->getContentSize());
		fly->setPosition(position);
		fly->setTag(fly->tag);
		fly->layer = layer;
		fly->scheduleUpdate();
		return fly;
	}
	CC_SAFE_DELETE(fly);
	return NULL;
}

void Fly::initFly()
{
	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/enemy/goblin/goblin.plist");
	//this->addChild(spritesheet)
	// Animation Idle
	idleAnimate = initAnimation(1, 6, 0.1f);
	idleAnimate->retain();
	setScaleY(3.0);
	setScaleX(-3.0);
}

Animate* Fly::initAnimation(int initIndex, int finIndex, float dt)
{
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int i = 1; i <= 4; i++) {
		sprintf(str, "idle_%i.png",i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

void Fly::update(float dt)
{   
	idle();
}

void Fly::idle() {
	this->runAction(RepeatForever::create(idleAnimate));
}

void Fly::move()
{
}   
