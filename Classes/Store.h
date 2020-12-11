#pragma once
#include <cocos2d.h>
#include "2d/CCFastTMXLayer.h"
USING_NS_CC;

class Store : public Layer {
public:
	static Store* createScene(TMXTiledMap* map, int countMap);
private:
	bool init(TMXTiledMap* map, int countMap);
	TMXTiledMap* store;
	TMXTiledMap* MapOne;
};
