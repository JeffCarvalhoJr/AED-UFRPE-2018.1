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
    int aiState;

}Character;

typedef struct TILE{

    int type;
    int color;
    int posX, posY;
    short isOccupied;
    short isPlayer;
    short isItem;
    short hasChar;
    int charIndex;

}Tile;

typedef struct MAP{

    Tile tiles[100][100];
    int active_Zombies;
    Character zombies[15];
    Character player;
    int number_Debris;
    int sizeX, sizeY;

}Map;

Map mainMap;

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
        return '|';
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

void updateMap(int posY, int posX, int type){

    setPosition(posY, posX);
    printf("%c", getTileGFX(type));
   // setPosition(29,0);
   // printf("**DEBUG**PrintID: %d", type);
   // getch();
}

Map placeOnMapR(int objectType, int amount, Map newMap){

    int randY, randX;
    int tries = 1000;
    short isDone = 0;
    int currentAmount = 0;

    while (tries > 0 && (isDone == 0 || currentAmount < amount)){

        randY = randomRange(0, newMap.sizeY - 1);
        randX = randomRange(0, newMap.sizeX  - 1);

        if(newMap.tiles[randY][randX].isOccupied == 0){
            newMap.tiles[randY][randX].isOccupied = 1;

            if(objectType == 100){
                Character newZombie;
                newZombie.isAI = 1;
                newZombie.isAlive = 1;
                newZombie.charID = 100;
                newZombie.posX = randX;
                newZombie.posY = randY;
                newZombie.indexId = currentAmount;
                newZombie.aiState = 0;

                newMap.tiles[randY][randX].type = objectType;
                newMap.tiles[randY][randX].hasChar = 1;
                newMap.tiles[randY][randX].charIndex = newZombie.indexId;
                newMap.zombies[newZombie.indexId] = newZombie;
                newMap.tiles[randY][randX].isPlayer = 0;
                //setPosition(29,0);
               // printf("**DEBUG**ZombieId: %d , zY: %d , zX: %d press any key to continue...", newZombie.indexId, newZombie.posY, newZombie.posX);
               // getch();

            }else if(objectType == 52){
                Character newPlayer;
                newPlayer.isAI = 0;
                newPlayer.isAlive = 1;
                newPlayer.ammoCount = 0;
                newPlayer.posX = randX;
                newPlayer.posY = randY;
                newPlayer.charID = 52;


                newMap.tiles[randY][randX].type = objectType;
                newMap.tiles[randY][randX].hasChar = 1;
                newMap.tiles[randY][randX].charIndex = -1;
                newMap.tiles[randY][randX].isPlayer = 1;
               // newMap.tiles[randY][randX].currentChar = newPlayer;
                newMap.player = newPlayer;
            }else if(objectType == 200){

                newMap.tiles[randY][randX].type = objectType;
                newMap.tiles[randY][randX].isItem = 1;
                newMap.tiles[randY][randX].isOccupied = 0;

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
                newMap.tiles[i][j].color = 0;
                newMap.tiles[i][j].isItem = 0;
                newMap.tiles[i][j].isOccupied = 0;
                newMap.tiles[i][j].isPlayer = 0;
                newMap.tiles[i][j].charIndex = -1;

            }
        }
    }
    newMap = placeOnMapR(2, 1, newMap); //Place Exit

    newMap = placeOnMapR(10, 4, newMap);//Place Debris #1
    newMap = placeOnMapR(11, 7, newMap);//Place Debris #2
    newMap = placeOnMapR(12, 8, newMap);//Place Debris #3

    newMap = placeOnMapR(200, 4, newMap);//PlaceConsumables

    newMap = placeOnMapR(100, 15, newMap);//Place Enemies
    newMap.active_Zombies = 15;

    newMap = placeOnMapR(52, 1, newMap);//Place Player


    return newMap;
}

