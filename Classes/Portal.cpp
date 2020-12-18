#include "Portal.h"

void Portal:: portalStart() {
    char str1[200] = { 0 };
    auto spritecache1 = SpriteFrameCache::getInstance();
    spritecache1->addSpriteFramesWithFile("portal/start/portalStart.plist");
    auto spritesheet1 = SpriteBatchNode::create("portal/start/portalStart.png");
    this->addChild(spritesheet1);

    Vector<SpriteFrame*> idleAnimFrames1(5);
    for (int i = 1; i <= 5; i++) {
        sprintf(str1, "portal_%i.png", i);
        idleAnimFrames1.pushBack(spritecache1->getSpriteFrameByName(str1));
    }
    auto idleAnimation1 = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    auto demo1 = Sprite::createWithSpriteFrameName("dead_1.png");
    demo1->setPosition(Point(this->getPosition().x, this->getPosition().y));
    demo1->setScale(3.0);
    Action* action1 = Repeat::create(Animate::create(idleAnimation1), 1);
    demo1->runAction(action1);
    spritesheet1->addChild(demo1);
}