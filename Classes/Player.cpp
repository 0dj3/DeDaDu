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
    if (newPlayer && newPlayer->sprite->initWithFile("test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->CreateWeapon();

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer->sprite->getContentSize() * 2);
        newPlayer->addComponent(newPlayer->body);
        newPlayer->layer = layer;
        newPlayer->listenKeyboard();
        newPlayer->listenMouse();
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
}

void Player::CreateWeapon() {
    weaponSprite = new Sprite();
    if (weaponSprite && weaponSprite->initWithFile("v1.1 dungeon crawler 16x16 pixel pack/heroes/knight/weapon_sword_1.png")) {
        weaponSprite->getTexture()->setAliasTexParameters();
        PhysicsBody* body = PhysicHelper::createDynamicPhysicBody(weaponSprite->getContentSize());
        body->getShape(body->getTag())->setRestitution(0);
        weaponSprite->addComponent(body);
        weaponSprite->setScale(3.0);
        weaponSprite->setPosition(Vec2(this->sprite->getContentSize().width / 2, 0));
        weaponSprite->setAnchorPoint(this->sprite->getPosition());
        this->addChild(weaponSprite);

        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
        return;
    }
    CC_SAFE_DELETE(weaponSprite);
    return;
}

void Player::rotate() {
    weaponSprite->setRotation(CC_RADIANS_TO_DEGREES(-(weaponSprite->getPosition() - mousePosition).getAngle()) - 135);
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
    log(directionX);
    log(directionY);
}

void Player::listenKeyboard() 
{
    auto eventListener = cocos2d::EventListenerKeyboard::create();
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

void Player::listenMouse()
{
    auto mouseListener = cocos2d::EventListenerMouse::create();

    mouseListener->onMouseMove = [this](cocos2d::Event* ccevnt)
    {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        EventMouse* eventMouse = (EventMouse*)ccevnt;
        mousePosition = Vec2(eventMouse->getCursorX() - visibleSize.width / 2 + origin.x, eventMouse->getCursorY() - visibleSize.height / 2 + origin.y);
        log("float is %f", mousePosition.x);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool Player::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode(); 
    if (nodeB->getTag() == 2) 
    {
        static_cast<Unit*> (nodeB)->Damage(50);
    }
    else if(nodeB->getTag() == 3)
    {
        static_cast<Unit*> (nodeB)->Damage(50);
    }

    return false;
}
