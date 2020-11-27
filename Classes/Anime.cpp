#include "Definitions.h"
#include "Anime.h"

USING_NS_CC;

Anime::Anime()
{

}

void Anime::runAnimation()
{
	char str[200] = { 0 };
	Vector<SpriteFrame*> runFrames(frame);

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(pathPlist);

	for (int _i = 1; _i <= frame; _i++) {
		sprintf(str, "run_%d.png", _i);
		runFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto runAnimation = Animation::createWithSpriteFrames(runFrames, 0.1f);
	auto runAnimate = Animate::create(runAnimation);
	runAnimate->retain();

	this->runAction(RepeatForever::create(runAnimate));
}

void Anime::idleAnimation()
{
	char str[200] = { 0 };
	Vector<SpriteFrame*> idleFrames(frame);

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(pathPlist);

	for (int _i = 1; _i <= frame; _i++) {
		sprintf(str, "idle_%d.png", _i);
		idleFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto idleAnimation = Animation::createWithSpriteFrames(idleFrames, 0.1f);
	auto idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain();

	this->runAction(RepeatForever::create(idleAnimate));
}

void Anime::dieAnimation()
{
	char str[200] = { 0 };
	Vector<SpriteFrame*> deadFrames(4);

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/effects/dead/dead.plist");

	for (int _i = 1; _i <= 4; _i++) {
		sprintf(str, "dead_%d.png", _i);
		deadFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrames, 0.1f);
	auto deadAnimate = Animate::create(deadAnimation);
	deadAnimate->retain();

	this->runAction(deadAnimate);
}