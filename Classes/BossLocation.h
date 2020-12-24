#include "cocos2d.h"
#include "Generation_map.h"
#include <string>
#include "2d/CCFastTMXLayer.h"

using namespace std;
USING_NS_CC;

class BossLocation: public Generation_map  {
public:
	static BossLocation* createScene(string bossName, vector<Unit*> enemies);

	TMXTiledMap* mapMain;
	TMXTiledMap* getPosRoom();

	TMXTiledMap* locIn;
	vector<Unit*> getEnemies();
	TMXTiledMap* getlocIn();
private:
	bool init();
	string name;
	TMXTiledMap* hallUp;
	TMXTiledMap* hallRight;
	TMXTiledMap* mapOne;
	void update(float dt);
	Enemy* addBoss(Point pos);
	vector<Unit*> enemies;
	float time;
};