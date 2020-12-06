#include <cocos2d.h>
#include "PhysicHelper.h"
#include <vector>

USING_NS_CC;
#define SIZE_MAP 5;

class Generation_map: public Sprite {
public:
	static Generation_map* createScene(void);

    void generation(bool checkLoc);
    void border(TMXTiledMap* tiled);
    void borderForRoom(TMXTiledMap* tiled);
    void generHall(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMapOne(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMainRoom(TMXTiledMap* tiled, int direction, bool checkLoc);
    void createDoor(TMXTiledMap* tiled, int direction, bool checkLoc, bool checkDelRoom);

    Vec2 getPosTileMapOne();

    void location2(TMXTiledMap* tiled, bool checkLoc);
    std::vector<Unit*> checkRoom(Unit* player, std::vector<Unit*> enemies, bool checkLoc);

private:
    bool init();
    int** generationArrayMap(int sizeMap);

    TMXTiledMap* tileMap;
    TMXTiledMap* tileHallML;
    TMXTiledMap* tileHallMR;
    TMXTiledMap* tileHallMU;
    TMXTiledMap* tileHall;
    TMXTiledMap* tileMapOne;
    TMXTiledMap* tileMainRoom;
    TMXTiledMap* wallLoc2;
    
    std::vector<TMXTiledMap*> allMainRoom;
    std::vector<TMXTiledMap*> allMapOne;

    std::vector<b2Body*> allPhysicBody;
    std::vector<b2Body*> PhBoDoorRoom;

    Node* edgeNode;
    size_t quantityEnemy;
    int** arrayMap;
    int checkI = 1, sizeMap = SIZE_MAP;
    int checkj;
    bool checkDoorRoom = false;
    PhysicsWorld* sceneWorld;
};
