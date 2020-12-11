#pragma once
#include <cocos2d.h>
#include <Generation_map.h>
#include "2d/CCFastTMXLayer.h"
USING_NS_CC;

class Store : public Layer {
public:
	static Store* createScene();
private:
	bool init();
	TMXTiledMap* store;
	std::vector<TMXTiledMap*> allMapOne;
};
