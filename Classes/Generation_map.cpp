#include "Generation_map.h"
#include "2d/CCFastTMXLayer.h"
#include <ctime>
#include "Fly.h"

USING_NS_CC;


Generation_map* Generation_map::createScene(bool checkLoc, Player* player, Vec2 posHero){
    Generation_map* gener = new Generation_map();
    gener->playerMiniMap = player;
    gener->posHero = posHero;
    gener->init(checkLoc);
    return gener;
}

bool Generation_map::init(bool checkLoc) {
    generation(checkLoc, 1);
    return true;
}

void Generation_map::generation(bool checkLoc, int statsEnemy) {
    cleanScene();
    checkPl = false;
    this->statsEnemy = statsEnemy;
    arrayMap = generationArrayMap(sizeMap);
    checkj = sizeMap / 2;

    tileMap = TMXTiledMap::create("maps/main_room.tmx");

    location2(tileMap, checkLoc);

    tileMap->setScale(3.0);
    tileMap->setAnchorPoint(Point(0, 0));
    this->addChild(tileMap);
    allMainRoom.push_back(tileMap);
    border(tileMap);
    
    //direction = 1;//["down"] 
    //direction = 2;//["up"]
    //direction = 3;//["right"]
    //direction = 4;//["left"] 

    generHall(tileMap, 1, checkLoc);
    generHall(tileMap, 4, checkLoc);
    generHall(tileMap, 3, checkLoc);
    generHall(tileMap, 2, checkLoc);


    for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
        checkj = j;
        if (arrayMap[1][j] == 2) {
            generMainRoom(tileHallMR, 3, checkLoc);
            if (arrayMap[1 + 1][j] == 2)
                generHall(tileMainRoom, 2, checkLoc);
            else
                createDoor(tileMainRoom, 2, checkLoc, false);
            if (arrayMap[1 - 1][j] != 2)
                createDoor(tileMainRoom, 1, checkLoc, false);
            generHall(tileMainRoom, 3, checkLoc);
        }
        else {
            if (arrayMap[1][j] == 1)
                generMapOne(tileHallMR, 3, checkLoc);
        }
    }

    for (int j = sizeMap / 2 - 1; j >= 0; j--) {
        checkj = j;
        if (arrayMap[1][j] == 2) {
            generMainRoom(tileHallML, 4, checkLoc);
            if (arrayMap[1 + 1][j] == 2)
                generHall(tileMainRoom, 2, checkLoc);
            else
                createDoor(tileMainRoom, 2, checkLoc, false);
            if (arrayMap[1 - 1][j] != 2)
                createDoor(tileMainRoom, 1, checkLoc, false);
            generHall(tileMainRoom, 4, checkLoc);
        }
        else {
            if (arrayMap[1][j] == 1)
                generMapOne(tileHallML, 4, checkLoc);
        }
    }

    for (int k = 2; k < sizeMap - 1; k++) {
        if (arrayMap[k][sizeMap / 2] == 2) {
            checkj = sizeMap / 2;
            generMainRoom(tileHallMU, 2, checkLoc);
            for (int dirMRoom = 1; dirMRoom < 4; dirMRoom++) {
                generHall(tileMainRoom, dirMRoom + 1, checkLoc);
            }
            for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
                checkj = j;
                if (arrayMap[k][j] == 2) {
                    generMainRoom(tileHallMR, 3, checkLoc);
                    if (arrayMap[k + 1][j] == 2)
                        generHall(tileMainRoom, 2, checkLoc);
                    else
                        createDoor(tileMainRoom, 2, checkLoc, false);
                    if (arrayMap[k - 1][j] != 2)
                        createDoor(tileMainRoom, 1, checkLoc, false);
                    generHall(tileMainRoom, 3, checkLoc);
                }
                else {
                    if (arrayMap[k][j] == 1)
                        generMapOne(tileHallMR, 3, checkLoc);
                }
            }

            for (int j = sizeMap / 2 - 1; j >= 0; j--) {
                checkj = j;
                if (arrayMap[k][j] == 2) {
                    generMainRoom(tileHallML, 4, checkLoc);
                    if (arrayMap[k + 1][j] == 2)
                        generHall(tileMainRoom, 2, checkLoc);
                    else
                        createDoor(tileMainRoom, 2, checkLoc, false);
                    if (arrayMap[k - 1][j] != 2)
                        createDoor(tileMainRoom, 1, checkLoc, false);
                    generHall(tileMainRoom, 4, checkLoc);
                }
                else {
                    if (arrayMap[k][j] == 1)
                        generMapOne(tileHallML, 4, checkLoc);
                }
            }
        }
    }

    generMapOne(tileHallMU, 2, checkLoc);

    createStore();
    generBarrel();
}