void moveChar(Character *charToMove, int dir){

    int curY, curX;
    int nextY, nextX;
    int mapSizeY, mapSizeX;
    int charId;

    mapSizeY = mainMap.sizeY;
    mapSizeX = mainMap.sizeX;

    curY = charToMove->posY;
    curX = charToMove->posX;

    charId = charToMove->charID;

    short haveUpdate = 0;

    switch(dir){

    case 1: //north (Y--/X0)
        nextY = curY - 1;
        nextX = curX;
        if(nextY > 0 && mainMap.tiles[nextY][nextX].isOccupied == 0){
            mainMap.tiles[curY][curX].isOccupied = 0;
            mainMap.tiles[curY][curX].type = 0;
            mainMap.tiles[curY][curX].hasChar = 0;
            mainMap.tiles[curY][curX].charIndex = -1;
            mainMap.tiles[curY][curX].isPlayer = 0;

            mainMap.tiles[nextY][nextX].isOccupied = 1;
            mainMap.tiles[nextY][nextX].type = charId;
            mainMap.tiles[nextY][nextX].hasChar = 1;
            if(charToMove->isAI == 0){
                mainMap.tiles[nextY][nextX].isPlayer = 1;
                mainMap.tiles[nextY][nextX].charIndex = -1;
            }else{
                mainMap.tiles[nextY][nextX].isPlayer = 0;
                mainMap.tiles[nextY][nextX].charIndex = charToMove->indexId;
            }

            charToMove->posX = nextX;
            charToMove->posY = nextY;

            haveUpdate = 1;
        }
        break;
    case 2: //east (Y0/X++)
        nextY = curY;
        nextX = curX + 1;
        if(nextX < mapSizeX - 1 && mainMap.tiles[nextY][nextX].isOccupied == 0){
            mainMap.tiles[curY][curX].isOccupied = 0;
            mainMap.tiles[curY][curX].type = 0;
            mainMap.tiles[curY][curX].hasChar = 0;
            mainMap.tiles[curY][curX].charIndex = -1;
            mainMap.tiles[curY][curX].isPlayer = 0;

            mainMap.tiles[nextY][nextX].isOccupied = 1;
            mainMap.tiles[nextY][nextX].type = charId;
            mainMap.tiles[nextY][nextX].hasChar = 1;
            if(charToMove->isAI == 0){
                mainMap.tiles[nextY][nextX].isPlayer = 1;
                mainMap.tiles[nextY][nextX].charIndex = -1;
            }else{
                mainMap.tiles[nextY][nextX].isPlayer = 0;
                mainMap.tiles[nextY][nextX].charIndex = charToMove->indexId;
            }

            charToMove->posX = nextX;
            charToMove->posY = nextY;

            haveUpdate = 1;
        }
        break;
    case 3: //south (Y++/X0)
        nextY = curY + 1;
        nextX = curX;
        if(nextY < mapSizeY - 1 && mainMap.tiles[nextY][nextX].isOccupied == 0){
            mainMap.tiles[curY][curX].isOccupied = 0;
            mainMap.tiles[curY][curX].type = 0;
            mainMap.tiles[curY][curX].hasChar = 0;
            mainMap.tiles[curY][curX].charIndex = -1;
            mainMap.tiles[curY][curX].isPlayer = 0;

            mainMap.tiles[nextY][nextX].isOccupied = 1;
            mainMap.tiles[nextY][nextX].type = charId;
            mainMap.tiles[nextY][nextX].hasChar = 1;
             if(charToMove->isAI == 0){
                mainMap.tiles[nextY][nextX].isPlayer = 1;
                mainMap.tiles[nextY][nextX].charIndex = -1;
            }else{
                mainMap.tiles[nextY][nextX].isPlayer = 0;
                mainMap.tiles[nextY][nextX].charIndex = charToMove->indexId;
            }

            charToMove->posX = nextX;
            charToMove->posY = nextY;

            haveUpdate = 1;
        }
        break;
    case 4: //west (Y0/X--)
        nextY = curY;
        nextX = curX - 1;
        if(nextX > 0 && mainMap.tiles[nextY][nextX].isOccupied == 0){
            mainMap.tiles[curY][curX].isOccupied = 0;
            mainMap.tiles[curY][curX].hasChar = 0;
            mainMap.tiles[curY][curX].type = 0;
            mainMap.tiles[curY][curX].charIndex = -1;
            mainMap.tiles[curY][curX].isPlayer = 0;


            mainMap.tiles[nextY][nextX].isOccupied = 1;
            mainMap.tiles[nextY][nextX].type = charId;
            mainMap.tiles[nextY][nextX].hasChar = 1;
            if(charToMove->isAI == 0){
                mainMap.tiles[nextY][nextX].isPlayer = 1;
                mainMap.tiles[nextY][nextX].charIndex = -1;
            }else{
                mainMap.tiles[nextY][nextX].isPlayer = 0;
                mainMap.tiles[nextY][nextX].charIndex = charToMove->indexId;
            }

            charToMove->posX = nextX;
            charToMove->posY = nextY;

            haveUpdate = 1;
        }
        break;
    default:
        break;
    }

    if(haveUpdate){
        updateMap(curY, curX, mainMap.tiles[curY][curX].type);
        updateMap(nextY, nextX, charId);
    }
}

