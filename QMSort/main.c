#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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

void setPosition(int X, int Y){
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position ={X, Y};

    SetConsoleCursorPosition(Screen, Position);
}


int test[10];


void quicksort(int init, int end){

    if(init < end){

        int pivot = end;
        int i = init - 1;
        int aux = 0;

        for(int j = init; j <= end; j++){

            if(test[pivot] >= test[j]){
                i++;
                aux = test[i];
                test[i] = test[j];
                test[j] = aux;
            }
        }

        pivot = i;

        quicksort(init, pivot - 1);
        quicksort(pivot + 1, end);
    }
}

void printArray(int passo, int swap, int number){

    if(swap == 0){
        printf("Array passo(%d NO SWAP(%d)):\n", passo, number);
        for(int i = 0; i < 20; i++){
            if(i < 19){
                printf("%d-", test[i]);
            }else{
                printf("%d", test[i]);
            }
        }
        printf("\n");
    }else{
        printf("Array passo(%d SWAP(%d)):\n", passo, number);
        for(int i = 0; i < 20; i++){
            if(i < 19){
                printf("%d-", test[i]);
            }else{
                printf("%d", test[i]);
            }
        }
        printf("\n");
    }

}

int main()
{
    srand(time(NULL));

    printf("Array inicial:\n");

    for(int i = 0; i < 10; i++){
            test[i] = randomRange(0, 20);
        if(i < 9){
            printf("%d-", test[i]);
        }else{
            printf("%d", test[i]);
        }
    }
    printf("\n");


    quicksort(0, 9);

    printf("Array final:\n");
    for(int i = 0; i < 10; i++){
        if(i < 9){
            printf("%d-", test[i]);
        }else{
            printf("%d", test[i]);
        }
    }
    printf("\n");


    return 0;
}
