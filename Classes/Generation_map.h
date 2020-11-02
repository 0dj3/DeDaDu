#ifndef __MAP_H__
#define __MAP_H__
#include "cocos2d.h"

class Generation_map: public cocos2d::Layer {
public:
	virtual bool init();
	void create_hall();
	void create_main_room();
	void create_shop();
	void create_room();
private:
	cocos2d::TMXTiledMap* tileHall;
	cocos2d::TMXTiledMap* tileMap;
};

#endif // __UNIT_H__