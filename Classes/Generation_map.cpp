#include "Generation_map.h"
#include "2d/CCFastTMXLayer.h"
#include <ctime>
#include "Fly.h"
USING_NS_CC;


Generation_map* Generation_map::createScene(){
    Generation_map* gener = new Generation_map();
    gener->init();
    return gener;
}

bool Generation_map::init() {
    generation();
    return true;
}

void Generation_map::generation() {
    arrayMap = generationArrayMap(sizeMap);
    checkj = sizeMap / 2;

    tileMap = TMXTiledMap::create("maps/main_room.tmx");



    auto layerCheck = tileMap->getLayer("walls");
    auto loc2Wall = tileMap->getLayer("location2")->getTileGIDAt(Vec2(0, 0));

    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                layerCheck->setTileGID(loc2Wall, Vec2(i, j));
            }
        }
    }





    tileMap->setScale(3.0);
    tileMap->setAnchorPoint(Point(0, 0));
    this->addChild(tileMap);
    border(tileMap);


    /*createDoor(tileMap, 1);
    createDoor(tileMap, 2);
    createDoor(tileMap, 3);
    createDoor(tileMap, 4);*/

    //direction = 1;//["down"] 
    //direction = 2;//["up"]
    //direction = 3;//["right"]
    //direction = 4;//["left"] 

    generHall(tileMap, 1);
    generHall(tileMap, 4);
    generHall(tileMap, 3);
    generHall(tileMap, 2);






    for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
        checkj = j;
        if (arrayMap[1][j] == 2) {
            generMainRoom(tileHallMR, 3);
            if (arrayMap[1 + 1][j] == 2)
                generHall(tileMainRoom, 2);
            else
                createDoor(tileMainRoom, 2);
            if (arrayMap[1 - 1][j] != 2)
                createDoor(tileMainRoom, 1);
            generHall(tileMainRoom, 3);
        }
        else {
            if (arrayMap[1][j] == 1)
                generMapOne(tileHallMR, 3);
        }
    }

    for (int j = sizeMap / 2 - 1; j >= 0; j--) {
        checkj = j;
        if (arrayMap[1][j] == 2) {
            generMainRoom(tileHallML, 4);
            if (arrayMap[1 + 1][j] == 2)
                generHall(tileMainRoom, 2);
            else
                createDoor(tileMainRoom, 2);
            if (arrayMap[1 - 1][j] != 2)
                createDoor(tileMainRoom, 1);
            generHall(tileMainRoom, 4);
        }
        else {
            if (arrayMap[1][j] == 1)
                generMapOne(tileHallML, 4);
        }
    }

    for (int k = 2; k < sizeMap - 1; k++) {
        if (arrayMap[k][sizeMap / 2] == 2) {
            checkj = sizeMap / 2;
            generMainRoom(tileHallMU, 2);
            for (int dirMRoom = 1; dirMRoom < 4; dirMRoom++) {
                generHall(tileMainRoom, dirMRoom + 1);
            }
            for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
                checkj = j;
                if (arrayMap[k][j] == 2) {
                    generMainRoom(tileHallMR, 3);
                    if (arrayMap[k + 1][j] == 2)
                        generHall(tileMainRoom, 2);
                    else
                        createDoor(tileMainRoom, 2);
                    if (arrayMap[k - 1][j] != 2)
                        createDoor(tileMainRoom, 1);
                    generHall(tileMainRoom, 3);
                }
                else {
                    if (arrayMap[k][j] == 1)
                        generMapOne(tileHallMR, 3);
                }
            }

            for (int j = sizeMap / 2 - 1; j >= 0; j--) {
                checkj = j;
                if (arrayMap[k][j] == 2) {
                    generMainRoom(tileHallML, 4);
                    if (arrayMap[k + 1][j] == 2)
                        generHall(tileMainRoom, 2);
                    else
                        createDoor(tileMainRoom, 2);
                    if (arrayMap[k - 1][j] != 2)
                        createDoor(tileMainRoom, 1);
                    generHall(tileMainRoom, 4);
                }
                else {
                    if (arrayMap[k][j] == 1)
                        generMapOne(tileHallML, 4);
                }
            }
        }
    }

    generMapOne(tileHallMU, 2);

    delete[] arrayMap;
}


