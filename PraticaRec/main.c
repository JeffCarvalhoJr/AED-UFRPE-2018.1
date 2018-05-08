#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main()
{
    srand(time(NULL));

    int teste[5];
    printf("\t|Array Original|");
    for(int i = 0; i < 5; i++){
        teste[i] = randomRange(0, 100);
        printf("\n%d", teste[i]);
    }

    int result = 0;

    result = sum_R(teste, 5);

    printf("\n\nresultado soma dos elementos do array: %d", result);

    result = mult_R(teste, 5);
    printf("\n\nresultado multiplicacao: %d", result);

    int randomFat = randomRange(0, 10);
    result = fat_R(5);

    printf("\n\nresultado fatoracao(%d): %d", randomFat,result);

    int indiceFibo = randomRange(1, 20);
    printf("\n\nfibonacci (%d): %d", indiceFibo,fibo_R(indiceFibo));

    int randomIndex = randomRange(0, 4);

    printf("\n\nInserir 52 no indice %d", randomIndex);
    insert_R(teste, 5, randomIndex, 52);

    int randomRemove = randomRange(0, 100);
    printf("\n\nse existir remover %d do array", randomRemove);
    remove_R(teste, 5, randomRemove);

    int indiceDaBusca, valorProcurar;
    valorProcurar = randomRange(0, 100);

    printf("\n\nProcurar pelo valor: %d ", valorProcurar);
    indiceDaBusca = search_R(teste, 5, valorProcurar);

    if(indiceDaBusca == - 1){
        printf("\nnao encontrado");
    }else{
        printf("\nO Indice do numero procurado eh %d", indiceDaBusca);
    }
     printf("\n\n\t| ARRAY TESTE ANTES DO SORT |");
    for(int i = 0; i < 5; i++){
        printf("\n%d", teste[i]);
    }

    jeffSort(teste, 5);

    printf("\n\t| ARRAY TESTE DEPOIS DO SORT |");
    for(int i = 0; i < 5; i++){
        printf("\n%d", teste[i]);
    }
}

int sum_R(int arr[5], int index){

    if(index > 0){
        return arr[index - 1] + sum_R(arr, index - 1);
    }else{
        return 0;
    }

}

int mult_R(int arr[5], int index){

    if(index > 0){
        return arr[index-1] * mult_R(arr, index - 1);
    }else{
        return 1;
    }
}

int fat_R(int input){

    if(input > 0){
        return input * fat_R(input - 1);
    }else{
        return 1;
    }

}

int fibo_R(int input){

    if(input == 1 || input == 2){
        return 1;
    }else{
         return fibo_R(input - 1) + fibo_R(input - 2);
    }

}

void insert_R(int array[5], int arrSize, int index, int value){

    if(index == arrSize - 1){
        array[index] = value;
        return;
    }else if(arrSize > 0){
        return insert_R(array, arrSize - 1, index, value);
    }else{
        return;
    }

}

void remove_R(int array[5], int arrSize, int value){

    if(array[arrSize - 1] == value){
        array[arrSize - 1] = 0;
        return;
    }else if(arrSize > 0){
        return remove_R(array, arrSize - 1, value);
    }else{
        return;
    }

}

int search_R(int array[5], int arraySize, int value){

    if(array[arraySize - 1] == value){
        return arraySize - 1;
    }else if(arraySize > 0){
        return search_R(array, arraySize - 1, value);
    }else{
        return -1;
    }
}

void jeffSort(int array[5], int arraySize){

    static int count = 0;

    if(count < arraySize){
        if(array[arraySize - 1] < array[count]){
            //substituir
            //count volta a ser 0
            //chamar a recursao
            int aux;
            aux = array[count];
            array[count] = array[arraySize - 1];
            array[arraySize - 1] = aux;
            count = 0;
            jeffSort(array, arraySize);
        }else{
            //continuar
            //count ++
            //chamar a recursao
            count++;
            jeffSort(array, arraySize);
        }
    }else{
        if(arraySize > 0){
            //chamar a unção com arraySize menor
            count = 0;
            jeffSort(array, arraySize - 1);
        }else{
            //array size nao pode diminuir, sair da recurssão
            return;
        }
    }
}
