#include "DeathScreen.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* DeathScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = DeathScreen::create();
    scene->addChild(layer);
    return scene;
}

bool DeathScreen::init()
{
    std::ifstream ifs("Resources/properties/data.json");
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("death_progress"));
    assert(doc["death_progress"].IsInt());
    progress = doc["death_progress"].GetInt();
    CCLOG("%d", progress);

    if ( !Scene::init() )
    {
        return false;
    }			
    MainMenuScene* settings = new MainMenuScene;
    AudioEngine::play2d("res/sounds/ds.mp3", false, settings->getMusicVolume());
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //switch (progress)
    //{
    //case 0: {
    //    str = "You need to rest, stranger...";
    //    progress = 1;
    //    doc["death_progress"].SetInt(progress);
    //    std::ofstream ofs("Resources/properties/data.json");
    //    rapidjson::OStreamWrapper osw(ofs);
    //    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    //    doc.Accept(writer);
    //}
    //      break;
    //case 1: {
    //    str = "So, next time...";
    //    //in razrabotke
    //}
    //default:
    //    str = "COMING SOON";
    //    break;
    //}

    if (progress == 0)
    {
        str = "You need to rest, stranger...";
            progress = 1;
            doc["death_progress"].SetInt(progress);
            std::ofstream ofs("Resources/properties/data.json");
            rapidjson::OStreamWrapper osw(ofs);
            rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
            doc.Accept(writer);
    }
    if (progress == 1)
    {
        str = "So, next time...";
    }

    auto label = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 30);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(label);

    auto FadeIn = FadeIn::create(1.0f);
    label->runAction(FadeIn);

    auto fadeOut = FadeOut::create(0.5f);
    label->runAction(fadeOut);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(DeathScreen::GoToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);

    return true;
}

void DeathScreen::GoToMainMenuScene(float dt)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
