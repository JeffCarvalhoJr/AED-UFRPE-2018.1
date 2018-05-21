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

void quicksort(int test[], int init, int end){

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

        quicksort(test, init, pivot - 1);
        quicksort(test, pivot + 1, end);
    }
}

void heapify(int array[], int index, int size){
    //children 1# = index * 2;
    //children 2# = index * 2 + 1;

    int biggest = index;
    int firstChild = index * 2 + 1;
    int secondChild = index * 2 + 2;

    if(firstChild < size && array[firstChild] > array[biggest]){
        biggest = firstChild;
    }

    if(secondChild < size && array[secondChild] > array[biggest]){
        biggest = secondChild;
    }

    if(biggest != index){
        //swap parent for children
        int aux = array[biggest];
        array[biggest] = array[index];
        array[index] = aux;

        heapify(array, biggest, size);
    }
}

void heapsort(int array[], int size){

    //heapinicial
    for(int i = size / 2 - 1; i >= 0; i--){
        heapify(array, i, size);
    }

    //enquanto tamanho do array for maior que 1
    //retirar o indice raiz (maior valor)
    //repetir o heapify
    while(size > 1){

        int aux = array[0];
        array[0] = array[size - 1];
        array[size - 1] = aux;
        size = size - 1;

        heapify(array, 0, size);
    }
}

int main(){
    srand(time(NULL));

    int test[10];

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


   // quicksort(test, 0, 9);
   // heapsort(test, 10);

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
