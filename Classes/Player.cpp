#include "Player.h"
#include "Definitions.h"
#include "Attack.h"
#include "HUD.h"
#include "Weapon.h"

USING_NS_CC;

Vec2 Player::position;
int Player::exp = 0;

Player::Player()
{
    dmgsound = "res/sounds/hit/punch.mp3";
    tag = ContactListener::PLAYER;
    gold = 20;
    stats = new UnitStats(1, 1, 1, 5);
    CheckMaxHP();
    hp = maxHP;
    autorelease();
}

Unit* Player::create(cocos2d::Layer* layer, const Vec2& position)
{
    Player* newPlayer = new Player();
    if (newPlayer && newPlayer->sprite->initWithFile("res/hero/test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->setPosition(position);
        newPlayer->setTag(newPlayer->tag);
        newPlayer->layer = layer;

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());

        newPlayer->hands = new Hands(newPlayer);
        newPlayer->addChild(newPlayer->hands);

        Item* weapon = Weapon::GetRandomWeapon();
        newPlayer->hands->PutInHands(weapon);

        newPlayer->scheduleUpdate();
        return newPlayer;
    }
    CC_SAFE_DELETE(newPlayer);
    return NULL;
}

void Player::update(float dt)
{
    position = getPosition();
    checkLVL();
    CheckMaxHP();
    move();
    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
    if (InputListener::Instance()->mouseStates[static_cast<int>(EventMouse::MouseButton::BUTTON_LEFT)])
    {
        Vec2 mousePos = InputListener::Instance()->mousePosition;
        mousePos.normalize();
        Vec2 pos = this->getPosition() + mousePos * this->sprite->getContentSize().height * this->getScale() * 3;
        hands->UseItem(pos, InputListener::Instance()->mousePosition);
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_R)]) {
        InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_R)] = false;
        Item* item;
        if (rand() % 2) {
            item = Weapon::GetRandomWeapon();
        }
        else {
            item = Potion::create("res/items/red_potion.png", "res/sounds/swoosh.mp3", rand() % 30 - 30);
        }
        Director::getInstance()->getRunningScene()->addChild(item);
        item->Sell(this->getPosition(), 5);
    }
    if (targetItem != NULL && InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)]) {
        InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)] = false;
        if (targetItem->IsForSale()) {
            if (gold >= targetItem->price) {
                gold -= targetItem->price;
                if (targetItem->type == Item::POTION) {
                    static_cast<Potion*>(targetItem)->Drink(this);
                    targetItem->setName(DEAD_TAG);
                    targetItem = NULL;
                }
                else {
                    hands->PutInHands(targetItem);
                    targetItem->setName(DEAD_TAG);
                    targetItem = NULL;
                }
            }
        }
        else {
            if (targetItem->type == Item::POTION) {
                static_cast<Potion*>(targetItem)->Drink(this);
                targetItem->setName(DEAD_TAG);
                targetItem = NULL;
            }
            else {
                hands->PutInHands(targetItem);
                targetItem->setName(DEAD_TAG);
                targetItem = NULL;
            }
        }
    }
}

void Player::move()
{
    float directionX = 0;
    float directionY = 0;
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_W)]) {
        directionY++;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_S)]) {
        directionY--;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_D)]) {
        directionX++;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_A)]) {
        directionX--;
    }
    b2Vec2 toTarget = b2Vec2(directionX, directionY);
    toTarget.Normalize();
    b2Vec2 desiredVel = stats->moveSpeed * toTarget;
    if (!isDashDelay && InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_SHIFT)]){
        double dashTime = 1;
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(dashTime);
        auto startDash = CallFunc::create([this, desiredVel]() {;
            int dashForce = 10;
            body->ApplyForceToCenter((LINEAR_ACCELERATION) *dashForce * this->stats->moveSpeed * desiredVel, true);
            isDashDelay = true;
        });
        auto endDash = CallFunc::create([this, desiredVel]() {;
            isDashDelay = false;
        });
        auto seq = cocos2d::Sequence::create(startDash, delay, endDash, nullptr);
        SetInvulnerable(dashTime / 2);
        this->runAction(seq);
    }
    else {
        body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
    }
}

void Player::setGold(int x)
{
    gold += x;
}

void Player::checkLVL() {
    if (exp >= EXP_UNTIL_LVL_UP) {
        CCLOG("LVL");
        lvl++;
        exp = exp - EXP_UNTIL_LVL_UP;
        switch (rand() % 4)
        {
        case 0:
            stats->UpHP();
            break;
        case 1:
            stats->UpDamage();
            break;
        case 2:
            stats->UpAttackSpeed();
            break;
        case 3:
            stats->UpMoveSpeed();
            break;
        default:
            break;
        }
    }
}

void Player::giveEXP(int value) {
    exp += value;
}