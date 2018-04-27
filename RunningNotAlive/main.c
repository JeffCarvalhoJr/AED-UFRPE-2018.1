#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

typedef struct CHARACTER{

    char name[20];
    int charID;
    int posX, posY;
    short isAlive;
    short isAI;
    int indexId;
    int ammoCount;

}Character;

typedef struct TILE{

    int type;
    int color;
    int posX, posY;
    short isOccupied;

}Tile;

typedef struct MAP{

    Tile tiles[100][100];
    int active_Zombies;
    Character zombies[15];
    Character player;
    int number_Debris;
    int sizeX, sizeY;

}Map;



int randomRange(int _min, int _max){

    int result = 0;
    int low_num = 0;
    int hi_num = 0;
    if(_min < _max){
        low_num = _min;
        hi_num = _max + 1;
    }else{
        low_num = _max + 1;
        hi_num = _min;
    }
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

void setPosition(int Y, int X){
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position ={X, Y};

    SetConsoleCursorPosition(Screen, Position);
}

char getTileGFX(int id){

    switch(id){
        //Map
    case 0:
        return ' ';
    case 1:
        return '[';
    case 2:
        return '>';
    case 10:
        return '=';
    case 11:
        return '0';
    case 12:
        return 'Y';
        //Player
    case 52:
        return '@';
        ///Enemies
    case 100:
        return 'Z';
        ///Consumables
    case 200:
        return '!';
    default:
        return 'X';
    }

}

void printMap(Map map){

    setPosition(0,0);

    for(int i = 0; i < map.sizeY; i++){
        for(int j = 0; j < map.sizeX; j++){
            setPosition(i, j);
            printf("%c", getTileGFX(map.tiles[i][j].type));
        }
    }
}

Map placeOnMapR(int objectType, int amount, Map newMap){

    int randY, randX;
    int tries = 1000;
    short isDone = 0;
    int currentAmount = 0;

    while (tries > 0 && (isDone == 0 || currentAmount < amount)){

        randY = randomRange(0, newMap.sizeY);
        randX = randomRange(0, newMap.sizeX);

        if(newMap.tiles[randY][randX].isOccupied == 0){
            newMap.tiles[randY][randX].isOccupied = 1;

            if(objectType == 100){
                Character newZombie;
                newZombie.isAI = 1;
                newZombie.isAlive = 1;
                newZombie.charID = 100;
                newZombie.posX = randX;
                newZombie.posY = randY;
                newZombie.indexId = amount;

                newMap.tiles[randY][randX].type = objectType;
                newMap.zombies[newZombie.indexId] = newZombie;
            }else if(objectType == 52){
                Character newPlayer;
                newPlayer.isAI = 0;
                newPlayer.isAlive = 1;
                newPlayer.ammoCount = 0;
                newPlayer.posX = randX;
                newPlayer.posY = randY;

                newMap.tiles[randY][randX].type = objectType;
                newMap.player = newPlayer;
            }else{
                newMap.tiles[randY][randX].type = objectType;
            }

            currentAmount++;
            if(currentAmount == amount){
                isDone = 1;
            }
        }else{
            tries--;
        }
    }

    return newMap;
}

Map map_Gen(int sizeY, int sizeX, Map newMap){

    //init map
    newMap.sizeX = sizeX;
    newMap.sizeY = sizeY;

    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            if(i == 0 || j == 0 || i == sizeY - 1 || j == sizeX - 1){
                newMap.tiles[i][j].type = 1;
                newMap.tiles[i][j].isOccupied = 1;
            }else{
                newMap.tiles[i][j].type = 0;
            }
        }
    }
    newMap = placeOnMapR(2, 1, newMap); //Place Exit

    newMap = placeOnMapR(10, 4, newMap);//Place Debris #1
    newMap = placeOnMapR(11, 7, newMap);//Place Debris #2
    newMap = placeOnMapR(12, 8, newMap);//Place Debris #3

    newMap = placeOnMapR(200, 4, newMap);//PlaceConsumables

    newMap = placeOnMapR(100, 15, newMap);//Place Enemies

    newMap = placeOnMapR(52, 1, newMap);//Place Player


    return newMap;
}

int main()
{
    srand(time(NULL));

    Map mainMap;

    mainMap = map_Gen(25, 100, mainMap);
    printMap(mainMap);


    return 0;
}
