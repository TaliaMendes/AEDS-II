#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"

int main(){

    FILE *arqClientes, *arqDvds, *arqLocadora;
    TCliente *cliente;
    TFuncionario *funcionario;
    TDvd *dvd;
    TLocadora *locadora;


    if ((arqClientes = fopen("clientes.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqDvds = fopen("Dvds.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

     if ((arqLocadora = fopen("locadora.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    criarBaseCliente(arqClientes, 20);
    imprimirBaseCliente(arqClientes);
    criarBaseDvd(arqDvds, 20);
    printf("\n");

   alugaDvd(arqClientes, arqDvds, arqLocadora);

    printf("\n");
    imprimirDvdAlugado(arqLocadora, arqDvds, arqClientes);
}
