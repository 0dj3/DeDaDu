#include "Definitions.h"
#include "Settings.h"
#include "MainMenuScene.h"
#include "AudioEngine.h"

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
    AudioEngine::play2d("res/sounds/bgsound2.mp3", true, 0.1f);

    if (!Scene::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("res/menubg.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

    auto playItem = MenuItemImage::create("res/ui/menu_button.png", "res/ui/menu_button_press.png", CC_CALLBACK_1(Settings::GoToMainMenuScene, this));
    playItem->setPosition(Point(0, 0));

    auto menu = Menu::create(playItem, NULL);
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