void Generation_map::border(TMXTiledMap* tiled) {
    auto layerCheck = tiled->getLayer("walls");
    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                /*auto X = layerCheck->getTileAt(Vec2(i, j))->getPosition().x;*/
                auto PositionTile = layerCheck->getTileAt(Vec2(i, j))->getPosition();
                auto Y = layerCheck->getTileAt(Vec2(i, j))->getTextureRect();
                edgeNode = Node::create();
                /*auto edgeBody = PhysicsBody::createBox(Size(Y.size), PHYSICSBODY_MATERIAL_DEFAULT);
                edgeBody->setDynamic(false);
                edgeNode->setPhysicsBody(edgeBody);*/
                edgeNode->setScale(2.0);
                edgeNode->setAnchorPoint(Vec2(0.5, 0.5));
                edgeNode->setPosition((PositionTile + Vec2(10, 10)) * 3 + tiled->getPosition());
                log("%f %f", edgeNode->getContentSize().width, edgeNode->getContentSize().height);
                PhysicHelper::createWallPhysicBody(edgeNode, Size(Y.size));
                this->addChild(edgeNode);
            }
        }
    }


}

void Generation_map::generHall(TMXTiledMap* PosMap, int direction) {
    auto MapX = PosMap->getPosition().x;
    auto MapY = PosMap->getPosition().y;

    switch (direction)
    {
    case 1://down
        tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
        tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (-tileHall->getMapSize().height) * 60));

        generMapOne(tileHall, direction);

        tileHall->setScale(3.0);
        tileHall->setAnchorPoint(Point(0, 0));
        border(tileHall);
        this->addChild(tileHall);

        break;
    case 2://up
        if (checkj == sizeMap / 2) {
            tileHallMU = TMXTiledMap::create("maps/hall_vertical.tmx");
            tileHallMU->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (PosMap->getMapSize().height) * 60));
            checkI += 1;

            tileHallMU->setScale(3.0);
            tileHallMU->setAnchorPoint(Point(0, 0));
            border(tileHallMU);
            this->addChild(tileHallMU);

        }
        else {
            tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
            tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (PosMap->getMapSize().height) * 60));

            tileHall->setScale(3.0);
            tileHall->setAnchorPoint(Point(0, 0));
            border(tileHall);
            this->addChild(tileHall);
        }
        //generMapOne(tileHall, direction);
        break;
    case 3://right
        tileHallMR = TMXTiledMap::create("maps/hall_horizont.tmx");
        tileHallMR->setPosition(Point(MapX + (PosMap->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height - 11) * 60));

        tileHallMR->setScale(3.0);
        tileHallMR->setAnchorPoint(Point(0, 0));
        border(tileHallMR);
        this->addChild(tileHallMR);

        //generMapOne(tileHall, direction);

        break;
    case 4://left
        tileHallML = TMXTiledMap::create("maps/hall_horizont.tmx");
        tileHallML->setPosition(Point(MapX + (-tileHallML->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height - 11) * 60));

        tileHallML->setScale(3.0);
        tileHallML->setAnchorPoint(Point(0, 0));
        border(tileHallML);
        this->addChild(tileHallML);

        //generMapOne(tileHall, direction);

        break;
    default:
        break;
    }


}

