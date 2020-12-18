#include <cocos2d.h>

USING_NS_CC;

class Portal : public  Node{
public:
	static Portal* create();
	void portalStart();
	Node* portalEnd();
private:
	bool init();
	Sprite* portal;
};