void enemyMovement(){

    for(int i = 0; i < mainMap.active_Zombies; i++){
        int randomDir = randomRange(1, 4);
        if(mainMap.zombies[i].isAlive == 1){
            int randMove;
            short foundPlayer = 0;
            int relativeX, relativeY;
            int moveDir;
            Tile tileToCheck;

            //Scan for player
            for(int y = -4; y < 4 && foundPlayer == 0; y++){
                for(int x = -4; x < 4 && foundPlayer == 0; x++){
                    if(mainMap.tiles[mainMap.zombies[i].posY + y][mainMap.zombies[i].posX + x].isPlayer == 1){
                        mainMap.zombies[i].aiState = 1;
                        relativeX = x;
                        relativeY = y;
                        foundPlayer = 1;
                    }
                }
            }

            if(mainMap.zombies[i].aiState == 1){
                 short coin = randomRange(0,1);

                if(relativeX < 0 && relativeY < 0){
                    //West or North (4 or 1)
                    if(coin == 1){
                        moveDir = 4;
                    }else{
                        moveDir = 1;
                    }
                }else if(relativeX < 0 && relativeY > 0){
                    //West or South (4 or 3)
                    if(coin == 1){
                        moveDir = 4;
                    }else{
                        moveDir = 3;
                    }
                }else if(relativeX > 0 && relativeY > 0){
                    //East or South (2 or 3)
                    if(coin == 1){
                        moveDir = 2;
                    }else{
                        moveDir = 3;
                    }
                }else if(relativeX > 0 && relativeY < 0){
                    //East or North (2 or 1)
                    if(coin == 1){
                        moveDir = 2;
                    }else{
                        moveDir = 1;
                    }
                }else if(relativeX == 0 && relativeY < 0){
                    //North
                    moveDir = 1;
                }else if(relativeX == 0 && relativeY > 0){
                    //South
                    moveDir = 3;
                }else if(relativeX < 0 && relativeY == 0){
                    //West
                    moveDir = 4;
                }else if(relativeX > 0 && relativeY == 0){
                    //East
                    moveDir = 2;
                }

                if(moveDir == 1){
                    //North
                    tileToCheck = mainMap.tiles[mainMap.zombies[i].posY - 1][mainMap.zombies[i].posX];
                    tileToCheck.posX = mainMap.zombies[i].posX;
                    tileToCheck.posY = mainMap.zombies[i].posY -1;
                }else if(moveDir == 2){
                    //East
                    tileToCheck = mainMap.tiles[mainMap.zombies[i].posY][mainMap.zombies[i].posX + 1];
                    tileToCheck.posX = mainMap.zombies[i].posX + 1;
                    tileToCheck.posY = mainMap.zombies[i].posY;
                }else if(moveDir == 3){
                    //South
                    tileToCheck = mainMap.tiles[mainMap.zombies[i].posY + 1][mainMap.zombies[i].posX];
                    tileToCheck.posX = mainMap.zombies[i].posX;
                    tileToCheck.posY = mainMap.zombies[i].posY +1;
                }else if(moveDir == 4){
                    //West
                    tileToCheck = mainMap.tiles[mainMap.zombies[i].posY][mainMap.zombies[i].posX - 1];
                    tileToCheck.posX = mainMap.zombies[i].posX - 1;
                    tileToCheck.posY = mainMap.zombies[i].posY;
                }

                if(tileToCheck.isPlayer == 1){
                    if(mainMap.player.ammoCount > 0){
                        //Zombie DED
                        mainMap.zombies[i].isAlive = 0;
                        mainMap.tiles[mainMap.zombies[i].posY][mainMap.zombies[i].posX].isOccupied = 0;
                        mainMap.tiles[mainMap.zombies[i].posY][mainMap.zombies[i].posX].type = 0;
                        mainMap.player.ammoCount--;
                    }else{
                        //Game Over
                        mainMap.player.isAlive = 0;
                        
                    }
                }else if(tileToCheck.isOccupied == 0){
                     moveChar(&mainMap.zombies[i], moveDir);
                }


            }else{
                randMove = randomRange(1, 100);
                if(randMove  < 25){
                    moveChar(&mainMap.zombies[i], randomRange(1,4));
                }
            }
       }
    }


}

