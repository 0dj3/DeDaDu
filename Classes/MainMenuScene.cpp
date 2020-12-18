#include "MainMenuScene.h"
#include "GameScene.h"
#include "CutScene.h"
#include "Settings.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "InputListener.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    layer->scheduleUpdate();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    InputListener::Instance()->Init(this);

    Settings* settings = new Settings;
    AudioEngine::play2d("res/sounds/bgsound2.mp3", true, settings->getMusicVolume());

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    parallax1 = Sprite::create("res/parallax/prlxback1.png");
    parallax1->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallax1->setScale(0.9);
    this->addChild(parallax1);
    parallax2 = Sprite::create("res/parallax/prlxmiddle1.png");
    parallax2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallax2->setScale(0.9);
    this->addChild(parallax2);
    parallax3 = Sprite::create("res/parallax/prlxfront1.png");
    parallax3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    parallax3->setScale(0.9);
    this->addChild(parallax3);

    auto playItem = MenuItemImage::create("res/ui/buttons/start.png", "res/ui/buttons/start_pressed.png", CC_CALLBACK_1(MainMenuScene::GoToCutScene,this));
    auto settingsItem = MenuItemImage::create("res/ui/buttons/options.png", "res/ui/buttons/options_pressed.png", CC_CALLBACK_1(MainMenuScene::GoToSettings, this));
    auto exitItem = MenuItemImage::create("res/ui/buttons/exit.png", "res/ui/buttons/exit_pressed.png", CC_CALLBACK_1(MainMenuScene::Exit, this));

    auto menu = Menu::create(playItem, settingsItem, exitItem, NULL);
    menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    menu->alignItemsVerticallyWithPadding(50);
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::GoToCutScene(cocos2d::Ref* sender)
{
    AudioEngine::stopAll();
    auto scene = CutScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void MainMenuScene::GoToMainMenu(cocos2d::Ref* sender)
{

}

void MainMenuScene::GoToSettings(cocos2d::Ref* sender)
{
    this->removeChildByName("menu", true);

    auto backItem = MenuItemImage::create("res/ui/buttons/back.png", "res/ui/buttons/back_pressed.png", CC_CALLBACK_1(MainMenuScene::GoToMainMenu, this));
    backItem->setPosition(Point(0, 0));

    auto mBackground = Sprite::create("res/ui/musicbg.png");
    mBackground->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(mBackground);
    musicBar = ui::LoadingBar::create("res/ui/musicbar.png");
    musicBar->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    musicBar->setDirection(ui::LoadingBar::Direction::LEFT);
    musicBar->setPercent(music * 100);
    this->addChild(musicBar);

    auto musicminusItem = MenuItemImage::create("res/ui/buttons/left.png", "res/ui/buttons/left_pressed.png", CC_CALLBACK_1(MainMenuScene::musicMinus, this));
    auto musicplusItem = MenuItemImage::create("res/ui/buttons/right.png", "res/ui/buttons/right_pressed.png", CC_CALLBACK_1(MainMenuScene::musicPlus, this));
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

    auto sfxminusItem = MenuItemImage::create("res/ui/buttons/left.png", "res/ui/buttons/left_pressed.png", CC_CALLBACK_1(MainMenuScene::sfxMinus, this));
    auto sfxplusItem = MenuItemImage::create("res/ui/buttons/right.png", "res/ui/buttons/right_pressed.png", CC_CALLBACK_1(MainMenuScene::sfxPlus, this));
    auto sfxMenu = Menu::create(sfxminusItem, sfxplusItem, NULL);
    sfxMenu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));
    sfxMenu->alignItemsHorizontallyWithPadding(sBackground->getContentSize().width + 10);
    this->addChild(sfxMenu);

    auto menu = Menu::create(backItem, NULL);
    menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 5 + origin.y));
    this->addChild(menu);
}

void MainMenuScene::Exit(cocos2d::Ref* sender)
{
    Director::getInstance()->end();
}

void MainMenuScene::update(float dt)
{
    CCLOG("mouse move %f, %f", InputListener::Instance()->mousePosition.x, InputListener::Instance()->mousePosition.y);
    parallax1->setPosition(Point(((visibleSize.width / 2 + origin.x) - InputListener::Instance()->mousePosition.x * 0.1), 50 + ((visibleSize.height / 2 + origin.y) - InputListener::Instance()->mousePosition.y * 0.1)));
    parallax2->setPosition(Point(((visibleSize.width / 2 + origin.x) - InputListener::Instance()->mousePosition.x * 0.2), 50 + ((visibleSize.height / 2 + origin.y) - InputListener::Instance()->mousePosition.y * 0.1)));
    parallax3->setPosition(Point(((visibleSize.width / 2 + origin.x) - InputListener::Instance()->mousePosition.x * 0.6), 50 + ((visibleSize.height / 2 + origin.y) - InputListener::Instance()->mousePosition.y * 0.1)));
}

void MainMenuScene::musicPlus(cocos2d::Ref* sender)
{
    if (music < 1.0)
    {
        music += 0.1f;
        musicBar->setPercent(music * 100);
        AudioEngine::setVolume(1, music);
    }
}

void MainMenuScene::musicMinus(cocos2d::Ref* sender)
{
    if (music > 0.00f)
    {
        music -= 0.1f;
        musicBar->setPercent(music * 100);
        AudioEngine::setVolume(1, music);
    }
}

void MainMenuScene::sfxPlus(cocos2d::Ref* sender)
{
    if (sfx < 1.0)
    {
        sfx += 0.1f;
        sfxBar->setPercent(sfx * 100);
    }
}

void MainMenuScene::sfxMinus(cocos2d::Ref* sender)
{
    if (sfx > 0.00f)
    {
        sfx -= 0.1f;
        sfxBar->setPercent(sfx * 100);
    }
}

float MainMenuScene::getMusicVolume()
{
    return music;
}

float MainMenuScene::getSFXVolume()
{
    return sfx;
}


double MainMenuScene::getDifficult()
{
    return difficult;
}