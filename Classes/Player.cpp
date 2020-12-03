#include "Player.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player()
{
    dmgsound = "res/sounds/hit/slime.mp3";
    tag = ContactListener::PLAYER;
    this->autorelease();
}

Unit* Player::create(cocos2d::Layer* layer, const Vec2& position)
{
    Player* newPlayer = new Player();
    if (newPlayer && newPlayer->sprite->initWithFile("res/hero/test_hero.png")) {
        newPlayer->sprite->getTexture()->setAliasTexParameters();
        newPlayer->sprite->setScale(3.0);
        newPlayer->setPosition(position);

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());

        newPlayer->setTag(newPlayer->tag);
        newPlayer->layer = layer;
        newPlayer->CreateWeapon();
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
    if (_weapon->isActive == false && InputListener::Instance()->mouseStates[static_cast<int>(EventMouse::MouseButton::BUTTON_LEFT)])
        _weapon->Attack();
}

void Player::CreateWeapon() {
    _weapon = new Weapon(layer, 20, 1);
    if (_weapon && _weapon->initWithFile("res/weapon/sword.png")) {
        _weapon->getTexture()->setAliasTexParameters();
        _weapon->setScale(3.0);
        _weapon->setTag(ContactListener::WEAPON);
        _weapon->setPosition(Vec2(this->sprite->getContentSize().width / 2, 0));
        _weapon->setAnchorPoint(this->sprite->getPosition());
        this->addChild(_weapon);
        return;
    }
    CC_SAFE_DELETE(_weapon);
    return;
}

void Player::rotate() {
    //if (_weapon->isActive == false)
        _weapon->setRotation(CC_RADIANS_TO_DEGREES(-(_weapon->getPosition() - InputListener::Instance()->mousePosition).getAngle()) - 135);
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
    b2Vec2 currentVel = body->GetLinearVelocity();
    //b2Vec2 thrust = desiredVel - currentVel;
    body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
    //log("%f %f", body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    //log("X = %f, Y = %f", this->getPosition().x, this->getPosition().y);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
}