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

        newPlayer->body = PhysicHelper::createDynamicPhysicBody(newPlayer, newPlayer->sprite->getContentSize());

        newPlayer->layer = layer;
        newPlayer->CreateWeapon();
        PhysicHelper::world->SetContactListener(newPlayer);
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
    weaponSprite->setRotation(CC_RADIANS_TO_DEGREES(-(weaponSprite->getPosition() - InputListener::Instance()->mousePosition).getAngle()) - 135);
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
    b2Vec2 desiredVel = stats->speed * PPM * toTarget;
    b2Vec2 currentVel = body->GetLinearVelocity();
    b2Vec2 thrust = desiredVel - currentVel;
    body->ApplyForceToCenter(sprite->getContentSize().width * LINEAR_ACCELERATION * thrust, true);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
}

void Player::BeginContact(b2Contact* contact)
{
    auto a = contact->GetFixtureA()->GetBody()->GetUserData();
    auto b = contact->GetFixtureB()->GetBody()->GetUserData();
    //PhysicsBody* playerBody = (bodyA->getTag() == 4) ? bodyA : bodyB;
    if (static_cast<Node*>(b)->getTag() == 2) {
        static_cast<Unit*> (b)->Damage(20);
    }
}

void Player::EndContact(b2Contact* contact)
{

}

void Player::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{

}

void Player::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{

}