void playerMovement(){

    Tile tileToCheck;
    int moveId;
    short hasMoved = 0;
    char userInput = getch();

        if(userInput == 'w'){
            //north
            tileToCheck = mainMap.tiles[mainMap.player.posY - 1][ mainMap.player.posX];
            tileToCheck.posX = mainMap.player.posX;
            tileToCheck.posY = mainMap.player.posY - 1;
            moveId = 1;
            hasMoved = 1;

        }else if(userInput == 'a'){
            //East
            tileToCheck = mainMap.tiles[mainMap.player.posY][mainMap.player.posX - 1];
            tileToCheck.posX = mainMap.player.posX;
            tileToCheck.posY = mainMap.player.posY - 1;
            moveId = 4;
            hasMoved = 1;

        }else if(userInput == 's'){
            //South
            tileToCheck = mainMap.tiles[mainMap.player.posY + 1][mainMap.player.posX];
            tileToCheck.posX = mainMap.player.posX;
            tileToCheck.posY = mainMap.player.posY + 1;
            moveId = 3;
            hasMoved = 1;

        }else if(userInput == 'd'){
            //West
            tileToCheck = mainMap.tiles[mainMap.player.posY][mainMap.player.posX + 1];
            tileToCheck.posX = mainMap.player.posX + 1;
            tileToCheck.posY = mainMap.player.posY;
            moveId = 2;
            hasMoved = 1;
        }else{
            //Skip turn
        }

        if(hasMoved == 1){
           if(tileToCheck.isOccupied == 0){
                if(tileToCheck.isItem == 1){
                    //Coletar item
                    mainMap.player.ammoCount++;
                    mainMap.tiles[tileToCheck.posY][tileToCheck.posX].isItem = 0;
                }
                //setPosition(29,0);
                //printf("TO MOVING   ");
                moveChar(&mainMap.player, moveId);
            }else if(tileToCheck.hasChar){
                //battle
                //setPosition(29,0);
                //printf("TO BATTLE");
                if(mainMap.player.ammoCount > 0){
                    mainMap.zombies[tileToCheck.charIndex].isAlive = 0;
                    mainMap.tiles[tileToCheck.posY][tileToCheck.posX].isOccupied = 0;
                    mainMap.tiles[tileToCheck.posY][tileToCheck.posX].type = 0;
                    mainMap.player.ammoCount--;
                    moveChar(&mainMap.player, moveId);
                }else{
                    //Game Over
                }


            }else{
                //Hit Obstacle
            }
        }

        setPosition(27,0);
        printf("X: %d Y: %d pressed: %c DONE!!!", mainMap.player.posX, mainMap.player.posY, userInput);

}


int main()
{
    srand(time(NULL));

    mainMap = map_Gen(25, 100, mainMap);
    printMap(mainMap);

    //Player movement
    while(mainMap.player.isAlive == 1){
        playerMovement();
        enemyMovement();
        //Zombies Movement

        setPosition(26, 0);
        printf("Balas: %d", mainMap.player.ammoCount);

    }
    return 0;
}
