#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    this->autorelease();
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Player::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(Player::onContactPreSolve, this);
    contactListener->onContactPostSolve = CC_CALLBACK_2(Player::onContactPostSolve, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(Player::onContactSeperate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


Unit* Player::create(cocos2d::Layer* layer, const Vec2& position)
{
    Player* newPlayer = new Player();
    if (newPlayer && newPlayer->sprite->initWithFile("test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->setPosition(position);
        newPlayer->CreateWeapon();

        //newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer->sprite->getContentSize() * 2);
        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());
        //newPlayer->body->getShape(newPlayer->body->getTag())->setRestitution(0);
        //newPlayer->body->setTag(4);
        //newPlayer->addComponent(newPlayer->body);

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

        //PhysicsBody* body = PhysicHelper::createDynamicPhysicBody(weaponSprite->getContentSize());
        //body->getShape(body->getTag())->setRestitution(0);
        //body->setDynamic(false);
        //weaponSprite->addComponent(body);

        weaponSprite->setScale(3.0);
        weaponSprite->setPosition(Vec2(this->sprite->getContentSize().width / 2, 0));
        weaponSprite->setAnchorPoint(this->sprite->getPosition());
        weaponSprite->setTag(5);
        this->addChild(weaponSprite);
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
        //directionY += stats->speed;
        directionY += 1;
    }
    if (keyStates[1]) {
        directionY -= 1;
    }
    if (keyStates[2]) {
        directionX += 1;
    }
    if (keyStates[3]) {
        directionX -= 1;
    }
    /*if (directionX != 0 && directionY != 0) {
        directionX *= 0.7f;
        directionY *= 0.7f;
    }*/
    /*if (directionX == 0 && directionY == 0) {
        this->body->setVelocity(Vec2(this->body->getVelocity().x / 2, this->body->getVelocity().y / 2));
    }*/
    //body->ApplyForceToCenter(b2Vec2(directionX * 20, directionY * 20), true);
    //this->runAction(MoveBy::create(0.3f, Vec2(directionX, directionY)));

    b2Vec2 toTarget = b2Vec2(directionX, directionY);
    toTarget.Normalize();
    b2Vec2 desiredVel = stats->speed * PPM * toTarget;
    b2Vec2 currentVel = body->GetLinearVelocity();
    b2Vec2 thrust = desiredVel - currentVel;
    body->ApplyForceToCenter(sprite->getContentSize().width * LINEAR_ACCELERATION * thrust, true);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
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
        //log("float is %f", mousePosition.x);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

bool Player::onContactBegin(PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();
    PhysicsBody* playerBody = (bodyA->getTag() == 4) ? bodyA : bodyB;
    if (bodyB->getTag() == 2) {
        static_cast<Unit*> (bodyB->getNode())->Damage(50);
    }
    if (bodyB->getTag() == 5 || bodyB->getTag() == 5) {
        return false;
    }

    return true;
}

bool Player::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve)
{
    contact.getShapeA()->getBody()->setVelocity({ 0,0 });
    contact.getShapeA()->getBody()->setVelocity({ 0,0 });
    solve.setRestitution(0);
    return true;
}

void Player::onContactPostSolve(PhysicsContact& contact, const PhysicsContactPostSolve& solve)
{

}

void Player::onContactSeperate(PhysicsContact& contact)
{

}
