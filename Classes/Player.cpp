#include "Player.h"
#include "Definitions.h"
#include "Attack.h"
#include "HUD.h"

USING_NS_CC;

Player::Player()
{
    dmgsound = "res/sounds/hit/punch.mp3";
    tag = ContactListener::PLAYER;
    this->gold = 20;
    this->maxHp = 100;
    this->hp = 100;
    this->autorelease();
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

        newPlayer->hands = new Hands();
        newPlayer->addChild(newPlayer->hands);
        std::map<std::string, int> stats{
            {"damage", 20},
            {"delay", 5}
        };
        Item* weapon = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/sword.png", stats);
        newPlayer->hands->PutInHands(weapon);

        newPlayer->scheduleUpdate();
        return newPlayer;
    }
    CC_SAFE_DELETE(newPlayer);
    return NULL;
}

void Player::update(float dt)
{
    move();
    rotate();
    if (InputListener::Instance()->mouseStates[static_cast<int>(EventMouse::MouseButton::BUTTON_LEFT)] && !isDelay)
    {
        //InputListener::Instance()->mouseStates[static_cast<int>(EventMouse::MouseButton::BUTTON_LEFT)] = false;
        Vec2 mousePos = InputListener::Instance()->mousePosition;
        mousePos.normalize();
        Vec2 pos = this->getPosition() + mousePos * this->sprite->getContentSize().height * this->getScale() * 2;
        Attack::StartMeleeAttack(pos, InputListener::Instance()->mousePosition, ContactListener::PLAYER, hands->GetItem());

        // cooldown
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create((double)hands->GetItem()->stats.find("delay")->second / 10);
        auto startCD = CallFunc::create([this]() {
            isDelay = true;
        });
        auto endCD = CallFunc::create([this]() {
            isDelay = false;
        });
        auto seq = cocos2d::Sequence::create(startCD, delay, endCD, nullptr);
        this->runAction(seq);
    }
    /*if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_R)]) {
        InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_R)] = false;
        Item* item;
        if (rand() % 2) {
            std::map<std::string, int> stats{
            {"healing", -20 + rand() % 40}
            };
            item = Item::create(Item::POTION, "Potion", "Super potion", "res/items/potion.png", stats);
            item->setColor(Color3B(rand() % 255, rand() % 255, rand() % 255));
        }
        else {
            std::map<std::string, int> stats{
            {"damage", 1 + rand() % 40},
            {"delay", 1 + rand() % 10}
            };
            item = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/sword.png", stats);
        }
        layer->addChild(item);
        item->Sell(this->getPosition(), 5);
    }*/
    if (targetItem != NULL && InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)]) {
        InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)] = false;
        if (targetItem->IsForSale()) {
            if (gold >= targetItem->price) {
                gold -= targetItem->price;
                if (targetItem->type == Item::POTION) {
                    Damage(targetItem->stats.begin()->second);
                    targetItem->setName(DEAD_TAG);
                    targetItem = NULL;
                }
                else {
                    hands->PutInHands(Item::create(targetItem));
                    targetItem->setName(DEAD_TAG);
                    targetItem = NULL;
                }
            }
        }
        else {
            if (targetItem->type == Item::POTION) {
                Damage(targetItem->stats.begin()->second);
                targetItem->setName(DEAD_TAG);
                targetItem = NULL;
            }
            else {
                hands->PutInHands(Item::create(targetItem));
                targetItem->setName(DEAD_TAG);
                targetItem = NULL;
            }
        }
    }
}

void Player::rotate() {

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
    b2Vec2 desiredVel = stats->speed * toTarget;
    body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
}

void Player::setGold(int x)
{
    gold += x;
}