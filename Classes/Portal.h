#include <cocos2d.h>
USING_NS_CC;

class Portal : public Sprite {
public:
	static Portal* Portal::create();
	Sprite* PortalSprite();
private:
	bool init();
	Sprite* portal;
};