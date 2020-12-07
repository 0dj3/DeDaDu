#include "Definitions.h"
#include "HUD.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"

USING_NS_CC;

HUD* HUD::create() {
	HUD* hud = new HUD();

	hud->Init();

	return hud;
}

void HUD::Init() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	hBBackground = Sprite::create("res/ui/hpbg.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(-620, 350));
	this->addChild(hBBackground);

	healthBar = ui::LoadingBar::create("res/ui/hp.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(-620, 350));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(100);
	this->addChild(healthBar);

	auto playItem = MenuItemImage::create("res/ui/buttons/exitbutton.png", "res/ui/buttons/exitbutton_press.png", CC_CALLBACK_1(HUD::GoToMenu, this));
	playItem->setPosition(Point(0, 0));

	menubutton = Menu::create(playItem, NULL);
	menubutton->setPosition(Point(600, 320));
	this->addChild(menubutton);
}

void HUD::getHit(int damage, Unit* player) {
	if (player->hp <= 0) {
		player->Dead();
	}
	else {
		player->hp -= damage;
		healthBar->setPercent(player->hp);
	}
}

void HUD::updatePos(Unit* player) 
{
	if (player)
	{
		healthBar->setPercent(player->hp);
		this->setPosition(player->getPosition());
	}
}

void HUD::GoToMenu(cocos2d::Ref* sender)
{
	AudioEngine::stopAll();
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}