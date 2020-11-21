#include "InputListener.h"
#include "Definitions.h"

InputListener* InputListener::instance;

bool InputListener::Init(cocos2d::Layer* layer) {
	auto director = cocos2d::Director::getInstance();

	kbListener = cocos2d::EventListenerKeyboard::create();

	director->getOpenGLView()->setIMEKeyboardState(true);
	kbListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyStates[static_cast<int>(keyCode)] = true;
	};
	kbListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyStates[static_cast<int>(keyCode)] = false;
	};

	layer->getEventDispatcher()->addEventListenerWithFixedPriority(kbListener, 2);


	mouseListener = cocos2d::EventListenerMouse::create();

	mouseListener->onMouseDown = [this](cocos2d::Event* ccevnt)
	{
		cocos2d::EventMouse* e = dynamic_cast<cocos2d::EventMouse*>(ccevnt);
		mouseStates[static_cast<int>(e->getMouseButton())] = true;
	};
	mouseListener->onMouseUp = [this](cocos2d::Event* ccevnt)
	{
		cocos2d::EventMouse* e = dynamic_cast<cocos2d::EventMouse*>(ccevnt);
		mouseStates[static_cast<int>(e->getMouseButton())] = false;
	}; 
	mouseListener->onMouseMove = [this](cocos2d::Event* ccevnt)
	{
		cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
		cocos2d::EventMouse* eventMouse = (cocos2d::EventMouse*)ccevnt;
		mousePosition = cocos2d::Vec2(eventMouse->getCursorX() - visibleSize.width / 2 + origin.x, eventMouse->getCursorY() - visibleSize.height / 2 + origin.y);
	};

	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, layer);

	return true;
}