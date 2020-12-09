#include "Player.h"
#include "Definitions.h"
#include <cstdlib>

USING_NS_CC;

Player::Player()
{
    dmgsound = "res/sounds/hit/punch.mp3";
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
        std::map<std::string, int> stats{
            {"damage", 20},
            {"speed", 8}
        };
        Item* weapon = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/sword.png", stats);
        newPlayer->CreateWeapon(weapon);
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
    {
        Vec2 mousePos = InputListener::Instance()->mousePosition;
        mousePos.normalize();
        Vec2 pos = this->getPosition() + mousePos * this->sprite->getContentSize().height * this->getScale() * 2;
        _weapon->Attack(pos);
    }
    if (InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_R)]) {
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
            {"speed", 1 + rand() % 8}
            };
            item = Item::create(Item::WEAPON, "Sword", "Super sword", "res/weapon/sword.png", stats);
        }
        layer->addChild(item);
        item->DropItem(this->getPosition());
    }
    if (targetItem != NULL && InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)]) {
        InputListener::Instance()->keyStates[static_cast<int>(EventKeyboard::KeyCode::KEY_E)] = false;
        if (targetItem->type == Item::POTION) {
            Damage(targetItem->stats.begin()->second);
            targetItem->setName(DEAD_TAG);
            targetItem = NULL;
        }
        else {
            _weapon->ChangeWeapon(Item::create(targetItem));
            targetItem->setName(DEAD_TAG);
            targetItem = NULL;
        }
    }
    
    /*for (b2ContactEdge* ce = body->GetContactList(); ce; ce = ce->next)
    {
        b2Contact* contact = ce->contact;
        b2Body* a = contact->GetFixtureA()->GetBody();
        b2Body* b = contact->GetFixtureB()->GetBody();
        if (b->GetUserData() != NULL && a->GetUserData() != NULL)
        {
            Node* node = static_cast<Node*>(a->GetUserData())->getTag() != ContactListener::PLAYER ? static_cast<Node*>(a->GetUserData()) : static_cast<Node*>(b->GetUserData());
            if (node->getTag() == ContactListener::ITEM) {

            }
        }
    }*/
}

void Player::CreateWeapon(Item* weapon) {
    _weapon = new Weapon(layer, weapon);
    if (_weapon) {
        _weapon->setPosition(Vec2(this->sprite->getContentSize().width / 2, 0));
        _weapon->setAnchorPoint(this->sprite->getPosition());
        this->addChild(_weapon);
        return;
    }
    CC_SAFE_DELETE(_weapon);
    return;
}

void Player::rotate() {
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
    //b2Vec2 currentVel = body->GetLinearVelocity();
    //b2Vec2 thrust = desiredVel - currentVel;
    body->ApplyForceToCenter((LINEAR_ACCELERATION)*desiredVel, true);
    //log("%f %f", body->GetLinearVelocity().x, body->GetLinearVelocity().y);
    //log("X = %f, Y = %f", this->getPosition().x, this->getPosition().y);

    auto cam = Camera::getDefaultCamera();
    cam->setPosition(this->getPosition());
}