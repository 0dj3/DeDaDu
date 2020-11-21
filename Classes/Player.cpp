#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    this->autorelease();
}


Unit* Player::create(cocos2d::Layer* layer, const Vec2& position)
{
    Player* newPlayer = new Player();
    if (newPlayer && newPlayer->sprite->initWithFile("test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->setPosition(position);

        newPlayer->CreateWeapon();

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());

        newPlayer->layer = layer;
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
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_W)]) {
        //directionY += stats->speed;
        directionY += 1;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_S)]) {
        directionY -= 1;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_D)]) {
        directionX += 1;
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_A)]) {
        directionX -= 1;
    }
    b2Vec2 toTarget = b2Vec2(directionX, directionY);
    toTarget.Normalize();
    b2Vec2 desiredVel = stats->speed * PPM * toTarget;
    b2Vec2 currentVel = body->GetLinearVelocity();
    b2Vec2 thrust = desiredVel - currentVel;
    body->ApplyForceToCenter(sprite->getContentSize().width * LINEAR_ACCELERATION * thrust, true);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
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
