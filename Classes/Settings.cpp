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
 
    auto backItem = MenuItemImage::create("res/ui/buttons/back.png", "res/ui/buttons/back_pressed.png", CC_CALLBACK_1(Settings::GoToMainMenuScene, this));
    backItem->setPosition(Point(0, 0));

    auto mBackground = Sprite::create("res/ui/musicbg.png");
    mBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(mBackground);
    musicBar = ui::LoadingBar::create("res/ui/musicbar.png");
    musicBar->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    musicBar->setDirection(ui::LoadingBar::Direction::LEFT);
    musicBar->setPercent(music * 100);
    this->addChild(musicBar);

    auto musicminusItem = MenuItemImage::create("res/ui/buttons/left.png", "res/ui/buttons/left_pressed.png", CC_CALLBACK_1(Settings::musicMinus, this));
    auto musicplusItem = MenuItemImage::create("res/ui/buttons/right.png", "res/ui/buttons/right_pressed.png", CC_CALLBACK_1(Settings::musicPlus, this));
    auto musicMenu = Menu::create(musicminusItem, musicplusItem, NULL);
    musicMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    musicMenu->alignItemsHorizontallyWithPadding(mBackground->getContentSize().width + 10);
    this->addChild(musicMenu);

    auto sBackground = Sprite::create("res/ui/sfxbg.png");
    sBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    this->addChild(sBackground);
    sfxBar = ui::LoadingBar::create("res/ui/sfxbar.png");
    sfxBar->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    sfxBar->setDirection(ui::LoadingBar::Direction::LEFT);
    sfxBar->setPercent(sfx * 100);
    this->addChild(sfxBar);

    auto sfxminusItem = MenuItemImage::create("res/ui/buttons/left.png", "res/ui/buttons/left_pressed.png", CC_CALLBACK_1(Settings::sfxMinus, this));
    auto sfxplusItem = MenuItemImage::create("res/ui/buttons/right.png", "res/ui/buttons/right_pressed.png", CC_CALLBACK_1(Settings::sfxPlus, this));
    auto sfxMenu = Menu::create(sfxminusItem, sfxplusItem, NULL);
    sfxMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    sfxMenu->alignItemsHorizontallyWithPadding(sBackground->getContentSize().width + 10);
    this->addChild(sfxMenu);

    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 5 + origin.y));
    this->addChild(menu);

    return true;
}

void Settings::GoToMainMenuScene(cocos2d::Ref* sender)
{
    AudioEngine::stopAll();
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void Settings::musicPlus(cocos2d::Ref* sender)
{
    if (music < 1.0)
    {
        music += 0.1f;
        musicBar->setPercent(music *100);
        AudioEngine::setVolume(1, music);
    } 
}

void Settings::musicMinus(cocos2d::Ref* sender)
{
    if (music > 0.00f)
    {
        music -= 0.1f;
        musicBar->setPercent(music * 100);
        AudioEngine::setVolume(1, music);
    }
}

void Settings::sfxPlus(cocos2d::Ref* sender)
{
    if (sfx < 1.0)
    {
        sfx += 0.1f;
        sfxBar->setPercent(sfx * 100);
    }
}

void Settings::sfxMinus(cocos2d::Ref* sender)
{
    if (sfx > 0.00f)
    {
        sfx -= 0.1f;
        sfxBar->setPercent(sfx * 100);
    }
}

float Settings::getMusicVolume()
{
    return music;
}

float Settings::getSFXVolume()
{
    return sfx;
}


double Settings::getDifficult()
{
    return difficult;
}

void Settings::update(float dt)
{ }