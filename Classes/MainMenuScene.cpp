#include "MainMenuScene.h"
#include "GameScene.h"
#include "Settings.h"
#include "Definitions.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
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
    Settings* settings = new Settings;
    AudioEngine::play2d("res/sounds/bgsound2.mp3", true, settings->getVolume());
    //char* asd = " ";
    //sprintf(asd,"%lf",settings->getVolume());
    //CCLOG(asd);
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //auto backgroundSprite = Sprite::create("res/menubg.png");
    //backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    //this->addChild(backgroundSprite);

    auto playItem = MenuItemImage::create("res/ui/start.png", "res/ui/start_pressed.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene,this));
    auto settingsItem = MenuItemImage::create("res/ui/options.png", "res/ui/options_pressed.png", CC_CALLBACK_1(MainMenuScene::GoToSettings, this));
    auto exitItem = MenuItemImage::create("res/ui/exit.png", "res/ui/exit_pressed.png", CC_CALLBACK_1(MainMenuScene::Exit, this));

    auto menu = Menu::create(playItem, settingsItem, exitItem, NULL);
    menu->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    menu->alignItemsVerticallyWithPadding(50);
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* sender)
{
    AudioEngine::stopAll();
    auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}

void MainMenuScene::GoToSettings(cocos2d::Ref* sender)
{
    auto scene = Settings::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::Exit(cocos2d::Ref* sender)
{
    Director::getInstance()->end();
}