#include "Player.h"
#include "Definitions.h"
#include "Attack.h"
#include "HUD.h"
#include "Weapon.h"
#include "DeathScreen.h"

USING_NS_CC;

Vec2 Player::position;
int Player::exp = 0;

Player::Player()
{
    dmgsound = "res/sounds/hit/punch.mp3";
    tag = ContactListener::PLAYER;
    gold = 20;
    stats = new UnitStats(1, 1, 1, 2);
    CheckMaxHP();
    hp = maxHP;
    autorelease();
}

Unit* Player::create(const Vec2& position)
{
    Player* newPlayer = new Player();
    if (newPlayer && newPlayer->sprite->initWithFile("res/hero/test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->setPosition(position);
        newPlayer->setTag(newPlayer->tag);

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());

        newPlayer->hands = new Hands(newPlayer);
        newPlayer->addChild(newPlayer->hands);

        Weapon* weapon = Weapon::GetRandomWeapon();
        newPlayer->hands->PutInHands(weapon);

        newPlayer->scheduleUpdate();
        return newPlayer;
    }
    CC_SAFE_DELETE(newPlayer);
    return NULL;
}

void Player::update(float dt)
{
    time += dt;
    position = getPosition();
    checkLVL();
    CheckMaxHP();
    move();
    cameraUpdate();
    if (targetItem != NULL)
        checkInteract();
    if (InputListener::Instance()->mouseStates[static_cast<int>(EventMouse::MouseButton::BUTTON_LEFT)])
    {
        Vec2 mousePos = InputListener::Instance()->mousePosition;
        mousePos.normalize();
        Vec2 pos = this->getPosition() + mousePos * this->sprite->getContentSize().height * this->getScale() * 3;
        hands->UseItem(this->getPosition(), InputListener::Instance()->mousePosition.getAngle());
    }
    if (time > 0.1f) {
        int pastPosX = pastPos.x;
        int pastPosY = pastPos.y;
        int posX = this->getPosition().x;
        int posY = this->getPosition().y;
        if (pastPosX != posX || pastPosY != posY) {
            char goblinStr[200] = { 0 };
            sprintf(goblinStr, "res/hero/run_%i.png", asRun);
            sprite->setTexture(goblinStr);
            sprite->getTexture()->setAliasTexParameters();
            sprite->setScale(3.0);
            if (asRun == 6)
                asRun = 1;
            else asRun++;
        }
        else {
            char goblinStr[200] = { 0 };
            sprintf(goblinStr, "res/hero/idle_%i.png", asIdle);
            sprite->setTexture(goblinStr);
            sprite->getTexture()->setAliasTexParameters();
            sprite->setScale(3.0);
            if (asIdle == 6)
                asIdle = 1;
            else asIdle++;
        }
        pastPos = this->getPosition();
        time = 0;
    }
}

void Player::cameraUpdate() {
    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
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
        sprite->setFlippedX(false);
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_A)]) {
        directionX--;
        sprite->setFlippedX(true);
    }
    b2Vec2 toTarget = b2Vec2(directionX, directionY);
    toTarget.Normalize();
    b2Vec2 desiredVel = stats->moveSpeed * toTarget;
    if (!isDashDelay && InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_SHIFT)]) {
        double dashTime = 1;
        cocos2d::DelayTime* delay = cocos2d::DelayTime::create(dashTime);
        auto startDash = CallFunc::create([this, desiredVel]() {;
        int dashForce = 10;
        body->ApplyForceToCenter((LINEAR_ACCELERATION)*dashForce * this->stats->moveSpeed * desiredVel, true);
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

void Player::DeathRattle() {
    this->setName("");
    AudioEngine::stopAll();
    Node::stopAllActions();
    InputListener::Instance()->ReleaseAllKeys();
    AudioEngine::preload("res/sounds/ds.mp3");
    auto scene = DeathScreen::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void Player::checkInteract()
{
    if (getPosition().distance(targetItem->getPosition()) > PPM * 3)
        targetItem = NULL;
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)]) {
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
                    hands->PutInHands(static_cast<Weapon*>(targetItem));
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
                hands->PutInHands(static_cast<Weapon*>(targetItem));
                targetItem->setName(DEAD_TAG);
                targetItem = NULL;
            }
        }
    }
}

void Player::idleGoblin(char* path)
{
    char goblinStr[200] = { 0 };
    auto goblinSpriteCache = SpriteFrameCache::getInstance();
    goblinSpriteCache->addSpriteFramesWithFile(path);

    Vector<SpriteFrame*> idleAnimFrames1(6);
    for (int i = 1; i <= 6; i++) {
        sprintf(goblinStr, "run_%i.png", i);
        SpriteFrame* spriteF = goblinSpriteCache->getSpriteFrameByName(goblinStr);
        spriteF->getTexture()->setAliasTexParameters();
        idleAnimFrames1.pushBack(spriteF);
    }
    auto goblinIdle = Animation::createWithSpriteFrames(idleAnimFrames1, 0.1f);
    /*auto demoGoblin = Sprite::createWithSpriteFrameName("run_1.png");
    demoGoblin->setPosition(Point(this->getPosition().x, this->getPosition().y));
    demoGoblin->setScale(3.0);*/
    //Action* action1 = RepeatForever::create(Animate::create(goblinIdle));
    Animate* animate = Animate::create(goblinIdle);
    Player::sprite->runAction(RepeatForever::create(animate));

    //sprite->runAction(action1);
}