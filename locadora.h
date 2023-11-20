#ifndef LOCADORA_H_INCLUDED
#define LOCADORA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int idC;
    char nomeC[100];
    char dataNascimentoC[50];
    char cpfC[50];
    char telefoneC[50];
}TCliente;

typedef struct dvd_est {
    int id_dvd;
    char nome_dvd[100];
    char genero[100];
    int emprestimo; // 0 disponivel , 1 emprestado
} TDvd;

typedef struct{
    int id_locacao;
    int id_dvd;
    int id_cliente;
}TLocadora;

int tamanhoRegistroLocadora();

void shuffle(int *vet,int MAX,int MIN);

int tamanho_arquivo(FILE *arq);


//Cliente
TCliente *criarCliente(int idC ,char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC);

void salvarCliente(TCliente *cliente, FILE *arq);

TCliente *lerCliente(FILE *arq);

void imprimeCliente(TCliente *cliente);

void criarBaseCliente(FILE *arq, int tam);

void imprimirBaseCliente(FILE *arq);

TCliente *buscaSequencialCliente(int chave, FILE *arq, const char *nomeArquivoLog);

TCliente *buscabinariaCliente(int chave, FILE *arqCliente);

//Dvd
TDvd *criarDvd(int id_dvd, char *nome_dvd, char *genero, int emprestimo);

void salvarDvd(TDvd *dvd, FILE *arq);

TDvd *lerDvd(FILE *arq);

void imprimeDvd(TDvd *dvd);

void criarBaseDvd(FILE *arq, int tam);

void imprimirBaseDvd(FILE *arq);

TDvd *buscaSequencialDvds(int chave, FILE *arq, const char *nomeArquivoLog);

TDvd *buscabinariaDvds(int chave, FILE *arqDvds);



//Locadora
TLocadora *lerRegistrosLocadora(FILE *arq);

TLocadora *criarLocadora(int id_locacao, int id_dvd, int id_cliente);

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora);

void imprimeLocadora(TLocadora *locadora);

void criarBaseLocadora(FILE *arqLocadora, int tam);

void imprimirBaseLocadora(FILE *arqLocadora);

TLocadora *buscaBinariaLocacao(int chave, FILE *in, int inicio, int fim);

//Operacoes

void dvdsDisponiveis(FILE *arq);

void alugaDvd(FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora);

void imprimirDvdAlugado(FILE *arq, FILE *arqD, FILE *aqrC);

int excluiDvd(int chave, FILE *arqDvds);

int excluiCliente(int chave, FILE *arqClientes);


#endif
