#include <cocos2d.h>

USING_NS_CC;
#define SIZE_MAP 5;

class Generation_map: public Sprite {
public:
	static Generation_map* createScene(void);

    void generation(bool checkLoc);
    void border(TMXTiledMap* tiled);
    void generHall(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMapOne(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMainRoom(TMXTiledMap* tiled, int direction, bool checkLoc);
    void createDoor(TMXTiledMap* tiled, int direction, bool checkLoc);
    void location2(TMXTiledMap* tiled, bool checkLoc);
    Vec2 getPosTileMapOne();
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


    Node* edgeNode;
    int** arrayMap;
    int checkI = 1, sizeMap = SIZE_MAP;
    int checkj;
    PhysicsWorld* sceneWorld;
};
