#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    speed = 1;
}


Unit* Player::create(cocos2d::Scene* scene)
{
    Player* newPlayer = new Player();
    if (newPlayer->sprite->initWithFile("CloseNormal.png")) {
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
    moveBy = cocos2d::MoveBy::create(0.01f, *targetPosition);
    this->runAction(Spawn::create(moveBy, nullptr));
}

void Player::listenKeyboard() 
{
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        targetPosition->y = speed;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        targetPosition->y = -speed;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        targetPosition->x = speed;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        targetPosition->x = -speed;
    }
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W)
    {
        targetPosition->y = 0;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
    {
        targetPosition->y = 0;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
    {
        targetPosition->x = 0;
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
    {
        targetPosition->x = 0;
    }
}
