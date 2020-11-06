#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    this->autorelease();
}


Unit* Player::create(cocos2d::Layer* layer)
{
    Player* newPlayer = new Player();
    if (newPlayer->sprite->initWithFile("test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer->sprite->getContentSize());
        newPlayer->addComponent(newPlayer->body);

        newPlayer->layer = layer;
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
        directionY += stats->speed;
    }
    if (keyStates[1]) {
        directionY -= stats->speed;
    }
    if (keyStates[2]) {
        directionX += stats->speed;
    }
    if (keyStates[3]) {
        directionX -= stats->speed;
    }
    if (directionX != 0 && directionY != 0) {
        directionX *= 0.7f;
        directionY *= 0.7f;
    }
    /*if (directionX == 0 && directionY == 0) {
        this->body->setVelocity(Vec2(this->body->getVelocity().x / 2, this->body->getVelocity().y / 2));
    }*/
    //this->body->setVelocity(Vec2(directionX * 20, directionY * 20));
    this->runAction(MoveBy::create(0.3f, Vec2(directionX, directionY)));
    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
    setPos(directionX, directionY);
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
