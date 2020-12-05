#include "DeathScreen.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "Settings.h"

USING_NS_CC;

Scene* DeathScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = DeathScreen::create();
    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.

// on "init" you need to initialize your instance
bool DeathScreen::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    AudioEngine::play2d("res/sounds/ds.mp3", false, 0.5);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(DeathScreen::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    auto backgroundSprite = Sprite::create("res/ds.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    this->addChild(backgroundSprite);

    return true;
}

void DeathScreen::GoToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