void Generation_map::generMapOne(TMXTiledMap* PosMap, int direction) {
    auto sizeMapX = PosMap->getPosition().x;
    auto sizeMapY = PosMap->getPosition().y;

    switch (direction)
    {
    case 1://down
        tileMapOne = TMXTiledMap::create("maps/room_down.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (-tileMapOne->getMapSize().height) * 60));

        break;
    case 2://up
        tileMapOne = TMXTiledMap::create("maps/room_up.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (PosMap->getMapSize().height) * 60));

        break;
    case 3://right
        tileMapOne = TMXTiledMap::create("maps/room_right.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 11) * 60));
        //tileMapOne->setPosition(Point(sizeMapX + (tileMapOne->getMapSize().width) * 60, sizeMapX + (PosMap->getMapSize().height - 4) * 60));

        break;
    case 4://left
        tileMapOne = TMXTiledMap::create("maps/room_left.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (-tileMapOne->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 11) * 60));

        break;
    default:
        break;
    }

    tileMapOne->setAnchorPoint(Point(0, 0));
    tileMapOne->setScale(3.0);
    border(tileMapOne);
    this->addChild(tileMapOne);

    /*if (direction == 1)
        createDoor(tileMapOne, 2);
    if (direction == 2)
        createDoor(tileMapOne, 1);

    createDoor(tileMapOne, direction);*/

}

void Generation_map::generMainRoom(TMXTiledMap* PosMap, int direction) {
    tileMainRoom = TMXTiledMap::create("maps/main_room.tmx");
    auto sizeMapX = PosMap->getPosition().x;
    auto sizeMapY = PosMap->getPosition().y;
    int check;
    switch (direction)
    {
    case 1://down
        tileMainRoom->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 8) * 60, sizeMapY + (-tileMainRoom->getMapSize().height) * 60));
        check = 2;
        break;
    case 2://up
        tileMainRoom->setPosition(Point(0, 5 * 60 + PosMap->getPosition().y));
        check = 1;
        break;
    case 3://right
        tileMainRoom->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 11) * 60));
        check = 4;
        break;
    case 4://left
        tileMainRoom->setPosition(Point(sizeMapX + (-tileMainRoom->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 11) * 60));
        check = 3;
        break;
    default:
        break;
    }


    /*for (int i = 1; i < 5; i++)
        if (i != check)
            generHall(tileMainRoom, i);

    generHall(tileMainRoom, 2);*/

    tileMainRoom->setAnchorPoint(Point(0, 0));
    tileMainRoom->setScale(3.0);
    border(tileMainRoom);


    this->addChild(tileMainRoom);
}

void Generation_map::createDoor(TMXTiledMap* tiled, int direction) {
    auto size = tiled->getMapSize();
    auto pos = tiled->getPosition();

    TMXTiledMap* wall;

    switch (direction)
    {
    case 1://down
        wall = TMXTiledMap::create("maps/wall_horizont.tmx");
        wall->setPosition(Vec2(pos.x + (size.width / 2 - 2) * 60, pos.y));
        break;
    case 2://up
        wall = TMXTiledMap::create("maps/wall_horizont.tmx");
        wall->setPosition(Vec2(pos.x + (size.width / 2 - 2) * 60, pos.y + (size.height - 1) * 60));
        break;
    case 3://right
        wall = TMXTiledMap::create("maps/wall_vertical.tmx");
        wall->setPosition(Vec2(pos.x, pos.y + (5) * 60));
        break;
    case 4://left
        wall = TMXTiledMap::create("maps/wall_vertical.tmx");
        wall->setPosition(Vec2(pos.x + (size.width - 1) * 60, pos.y + (5) * 60));
        break;
    default:
        break;
    }

    wall->setScale(3.0);
    border(wall);
    this->addChild(wall);
}



int** Generation_map::generationArrayMap(int sizeMap) {

    int x = sizeMap, y = sizeMap;

    int** a = new int* [sizeMap];
    for (int i = 0; i < sizeMap; i++)
        a[i] = new int[sizeMap];

    srand(time(0));
    int random;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (j == x / 2)
                a[i][j] = 2;
            else a[i][j] = 0;
            if (i == 0 || i == y - 1)
                a[i][x / 2] = 1;
        }
    }
    for (int i = 0; i < y; i++) {
        for (int j = x / 2 + 1; j < x; j++) {
            if (a[i][j - 1] == 1)
                break;
            random = 1 + rand() % 2;
            if (random == 1) {
                a[i][j] = random;
                break;
            }
            else
                a[i][j] = random;
            if (j == (x - 1))
                a[i][j] = 1;
        }
        for (int j = x / 2 - 1; j >= 0; j--) {
            if (a[i][j + 1] == 1)
                break;
            random = 1 + rand() % 2;
            if (random == 1) {
                a[i][j] = random;
                break;
            }
            else
                a[i][j] = random;
            if (j == 0)
                a[i][j] = 1;
        }
    }
    return a;
}