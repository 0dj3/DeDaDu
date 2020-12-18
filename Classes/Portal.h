#include <cocos2d.h>

USING_NS_CC;

class Portal : public  Node{
public:
	static Portal* create();
	Sprite* PortalSprite();
private:
	bool init();
	Sprite* portal;
};