void Generation_map::location2(TMXTiledMap* tiled, bool checkLoc) {
    if (checkLoc == true) {
        auto layerCheck = tiled->getLayer("walls");
        auto loc2Wall = tiled->getLayer("loc2")->getTileGIDAt(Vec2(0, 0));

        for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
            for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
                if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                    layerCheck->setTileGID(loc2Wall, Vec2(i, j));
                }
            }
        }
        layerCheck->setVisible(true);
        tiled->getLayer("background")->setVisible(false);
    }
}

void Generation_map::border(TMXTiledMap* tiled) {
    auto layerCheck = tiled->getLayer("walls");
    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                auto PositionTile = layerCheck->getTileAt(Vec2(i, j))->getPosition();
                auto Y = layerCheck->getTileAt(Vec2(i, j))->getTextureRect();
                edgeNode = Node::create();
                /*auto edgeBody = PhysicsBody::createBox(Size(Y.size), PHYSICSBODY_MATERIAL_DEFAULT);
                edgeBody->setDynamic(false);
                edgeNode->setPhysicsBody(edgeBody);*/
                edgeNode->setScale(2.0);
                edgeNode->setAnchorPoint(Vec2(0.5, 0.5));
                edgeNode->setPosition((PositionTile + Vec2(10, 10)) * 3 + tiled->getPosition());
                auto body = PhysicHelper::createWallPhysicBody(edgeNode, Size(Y.size));
                allPhysicBody.push_back(body);
                this->addChild(edgeNode);
            }
        }
    }
}

void Generation_map::borderForRoom(TMXTiledMap* tiled) {
    auto layerCheck = tiled->getLayer("walls");
    for (int i = 0; i < layerCheck->getLayerSize().width; i++) {
        for (int j = 0; j < layerCheck->getLayerSize().height; j++) {
            if (layerCheck->getTileGIDAt(Vec2(i, j)) != 0) {
                auto PositionTile = layerCheck->getTileAt(Vec2(i, j))->getPosition();
                auto Y = layerCheck->getTileAt(Vec2(i, j))->getTextureRect();
                edgeNode = Node::create();
                edgeNode->setScale(2.0);
                edgeNode->setAnchorPoint(Vec2(0.5, 0.5));
                edgeNode->setPosition((PositionTile + Vec2(10, 10)) * 3 + tiled->getPosition());
                auto body = PhysicHelper::createWallPhysicBody(edgeNode, Size(Y.size));

                //������� �� ������ border() 
                PhBoDoorRoom.push_back(body);

                this->addChild(edgeNode);
            }
        }
    }
}

