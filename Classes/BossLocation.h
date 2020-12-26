#include "cocos2d.h"
#include "Generation_map.h"
#include <string>
#include "2d/CCFastTMXLayer.h"
#include <SlimeKing.h>
#include <GoblinWarlord.h>

using namespace std;
USING_NS_CC;

class BossLocation: public Generation_map  {
public:
	static BossLocation* createScene(string bossName, vector<Unit*> enemies, Player* player);

	TMXTiledMap* mapMain;
	TMXTiledMap* getPosRoom();

	TMXTiledMap* locIn;
	string name;
	vector<Unit*> getEnemies();
	TMXTiledMap* getlocIn();
	int countBoss;
	bool checkDoor = false;
	bool bossDeath = false;
private:
	bool init();
	void update(float dt);
	float time;

	TMXTiledMap* hallUp;
	TMXTiledMap* hallRight;
	TMXTiledMap* mapOne;
	TMXTiledMap* wall;

	Unit* playerGL;
	SlimeKing* slimeking;
	GoblinWarlord* goblinWarlord;
	Enemy* boss;
	vector<Unit*> enemies;
	bool checkBoss = false;
	Enemy* addSlime(Point pos);
	Enemy* addGoblin(Point pos);
};