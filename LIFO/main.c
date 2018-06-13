#include <stdio.h>
#include <stdlib.h>



void push(int value, int *list, int *index){

    if((*index) < 10 - 1){
        (*index) = (*index) + 1;
        list[(*index)] = value;
    }

}


void pop(int *index){

    if(*index > -1){
        (*index) = (*index) - 1;
    }

}

void printList(int *list, int size){

    printf("\n---Pilha---\n");
    for(int i = 0; i <= size; i++){
        printf("%d", list[i]);
        printf("-");
    }

    printf("\n");
}


int main()
{
    int lista[10];
    int topIndex = -1;

    int userChoice;
    int addValue;

    do{
        printf("escolha sua acao: \n[1]Inserir na pilha \n[2]Retirar da fila");
        scanf("%d", &userChoice);

        switch(userChoice){
            case 1:
                printf("\nDigite o valor a ser adicionado: ");
                scanf("%d", &addValue);
                push(addValue, lista, &topIndex);

                break;
            case 2:
                pop(&topIndex);
                break;
            default:
                break;
        }
        system("cls");
        printList(lista,topIndex);
    }while(userChoice == 1 || userChoice == 2);



    return 0;
}