void Generation_map::generHall(TMXTiledMap* PosMap, int direction, bool checkLoc) {
    auto MapX = PosMap->getPosition().x;
    auto MapY = PosMap->getPosition().y;

    switch (direction)
    {
    case 1://down
        tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
        tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (-tileHall->getMapSize().height) * 60));

        generMapOne(tileHall, direction, checkLoc);

        tileHall->setScale(3.0);
        tileHall->setAnchorPoint(Point(0, 0));
        border(tileHall);
        this->addChild(tileHall); 
        location2(tileHall, checkLoc);
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
            location2(tileHallMU, checkLoc);
        }
        else {
            tileHall = TMXTiledMap::create("maps/hall_vertical.tmx");
            
            tileHall->setPosition(Point(MapX + (PosMap->getMapSize().width / 5) * 60, MapY + (PosMap->getMapSize().height) * 60));

            tileHall->setScale(3.0);
            tileHall->setAnchorPoint(Point(0, 0));
            border(tileHall);
            this->addChild(tileHall);
            location2(tileHall, checkLoc);
        }
        //generMapOne(tileHall, direction);
        break;
    case 3://right
        tileHallMR = TMXTiledMap::create("maps/hall_horizont.tmx");
        
        tileHallMR->setPosition(Point(MapX + (PosMap->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height - 10) * 60));

        tileHallMR->setScale(3.0);
        tileHallMR->setAnchorPoint(Point(0, 0));
        border(tileHallMR);
        this->addChild(tileHallMR);
        location2(tileHallMR, checkLoc);

        break;
    case 4://left
        tileHallML = TMXTiledMap::create("maps/hall_horizont.tmx");
        
        tileHallML->setPosition(Point(MapX + (-tileHallML->getMapSize().width) * 60, MapY + (PosMap->getMapSize().height - 10) * 60));

        tileHallML->setScale(3.0);
        tileHallML->setAnchorPoint(Point(0, 0));
        border(tileHallML);
        this->addChild(tileHallML);

        location2(tileHallML, checkLoc);
        break;
    default:
        break;
    }
}

