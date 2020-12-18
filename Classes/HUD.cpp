#include "Definitions.h"
#include "HUD.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "Hands.h"
#include "Item.h"
#include "Weapon.h"

USING_NS_CC;

HUD* HUD::create(Player* player) {
	HUD* hud = new HUD();
	hud->playerHUD = player;
	hud->Init();
	hud->scheduleUpdate();
	return hud;
}

void HUD::Init() 
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//////////////////////// Weapon slot

	weaponSlot = Sprite::create("res/ui/selected_slot.png");
	weaponSlot->setPosition(Point(-620, -350));
	weaponSlot->setAnchorPoint(Point(0, 0));
	this->addChild(weaponSlot);

	weaponSprite = Sprite::create("res/ui/selected_slot.png");
	weaponSprite->setScale(3.0);
	weaponSprite->setPosition(Point(-540, -275));
	this->addChild(weaponSprite);

	damagestats = Label::createWithTTF("0", "fonts/Pixel Times.ttf", 30);
	damagestats->setAnchorPoint(Point(0, 1));
	damagestats->setPosition(Point(500, -240));
	this->addChild(damagestats);

	delaystats = Label::createWithTTF("0", "fonts/Pixel Times.ttf", 30);
	delaystats->setAnchorPoint(Point(0, 1));
	delaystats->setPosition(Point(500, -275));
	this->addChild(delaystats);


	////////////////////////

	hBBackground = Sprite::create("res/ui/hpbg.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(-620, 350));
	this->addChild(hBBackground);

	coinBar = Sprite::create("res/ui/coins.png");
	coinBar->setAnchorPoint(Point(0, 1));
	coinBar->setScale(0.8);
	coinBar->setPosition(Point(-620, 315));
	this->addChild(coinBar);

	char str[200] = { 0 };
	sprintf(str, "%d", playerHUD->gold);
	counter = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 27);
	counter->setAnchorPoint(Point(0, 1));
	counter->setPosition(Point(-580, 303));
	this->addChild(counter);

	hBBackground = Sprite::create("res/ui/hpbg.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(-620, 350));
	this->addChild(hBBackground);

	healthBar = ui::LoadingBar::create("res/ui/hp.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(-620, 350));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(playerHUD->hp);
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
		healthBar->setPercent(player->hp / player->maxHp);
	}
}

void HUD::GoToMenu(cocos2d::Ref* sender)
{
	AudioEngine::stopAll();
	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void HUD::setGold(int x)
{
	playerHUD->gold += x;
}

void HUD::update(float dt)
{
	if (playerHUD)
	{
		healthBar->setPercent(playerHUD->hp);
		this->setPosition(playerHUD->getPosition());

		removeChild(counter, true);
		char counter_str[200] = { 0 };
		sprintf(counter_str, "%d", playerHUD->gold);
		counter = Label::createWithTTF(counter_str, "fonts/Pixel Times.ttf", 27);
		counter->setAnchorPoint(Point(0, 1));
		counter->setPosition(Point(-580, 303));
		this->addChild(counter);

		if (playerHUD->hands->GetItem() != NULL) {
			weaponSprite->setTexture(playerHUD->hands->GetItem()->filename);
			weaponSprite->getTexture()->setAliasTexParameters();

			if (playerHUD->hands->GetItem()->type == Item::WEAPON) {
				char damage_str[200] = { 0 };
				sprintf(damage_str, "dmg: %i", static_cast<Weapon*>(playerHUD->hands->GetItem())->damage);
				damagestats->setString(damage_str);

				char delay_str[200] = { 0 };
				sprintf(delay_str, "del: %.2f s", static_cast<Weapon*>(playerHUD->hands->GetItem())->delay);
				delaystats->setString(delay_str);
			}
		}
		
	}
}

void HUD::DisplayString(Vec2 position, std::string value, int fontSize, Color3B color)
{
	Label* counter = Label::createWithTTF(value, "fonts/Pixel Times.ttf", fontSize);
	counter->setColor(color);
	counter->setPosition(Vec2(position.x - 30 + rand() % 60, position.y - 5 + rand() % 10));
	Director::getInstance()->getRunningScene()->addChild(counter);
	auto moveBy = MoveBy::create(2, Vec2(0, 40));
	auto fadeOut = FadeOut::create(3.0f);
	auto spawn = cocos2d::Spawn::create(moveBy, fadeOut, nullptr);
	auto end = CallFunc::create([counter]() {
		counter->removeFromParentAndCleanup(true);
	});
	auto seq = cocos2d::Sequence::create(spawn, end, nullptr);
	counter->runAction(seq);
}