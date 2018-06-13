#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define maxQueue 10


int headEntry;
int tailEntry;
int queueSize;



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

void printArray(int array[maxQueue]){
    setPosition(1,0);
    for(int i = 0; i < maxQueue; i++){
        if(queueSize < 1){
             printf("X-");
        }else{
            if(tailEntry < headEntry){
                if(i > tailEntry - 1 && i < headEntry){
                        printf("X-");
                }else{
                        printf("%d-", array[i]);
                }
             }else if(tailEntry > headEntry){
                if(i < headEntry || i > tailEntry - 1){
                    printf("X-");
                }else{
                    printf("%d-", array[i]);
                }
            }else{
                printf("%d-", array[i]);
            }
        }
    }
}

void push(int *array){
    if(queueSize < maxQueue){
        if(tailEntry < maxQueue){
            array[tailEntry] = 1;
            tailEntry++;
            if(tailEntry >= maxQueue){
                tailEntry = 0;
            }
            queueSize++;
        }
    }else{
        //Full Queue
    }
}

int pop(){

    if(queueSize > 0){
        if(headEntry < maxQueue){
            headEntry++;
            if(headEntry == 10){
                headEntry = 0;
            }
        }else{
            headEntry = 0;
        }
        queueSize--;
    }else{
        //Empty Queue
    }
}

int main()
{
    int array[maxQueue];
    int userInput;

    queueSize = 0;
    headEntry = 0;
    tailEntry = 0;

    printf("FIFO Implementation\n");

    printArray(array);

    setPosition(5,0);
    printf("(1)Push");
    setPosition(6,0);
    printf("(2)Pop");

    srand(time(NULL));




    do{
        setPosition(7,0);
        printf("Command:");
        scanf("%d", &userInput);
        switch(userInput){
            case 1:
                push(array);
                break;
            case 2:
                pop();
                break;
            default:
                break;
        }
        setPosition(3,0);
        printf("Queue Size: %d\tTail Position: %d\tHead Position: %d \n", queueSize,tailEntry, headEntry);
        printArray(array);
    }while(userInput != 1 || userInput != 2);


    tailEntry = 0;
    headEntry = 0;
    queueSize = 0;


    return 0;
}
