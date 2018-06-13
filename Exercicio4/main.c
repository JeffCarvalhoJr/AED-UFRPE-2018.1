#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct CLIENT{

    char name[20];
    char cpf[11];
    int status;

}client;

void insertClient(client *clientDB,  int clientID){

    client newClient;
    char newCpf[11];
    char newName[20];

    printf("\n Digite o cpf: ");
    gets(newCpf);
    printf("\n Digite o nome: ");
    gets(newName);

    strcpy(newClient.cpf, newCpf);
    strcpy(newClient.name, newName);
    newClient.status = 1;

    clientDB  = (client *)malloc((clientID + 1) * sizeof(client));
    clientDB[clientID] = newClient;

}

void removeClient(client *clientsDB, int activeClients){

    char cpfToRemove[11];

    gets(cpfToRemove);


    for(int i = 0; i < activeClients; i++){


    }

}

void searchClient(client *clientsDB, char *cpf, int activeClients){

    //print Client data

     for(int i = 0; i < activeClients - 1; i++){
        if(strcmp(cpf, clientsDB[i].cpf) != 0){
            printf("\nexiste");
        }
    }

}

int main()
{

    client *clientes;
    client newClient;
    int clientNumber = 0;
    int userChoice;

      printf("Digita a acao: ");
   // scanf("%d", &userChoice);
    userChoice = 1;
    //Escolha a ação:
    //1. inserir
    //2. remover
    //3. buscar

    while(userChoice > 0 && userChoice < 4){


        if(userChoice == 1){
            //inserir cliente
            //clientNumber ++
            //Digitar dados do cliente
            clientNumber++;
            insertClient(clientes, clientNumber);
        }else if(userChoice == 2){
            //remover cliente
            //clientNumber ==
            //buscar por cliente pelo CPF e desativar a conta
            removeClient(clientes, clientNumber);

        }else if(userChoice == 3){
            char searchCpf[11];
             printf("digite o cpf a ser procurado: ");
            gets(searchCpf);

            searchClient(clientes, searchCpf, clientNumber);
              //buscar cliente
            //procurar por CPF e retornar dados



        }
        //scanf("%d", &userChoice);
        userChoice = 3;

    }






    free(clientes);


    return 0;
}
