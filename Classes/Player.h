#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "InputListener.h"

class Player : public Unit
{
public:
    Player();
    static Unit* create(cocos2d::Layer* scene, const cocos2d::Vec2& position);

private:
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    bool onContactPreSolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve); 
    void onContactPostSolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
    void onContactSeperate(cocos2d::PhysicsContact& contact);
    cocos2d::Sprite* weaponSprite;

    void listenMouse();
    cocos2d::Vec2 mousePosition;

    void CreateWeapon();

    void update(float dt);

    void move();
    void rotate();

};

#endif // __PLAYER_H__
