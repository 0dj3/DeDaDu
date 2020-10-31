#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    speed = 3;
}


Unit* Player::create(cocos2d::Scene* scene)
{
    Player* newPlayer = new Player();
    if (newPlayer->sprite->initWithFile("hero.png")) {
        auto body = PhysicsBody::createCircle(newPlayer->sprite->getContentSize().width / 2);
        body->setContactTestBitmask(true);
        newPlayer->setPhysicsBody(body);
        newPlayer->scene = scene;
        newPlayer->autorelease();
        newPlayer->listenKeyboard();
        newPlayer->scheduleUpdate();
        return newPlayer;
    }
    CC_SAFE_DELETE(newPlayer);
    return NULL;
}

void Player::update(float dt)
{
    move();
}

void Player::move()
{
    float directionX = 0;
    float directionY = 0;
    if (keyStates[0]) {
        directionY += speed;
    }
    if (keyStates[1]) {
        directionY -= speed;
    }
    if (keyStates[2]) {
        directionX += speed;
    }
    if (keyStates[3]) {
        directionX -= speed;
    }
    if (directionX != 0 && directionY != 0) {
        directionX *= 0.7f;
        directionY *= 0.7f;
    }
    this->runAction(MoveBy::create(0.3f, Vec2(directionX, directionY)));
}

void Player::listenKeyboard() 
{
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W:
            keyStates[0] = true;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            keyStates[1] = true;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            keyStates[2] = true;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            keyStates[3] = true;
            break;
        }
    };
    eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_W:
            keyStates[0] = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            keyStates[1] = false;
            break;
        case EventKeyboard::KeyCode::KEY_D:
            keyStates[2] = false;
            break;
        case EventKeyboard::KeyCode::KEY_A:
            keyStates[3] = false;
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