void Generation_map::generMapOne(TMXTiledMap* PosMap, int direction, bool checkLoc) {
    auto sizeMapX = PosMap->getPosition().x;
    auto sizeMapY = PosMap->getPosition().y;

    switch (direction)
    {
    case 1://down
        tileMapOne = TMXTiledMap::create("maps/room_down.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (-tileMapOne->getMapSize().height) * 60));
        allMapOne.push_back(tileMapOne);
        break;
    case 2://up
        tileMapOne = TMXTiledMap::create("maps/room_up.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width - 10) * 60, sizeMapY + (PosMap->getMapSize().height) * 60));

        allMapOne.push_back(tileMapOne);
        break;
    case 3://right
        tileMapOne = TMXTiledMap::create("maps/room_right.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));
        //tileMapOne->setPosition(Point(sizeMapX + (tileMapOne->getMapSize().width) * 60, sizeMapX + (PosMap->getMapSize().height - 4) * 60));

        allMapOne.push_back(tileMapOne);
        break;
    case 4://left
        tileMapOne = TMXTiledMap::create("maps/room_left.tmx");
        tileMapOne->setPosition(Point(sizeMapX + (-tileMapOne->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));

        allMapOne.push_back(tileMapOne);
        break;
    default:
        break;
    }
    
    tileMapOne->setAnchorPoint(Point(0, 0));
    tileMapOne->setScale(3.0);
    border(tileMapOne);
    this->addChild(tileMapOne);
    location2(tileMapOne, checkLoc);
}

void Generation_map::generMainRoom(TMXTiledMap* PosMap, int direction, bool checkLoc) {
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
        tileMainRoom->setPosition(Point(sizeMapX + (PosMap->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));
        check = 4;
        break;
    case 4://left
        tileMainRoom->setPosition(Point(sizeMapX + (-tileMainRoom->getMapSize().width) * 60, sizeMapY + (PosMap->getMapSize().height - 10) * 60));
        check = 3;
        break;
    default:
        break;
    }
    tileMainRoom->setAnchorPoint(Point(0, 0));
    tileMainRoom->setScale(3.0);
    border(tileMainRoom);
    
    this->addChild(tileMainRoom);
    allMainRoom.push_back(tileMainRoom);
    location2(tileMainRoom, checkLoc);
}

void Generation_map::createDoor(TMXTiledMap* tiled, int direction, bool checkLoc, bool checkDelRoom) {
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
    if (checkDelRoom == true) {
        borderForRoom(wall);
        childDoorRoom.push_back(wall);
    }
    else border(wall);
    this->addChild(wall);
    location2(wall, checkLoc);
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

Vec2 Generation_map::getPosTileMapOneEnd() {
    return tileMapOne->getPosition();
}

Size Generation_map::getSizeTileMapOneEnd() {
    return tileMapOne->getMapSize();
}

std::vector<TMXTiledMap*> Generation_map::getAllMapOne() {
    return allMapOne;
}

std::vector<TMXTiledMap*> Generation_map::getAllMapMain() {
    return allMainRoom;
}

std::vector<Unit*> Generation_map::checkRoom(Unit* player, std::vector<Unit*> enemies, bool checkLoc) {
    quantityEnemy = enemies.size();
    if (checkDoorRoom == false) {
        auto posPX = player->getPosition().x;
        auto posPY = player->getPosition().y;
        Size sizeMap;
        Vec2 posMap;
        int posAX, posAY, posBX, posBY;

        for (int i = 0; i < allMainRoom.size(); i++) {
            sizeMap = allMainRoom[i]->getMapSize();
            posMap = allMainRoom[i]->getPosition();

            posAX = posMap.x + 80;
            posAY = posMap.y + ((sizeMap.height - 1) * 60 - 20);
            posBX = posMap.x + ((sizeMap.width - 1) * 60 - 20);
            posBY = posMap.y + 80;
            
            if (posPX >= posAX && posPX <= posBX && posPY <= posAY && posPY >= posBY) {
                for (int j = 1; j < 5; j++) {
                    createDoor(allMainRoom[i], j, checkLoc, true);
                }
                enemies = createEnemy(enemies, allMainRoom[i], player);
                checkDoorRoom = true;
                allMainRoom.erase(allMainRoom.begin() + i);
                playerMiniMap->SetInvulnerable(TIMEIMOORT);
            }
        }
        for (int i = 0; i < allMapOne.size(); i++) {
            sizeMap = allMapOne[i]->getMapSize();
            posMap = allMapOne[i]->getPosition();

            posAX = posMap.x + 80;
            posAY = posMap.y + ((sizeMap.height - 1) * 60 - 20);
            posBX = posMap.x + ((sizeMap.width - 1) * 60 - 20);
            posBY = posMap.y + 80;

            if (posPX >= posAX && posPX <= posBX && posPY <= posAY && posPY >= posBY) {
                for (int j = 1; j < 5; j++) {
                    createDoor(allMapOne[i], j, checkLoc, true);
                }
                enemies = createEnemy(enemies, allMapOne[i], player);
                checkDoorRoom = true;
                allMapOne.erase(allMapOne.begin() + i);
                playerMiniMap->SetInvulnerable(TIMEIMOORT);
            }
        }
    }
    else {
        if (quantityEnemy == 0) {
            for (int i = 0; i < PhBoDoorRoom.size(); i++) {
                PhysicHelper::world->DestroyBody(PhBoDoorRoom[i]);
            }
            for (int i = 0; i < childDoorRoom.size(); i++) {
                this->removeChild(childDoorRoom[i], true);
            }
            childDoorRoom.clear();
            PhBoDoorRoom.clear();
            checkDoorRoom = false;
        }
    }
    return enemies;
}

std::vector<Unit*> Generation_map::createEnemy(std::vector<Unit*> enemies, TMXTiledMap* tiled, Unit* player) {
    srand(time(0));
    int count = 3 + rand() % 5;
    Enemy* enemy;
    for (int i = 0; i < count; i++) {
        int enemyType = 1 + rand() % 2;
        

        int rX = ((tiled->getMapSize().width - 3) * 60);
        int rY = ((tiled->getMapSize().height - 3) * 60);

        int randomX = (tiled->getPosition().x + 100) + rand() % rX;
        int randomY = (tiled->getPosition().y + 80) + rand() % rY;

        switch (enemyType)
        {
        case 1:
            enemy = Goblin::create(Point(randomX, randomY), static_cast<Player*>(player));
            break;
        case 2:
            //enemy = SlimeKing::create(Point(randomX, randomY), static_cast<Player*>(player), 3);
            enemy = Slime::create(Point(randomX, randomY));
            break;
        /*case 3:
            enemy = Fly::create(this, Point(randomX, randomY));
            break;*/
        default:
            break;
        }
        static_cast<Enemy*>(enemy)->statsScale(statsEnemy);
        this->addChild(enemy, 2);

        enemies.push_back(enemy);
    }
    return enemies;
}

void Generation_map::createStore() {
    srand(time(0));

    auto countMap = allMapOne.size() - 1;
    auto mapLocation = 1 + rand() % (countMap - 1);

    for (int i = 0; i < allPhStore.size(); i++)
        PhysicHelper::world->DestroyBody(allPhStore[i]);

    store = Store::createScene(allMapOne[mapLocation]);
    this->addChild(store);

    auto items = store->getItems();
    for (int i = 0; i < items.size(); i++)
        this->addChild(items[i]);

    allPhStore = store->getTray();

    allMapOne.erase(allMapOne.begin() + mapLocation);
    auto storeMap = store->getMap();
    border(storeMap);
}

void Generation_map::generBarrel() {
    srand(time(0));
    
    int count = 3 + rand() % 4;
    for (int i = 0; i < allMainRoom.size(); i++) {
        for (int j = 0; j < count; j++) {
            int rX = ((allMainRoom[i]->getMapSize().width - 3) * 60);
            int rY = ((allMainRoom[i]->getMapSize().height - 3) * 60);

            int randomX = (allMainRoom[i]->getPosition().x + 100) + rand() % rX;
            int randomY = (allMainRoom[i]->getPosition().y + 80) + rand() % rY;

            auto enemy = Fly::create(Point(randomX, randomY));
            allPhysicBarrel.push_back(enemy);
        }
    }
}

void Generation_map::miniMap(int idRoom) {
    Generation_map* gener = new Generation_map();
    Node* layer = Node::create();
    //layer->setPosition(playerMiniMap->getPosition());
    //layer->setPosition(Vec2(320, 320));


    std::vector<Sprite*> allDrawRoom;
    std::vector<Sprite*> allDrawMainRoom;
    int konMap;
    int k = 0, z = 0;
    int sizeX = 0, sizeY = 0;
    int posMapX = 500, posMapY = -70;

    miniRoom = Sprite::create("miniMap/miniRoom.png");
    miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
    miniRoom->setScale(2.5);
    layer->addChild(miniRoom, 5);
    allDrawMainRoom.push_back(miniRoom);
    allDrawRoom.push_back(miniRoom);

    for (int i = 1; i <= 4; i++) {
        auto hall = miniHall(miniRoom, i);
        layer->addChild(hall, 5);
    }

    Sprite* miniRoomD = Sprite::create("miniMap/miniRoom.png");
    miniRoomD->setPosition(Vec2(sizeX + posMapX, posMapY - 50));
    miniRoomD->setScale(2.5);
    layer->addChild(miniRoomD, 5);
    allDrawRoom.push_back(miniRoomD);
    sizeX += 50;

    for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
        if (arrayMap[1][j] == 2) {
            miniRoom = Sprite::create("miniMap/miniRoom.png");
            miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
            miniRoom->setScale(2.5);
            layer->addChild(miniRoom, 5);
            allDrawMainRoom.push_back(miniRoom);

            if (arrayMap[1 + 1][j] == 2) {
                auto hall = miniHall(miniRoom, 2);
                layer->addChild(hall, 5);
            }
            auto hall = miniHall(miniRoom, 3);
            layer->addChild(hall, 5);
        }
        else {
            if (arrayMap[1][j] == 1) {
                miniRoom = Sprite::create("miniMap/miniRoom.png");
                miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                miniRoom->setScale(2.5);
                layer->addChild(miniRoom, 5);
            }
        }
        allDrawRoom.push_back(miniRoom);
        sizeX += 50;
    }
    sizeX = -50;

    for (int j = sizeMap / 2 - 1; j >= 0; j--) {
        if (arrayMap[1][j] == 2) {
            miniRoom = Sprite::create("miniMap/miniRoom.png");
            miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
            miniRoom->setScale(2.5);
            layer->addChild(miniRoom, 5);
            allDrawMainRoom.push_back(miniRoom);

            if (arrayMap[1 + 1][j] == 2) {
                auto hall = miniHall(miniRoom, 2);
                layer->addChild(hall, 5);
            }
            auto hall = miniHall(miniRoom, 4);
            layer->addChild(hall, 5);
        }
        else {
            if (arrayMap[1][j] == 1) {
                miniRoom = Sprite::create("miniMap/miniRoom.png");
                miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                miniRoom->setScale(2.5);
                layer->addChild(miniRoom, 5);
            }
        }
        allDrawRoom.push_back(miniRoom);
        sizeX -= 50;
    }
    sizeX = 0;
    sizeY += 50;

    for (int k = 2; k < sizeMap - 1; k++) {
        if (arrayMap[k][sizeMap / 2] == 2) {
            miniRoom = Sprite::create("miniMap/miniRoom.png");
            miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
            miniRoom->setScale(2.5);
            layer->addChild(miniRoom, 5);
            allDrawMainRoom.push_back(miniRoom);
            allDrawRoom.push_back(miniRoom);
            sizeX += 50;

            for (int dirMRoom = 1; dirMRoom < 4; dirMRoom++) {
                auto hall = miniHall(miniRoom, dirMRoom + 1);
                layer->addChild(hall, 5);
            }
            for (int j = sizeMap / 2 + 1; j < sizeMap; j++) {
                if (arrayMap[k][j] == 2) {
                    miniRoom = Sprite::create("miniMap/miniRoom.png");
                    miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                    miniRoom->setScale(2.5);
                    layer->addChild(miniRoom, 5);
                    allDrawMainRoom.push_back(miniRoom);
                    allDrawRoom.push_back(miniRoom);
                    sizeX += 50;
                    if (arrayMap[k + 1][j] == 2) {
                        auto hall = miniHall(miniRoom, 2);
                        layer->addChild(hall, 5);
                    }
                    auto hall = miniHall(miniRoom, 3);
                    layer->addChild(hall, 5);
                }
                else {
                    if (arrayMap[k][j] == 1) {
                        miniRoom = Sprite::create("miniMap/miniRoom.png");
                        miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                        miniRoom->setScale(2.5);
                        layer->addChild(miniRoom, 5);
                        allDrawRoom.push_back(miniRoom);
                        sizeX += 50;
                    }
                }
            }
            sizeX = -50;
            for (int j = sizeMap / 2 - 1; j >= 0; j--) {
                if (arrayMap[k][j] == 2) {
                    miniRoom = Sprite::create("miniMap/miniRoom.png");
                    miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                    miniRoom->setScale(2.5);
                    layer->addChild(miniRoom, 5);
                    allDrawMainRoom.push_back(miniRoom);
                    allDrawRoom.push_back(miniRoom);
                    sizeX -= 50;
                    if (arrayMap[k + 1][j] == 2) {
                        auto hall = miniHall(miniRoom, 2);
                        layer->addChild(hall, 5);
                    }
                    auto hall = miniHall(miniRoom, 4);
                    layer->addChild(hall, 5);
                }
                else {
                    if (arrayMap[k][j] == 1) {
                        miniRoom = Sprite::create("miniMap/miniRoom.png");
                        miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
                        miniRoom->setScale(2.5);
                        layer->addChild(miniRoom, 5);
                        allDrawRoom.push_back(miniRoom);
                        sizeX -= 50;
                    }
                }
            }
        }
        sizeY += 50;
        sizeX = 0;
    }

    miniRoom = Sprite::create("miniMap/miniRoom.png");
    miniRoom->setPosition(Vec2(sizeX + posMapX, sizeY + posMapY));
    miniRoom->setScale(2.5);
    layer->addChild(miniRoom, 5);
    allDrawRoom.push_back(miniRoom);

    Vec2 dotPlayer;
    dotPlayer = Vec2(allDrawMainRoom[idRoom]->getPosition().x + (posHero.x / 18) - FirstPosPl.x + 1, allDrawMainRoom[idRoom]->getPosition().y + posHero.y / 22.8 - FirstPosPl.y);

    this->colorMiniRoom =miniRoom->getColor();
    //return layer;
    this->allDrawRoom = allDrawRoom;
    this->allDrawMainRoom = allDrawMainRoom;
    this->layer = layer;
    this->dotPlayer = dotPlayer;
    this->addChild(layer, 5);
    allMainRoom.erase(allMainRoom.begin() + idRoom);
}

void Generation_map::addMiniMap(Player* player, Vec2 posHero, int idRoom, Point posHUD) {
    
    if (checkPl == false) {
        FirstPosPl = Vec2(posHero.x / 18, posHero.y / 22.8);
        checkPl = true;        
    }
    layer->setPosition(posHUD);
    dotPlayer = (Vec2(allDrawMainRoom[idRoom]->getPosition().x + (posHero.x / 18) - FirstPosPl.x + 1, allDrawMainRoom[idRoom]->getPosition().y + posHero.y / 22.8 - FirstPosPl.y));
    
    //������������ ����� � ��������� 
    /*removeChild(draw);
    draw = DrawNode::create();
    draw->drawDot(dotPlayer+posHUD, 2, Color4F::RED);
    addChild(draw);
    */


    for (int i = 0; i < allDrawRoom.size(); i++) {

        auto posPX = dotPlayer.x;
        auto posPY = dotPlayer.y;

        auto posAX = allDrawRoom[i]->getPosition().x - 20;
        auto posAY = allDrawRoom[i]->getPosition().y + 20;

        auto posBX = allDrawRoom[i]->getPosition().x + 20;
        auto posBY = allDrawRoom[i]->getPosition().y - 20;
        
        //log("Px=%f Py=%f BX=%f BY=%f", posPX, posPY, allDrawRoom[1 - 1]->getPosition().x, allDrawRoom[1 - 1]->getPosition().y);
        if (posPX >= posAX && posPX <= posBX && posPY <= posAY && posPY >= posBY)
            allDrawRoom[i]->setColor(Color3B::GRAY);
        else 
            if (allDrawRoom[i]->getColor() ==  Color3B::GRAY) 
                allDrawRoom[i]->setColor(colorMiniRoom);
           
    }
}

Sprite* Generation_map::miniHall(Sprite* miniRoom, int dir) {
    Sprite* miniHall = Sprite::create();
    miniHall->initWithFile("miniMap/miniHall.png");
    miniHall->setScale(2.5);

    auto posRoom = miniRoom->getPosition();
    auto sizeRoom = miniRoom->getBoundingBox().size;

    switch (dir)
    {
    case 1://down
        miniHall->setPosition(Vec2(posRoom.x, posRoom.y - sizeRoom.height / 1.25));
        break;
    case 2://up
        miniHall->setPosition(Vec2(posRoom.x, posRoom.y + sizeRoom.height / 1.25));
        break;
    case 3://right
        miniHall->setPosition(Vec2(posRoom.x + sizeRoom.width / 1.25, posRoom.y));
        miniHall->setRotation(90);
        break;
    case 4://left
        miniHall->setPosition(Vec2(posRoom.x - sizeRoom.width / 1.25, posRoom.y));
        miniHall->setRotation(90);
        break;
    default:
        break;
    }
    return miniHall;
}

void Generation_map::cleanScene() {
    this->removeAllChildren();
    this->removeChild(layer);
    allMainRoom.clear();
    allMapOne.clear();
    for (int i = 0; i < allPhysicBody.size(); i++)
        PhysicHelper::world->DestroyBody(allPhysicBody[i]);
    allPhysicBody.clear();
    allPhysicBarrel.clear();
    for (int i = 0; i < Director::getInstance()->getRunningScene()->getChildren().size(); i++) {
        if (Director::getInstance()->getRunningScene()->getChildren().at(i)->getTag() != ContactListener::PLAYER)
            Director::getInstance()->getRunningScene()->getChildren().at(i)->setName(DEAD_TAG);
    }
}

std::vector<Unit*> Generation_map::getBarrel() {
    return allPhysicBarrel;
}