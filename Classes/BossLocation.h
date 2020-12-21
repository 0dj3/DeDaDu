#include "cocos2d.h"
#include "Generation_map.h"
#include <string>
#include "2d/CCFastTMXLayer.h"

using namespace std;
USING_NS_CC;

class BossLocation: public Generation_map  {
public:
	static BossLocation* createScene(string bossName);
private:
	bool init();
	string name;

	TMXTiledMap* locIn;
};