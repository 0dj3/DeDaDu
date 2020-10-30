#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Unit.h"
#include <string>

class Player : public Unit
{
public:
    cocos2d::EventListenerKeyboard* listener = cocos2d::EventListenerKeyboard::create();

    Player();

    static Unit* create(cocos2d::Scene* scene);

private:
    cocos2d::MoveBy* moveBy = new cocos2d::MoveBy();
    cocos2d::Vec2* targetPosition = new cocos2d::Vec2(0, 0);

    void listenKeyboard();

    void update(float dt);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

};

#endif // __PLAYER_H__
