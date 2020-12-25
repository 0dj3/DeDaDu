#include "CutScene.h"
#include "GameScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CutScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CutScene::create();
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
bool CutScene::init()
{
    std::ifstream ifs("Resources/properties/data.json");
    rapidjson::IStreamWrapper isw(ifs);

    doc.ParseStream(isw);
    assert(doc.IsObject());
    assert(doc.HasMember("progress"));
    assert(doc["progress"].IsInt());
    progress = doc["progress"].GetInt();

    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(CutScene::GoToGameScene), DISPLAY_TIME_SPLASH_SCENE);
    switch (progress)
    {
    case 0: {
        str = "Who are you?";
        progress = 1;
        doc["progress"].SetInt(progress);
        std::ofstream ofs("../Resources/properties/data.json");
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
        doc.Accept(writer);
    }
        break;
    case 1: {
        str = "Are you hear me?";
        //in razrabotke
    }
    default:
        str = "ERROR";
        break;
    }
    
    auto label = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 30);
    label->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(label);

    auto FadeIn = FadeIn::create(0.5f);
    label->runAction(FadeIn);

    auto fadeOut = FadeOut::create(0.5f);
    label->runAction(fadeOut);

    return true;
}

void CutScene::GoToGameScene(float dt)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
