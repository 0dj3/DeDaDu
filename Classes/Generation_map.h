#include <cocos2d.h>
#include "PhysicHelper.h"
#include <vector>
#include <Slime.h>
#include <Goblin.h>
#include <Store.h>
USING_NS_CC;
#define SIZE_MAP 5;

class Generation_map: public Layer {
public:
	static Generation_map* createScene(bool checkLoc);
    
    void generation(bool checkLoc);
    void border(TMXTiledMap* tiled);
    void borderForRoom(TMXTiledMap* tiled);
    void generHall(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMapOne(TMXTiledMap* sizeMap, int direction, bool checkLoc);
    void generMainRoom(TMXTiledMap* tiled, int direction, bool checkLoc);
    void createDoor(TMXTiledMap* tiled, int direction, bool checkLoc, bool checkDelRoom);
    
    Vec2 getPosTileMapOneEnd();
    Size getSizeTileMapOneEnd();
    std::vector<TMXTiledMap*> getAllMapOne();

    void location2(TMXTiledMap* tiled, bool checkLoc);
    std::vector<Unit*> checkRoom(Unit* player, std::vector<Unit*> enemies, bool checkLoc);
    std::vector<Unit*> createEnemy(std::vector<Unit*> enemies, TMXTiledMap* tiled, Unit* player);

    void createStore();

    void generBarrel();

    Node* miniMap(Player* player, Vec2);
    Sprite* miniHall(Sprite* miniRoom, int direction);
private:
    bool init(bool checkLoc);
    int** generationArrayMap(int sizeMap);

    Store* store;

    TMXTiledMap* tileMap;
    TMXTiledMap* tileHallML;
    TMXTiledMap* tileHallMR;
    TMXTiledMap* tileHallMU;
    TMXTiledMap* tileHall;
    TMXTiledMap* tileMapOne;
    TMXTiledMap* tileMainRoom;
    TMXTiledMap* wallLoc2;
    
    DrawNode* drawOne;
    DrawNode* drawOne2;
    std::vector<Sprite*> allDrawRoom;
    DrawNode* drawPlayer;

    std::vector<TMXTiledMap*> allMainRoom;
    std::vector<TMXTiledMap*> allMapOne;

    std::vector<b2Body*> allPhysicBody;
    std::vector<b2Body*> allPhysicBarrel;
    std::vector<b2Body*> PhBoDoorRoom;
    std::vector<TMXTiledMap*> childDoorRoom;

    Node* edgeNode;
    size_t quantityEnemy;
    int** arrayMap;
    int checkI = 1, sizeMap = SIZE_MAP;
    int checkj;
    bool checkDoorRoom = false;
    PhysicsWorld* sceneWorld;

    bool checkPl = false;
    Vec2 FirstPosPl = Vec2(0, 0);
    Node* layer;
    Sprite* miniRoom;
    std::vector<b2Body*> allPhStore;
};
