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

	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, layer);

	return true;
}