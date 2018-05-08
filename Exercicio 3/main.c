#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
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
/*
    int sizeXMA, sizeYMA;

    scanf("%d", &sizeXMA);
    scanf("%d", &sizeYMA);

    int matrixA[sizeYMA][sizeXMA];

    for(int i = 0; i < sizeYMA; i++){
        for(int j = 0; j < sizeXMA; j++){
            matrixA[i][j] = randomRange(0,9);
        }
    }

    int matrixB[sizeXMA][sizeYMA];
    for(int i = 0; i < sizeXMA; i++){
        for(int j = 0; j < sizeYMA; j++){
            matrixB[i][j] = matrixA[j][i];
        }
    }

    printf("MATRIZ A \n");
    for(int i = 0; i < sizeYMA; i++){
        for(int j = 0; j < sizeXMA; j++){
            printf("%d", matrixA[i][j]);
        }
        printf("\n");
    }


    printf("\n MATRIZ B \n");
    for(int i = 0; i < sizeXMA; i++){
        for(int j = 0; j < sizeYMA; j++){
           printf("%d", matrixB[i][j]);
        }
        printf("\n");
    }
*/

    //Exercicio 3

    int numX;
    int result = 3;
    scanf("%d", &numX);

    for(int i = 1; i <= numX; i++){

        for(int x = 1; x <= i; x++){
            result 3= result * numX;
        }
    }

    printf("\n Result: %d", result);


}
