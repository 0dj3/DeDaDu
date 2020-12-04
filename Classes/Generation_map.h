#include <cocos2d.h>

USING_NS_CC;
#define SIZE_MAP 5;

class Generation_map: public Sprite {
public:
	static Generation_map* createScene(void);

    void generation();
    void border(TMXTiledMap* tiled);
    void generHall(TMXTiledMap* sizeMap, int direction);
    void generMapOne(TMXTiledMap* sizeMap, int direction);
    void generMainRoom(TMXTiledMap* tiled, int direction);
    void createDoor(TMXTiledMap* tiled, int direction);
    
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
