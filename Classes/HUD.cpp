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
	hBBackground = Sprite::create("res/ui/block2.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(-50, 650));
	hBBackground->setScale(0.5);
	this->addChild(hBBackground);

	healthBar = ui::LoadingBar::create("res/ui/block.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(-50, 650));
	healthBar->setScale(0.5);
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(health);
	this->addChild(healthBar);

	auto playItem = MenuItemImage::create("res/ui/menu_button.png", "res/ui/menu_button_press.png", CC_CALLBACK_1(HUD::GoToMenu, this));
	playItem->setPosition(Point(0, 0));
	menubutton = Menu::create(playItem, NULL);
	menubutton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
	this->addChild(menubutton);
}

void HUD::getHit(int damage, Unit* player) {
	if (health <= 0) {
		player->Dead();
	}
	else {
		player->hp -= damage;
		healthBar->setPercent(player->hp);
	}
}

void HUD::updatePos(Unit* player) 
{
	float x = player->getPosition().x;
	float y = player->getPosition().y;
	hBBackground->setPosition(Point(x - 500, y + 300));
	healthBar->setPosition(Point(x - 500,y + 300));
	menubutton->setPosition(Point(x + 500, y + 300));
}

void HUD::GoToMenu(cocos2d::Ref* sender)
{
	AudioEngine::stopAll();
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}