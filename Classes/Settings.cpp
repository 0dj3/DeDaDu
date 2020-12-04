#include "Definitions.h"
#include "Settings.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* Settings::createScene()
{
    auto scene = Scene::create();
    auto layer = Settings::create();
    scene->addChild(layer);
    return scene;
}

bool Settings::init()
{
    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->scheduleUpdate();

    auto vBackground = Sprite::create("res/ui/sound_bg.png");
    vBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(vBackground);

    volumeBar = ui::LoadingBar::create("res/ui/sound.png");
    volumeBar->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    volumeBar->setDirection(ui::LoadingBar::Direction::LEFT);
    volumeBar->setPercent(volume*100);
    this->addChild(volumeBar);

    auto backItem = MenuItemImage::create("res/ui/back.png", "res/ui/back_pressed.png", CC_CALLBACK_1(Settings::GoToMainMenuScene, this));
    backItem->setPosition(Point(0, 0));

    auto volumeminusItem = MenuItemImage::create("res/ui/left.png", "res/ui/left.png", CC_CALLBACK_1(Settings::volumeMinus, this));
    //volumeminusItem->setPosition(Point(-100, 0));
    auto volumeplusItem = MenuItemImage::create("res/ui/right.png", "res/ui/right.png", CC_CALLBACK_1(Settings::volumePlus, this));
    //volumeplusItem->setPosition(Point(100, 0));

    auto volumeMenu = Menu::create(volumeminusItem, volumeplusItem, NULL);
    volumeMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    volumeMenu->alignItemsHorizontallyWithPadding(vBackground->getContentSize().width + 10);
    this->addChild(volumeMenu);


    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    this->addChild(menu);

    return true;
}

void Settings::GoToMainMenuScene(cocos2d::Ref* sender)
{
    AudioEngine::stopAll();
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void Settings::volumePlus(cocos2d::Ref* sender)
{
    if (volume < 1.0)
    {
        volume += 0.1f;
        volumeBar->setPercent(volume*100);
    } 
}

void Settings::volumeMinus(cocos2d::Ref* sender)
{
    if (volume > 0.00f)
    {
        volume -= 0.1f;
        volumeBar->setPercent(volume * 100);
    }
}

float Settings::getVolume()
{
    return volume;
}

double Settings::getDifficult()
{
    return difficult;
}

void Settings::update(float dt)
{ }