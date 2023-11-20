#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "locadora.h"

void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

//Cliente
TCliente *criarCliente(int idC, char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC){

    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

    if(cliente) memset(cliente, 0, sizeof(cliente)); //inicializa espaco de memoria com ZEROS
        cliente->idC = idC;  //copia os valores para os seus respectivos campos
        strcpy(cliente->nomeC, nomeC);
        strcpy(cliente->dataNascimentoC, dataNascimentoC); //strcpy (copia uma string para outra)
        strcpy(cliente->cpfC, cpfC);
        strcpy(cliente->telefoneC, telefoneC);

        return cliente;
}

void salvarCliente(TCliente *cliente, FILE *arq){ //Salva os dados na posicao atual do cursor
    fwrite(&cliente->idC, sizeof(int), 1, arq); //fwrite(Salvar dados no arquivo).
    fwrite(cliente->nomeC, sizeof(char), sizeof(cliente->nomeC), arq);
    fwrite(cliente->dataNascimentoC, sizeof(char), sizeof(cliente->dataNascimentoC), arq);
    fwrite(cliente->cpfC, sizeof(char), sizeof(cliente->cpfC), arq);
    fwrite(cliente->telefoneC, sizeof(char), sizeof(cliente->telefoneC), arq);
}

TCliente *lerCliente(FILE *arq){ // ler dados do arquivo na posiçao atual do cursor
     TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

     if (0 >= fread(&cliente->idC, sizeof(int), 1, arq)) { // Se o numero de unidades lidas for menor do que 0, retorna null , pois o arquivo esta vazio
        free(cliente);
        return NULL;
    }
    fread(cliente->nomeC, sizeof(char), sizeof(cliente->nomeC), arq);
    fread(cliente->dataNascimentoC, sizeof(char), sizeof(cliente->dataNascimentoC), arq);
    fread(cliente->cpfC, sizeof(char), sizeof(cliente->cpfC), arq);
    fread(cliente->telefoneC, sizeof(char), sizeof(cliente->telefoneC), arq);

    return cliente;

}

TCliente *buscaSequencialCliente(int chave, FILE *arq, const char *nomeArquivoLog) {  //Busca sequencial para o arquivo de clientes
    TCliente *cliente;
    int achou = 0;
    clock_t inicio, fim;
    double tempoGasto;
    int contComparacao = 0;
                                                // o nome do arquivo e passado como parametro
    FILE *logFile = fopen(nomeArquivoLog, "a"); // Abre o arquivo de log em modo de adicao de novos dados.
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    inicio = clock(); // inicio da funcao que conta o tempo para a busca da chave desejada em milisegundos
    rewind(arq); // volta o cursor para o inicio do arquivo
    while ((cliente = lerCliente(arq)) != NULL) {
        contComparacao++; // enquanto nao e encontrada a chave dejada, e acrescentado o valor 1 a variavel

        if (cliente->idC == chave) { //faz a comparação da chave desejada
            achou = 1;
            break;
        }

        free(cliente); // Libera o cliente se não for o procurado
    }
    fim = clock();

    tempoGasto = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC; // calcula o tempo gasto para encontrar a chave. CLOCKS_PER_SEC: responsável por armazenar a quantidade de pulsos por segundo do processador da máquina.

    // Escrevendo no arquivo de log
    fprintf(logFile, "Busca pela chave %d: Comparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (achou == 1) {
        return cliente;
    } else {
        printf("Cliente não encontrado\n");
    }

    printf("Tempo gasto: %f milissegundos\n", tempoGasto);

    return NULL;
}


void imprimeCliente(TCliente *cliente){
    printf("\n CLIENTE \n");
    printf("\nID do cliente: ");
    printf("%d", cliente->idC);
    printf("\nNome do Cliente: ");
    printf("%s", cliente->nomeC);
    printf("\nData de nascimento do cliente: ");
    printf("%s", cliente->dataNascimentoC);
    printf("\nCPF do cliente: ");
    printf("%s", cliente->cpfC);
    printf("\nTelefone do cliente: ");
    printf("%s", cliente->telefoneC);
    printf("\n");
}

void criarBaseCliente(FILE *arq, int tam){
char nomeCliente[50];
int vet[tam];
    TCliente *cliente;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        sprintf(nomeCliente, "Cliente %d " ,i+1);
        cliente = criarCliente(vet[i], nomeCliente, "09/03/200", "15896375214","23254153");
        salvarCliente(cliente, arq);
    }

    free(cliente);
}

void imprimirBaseCliente(FILE *arq){
rewind(arq);
    TCliente *cliente;

    while ((cliente = lerCliente(arq)) != NULL)
        imprimeCliente(cliente);

    free(cliente);
}

//Dvd
TDvd *criarDvd(int id_dvd, char *nome_dvd, char *genero, int emprestimo){

    TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

    if(dvd) memset(dvd, 0, sizeof(dvd));
        dvd->id_dvd = id_dvd;
        strcpy(dvd->nome_dvd, nome_dvd);
        strcpy(dvd->genero, genero);
        dvd->emprestimo = emprestimo;

        return dvd;
}

void salvarDvd(TDvd *dvd, FILE *arq){
     fwrite(&dvd->id_dvd, sizeof(int), 1, arq);
     fwrite(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq);
     fwrite(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
     fwrite(&dvd->emprestimo, sizeof(int), 1, arq);
}

TDvd *lerDvd(FILE *arq){
  TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

     if (0 >= fread(&dvd->id_dvd, sizeof(int), 1, arq)) {
        free(dvd);
        return NULL;
    }
    fread(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq);
    fread(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
    fread(&dvd->emprestimo, sizeof(int), 1, arq);

    return dvd;
}

void imprimeDvd(TDvd *dvd){
    printf("\n DVD \n");
    printf("\nID do dvd: ");
    printf("%d", dvd->id_dvd);
    printf("\nNome do dvd: ");
    printf("%s", dvd->nome_dvd);
    printf("\nGenero do dvd: ");
    printf("%s", dvd->genero);
    printf("\nSituacao do emprestimo: ");
    printf("%d", dvd->emprestimo);
    printf("\n");
}

void criarBaseDvd(FILE *arq, int tam){
int vet[tam];
    TDvd *Dvd;
char nomeFilme[50];

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        sprintf(nomeFilme, "Filme %d " ,i+1);
        Dvd = criarDvd(vet[i], nomeFilme, "Acao", 0);
        salvarDvd(Dvd, arq);
    }

    free(Dvd);
}

void imprimirBaseDvd(FILE *arq){
rewind(arq);
    TDvd *Dvd;

    while ((Dvd = lerDvd(arq)) != NULL)
        imprimeDvd(Dvd);

    free(Dvd);
}

TDvd *buscaSequencialDvds(int chave, FILE *arq, const char *nomeArquivoLog) {
    TDvd *dvd;
    int achou = 0;
    clock_t inicio, fim;
    double tempoGasto;
    int contComparacao = 0;

    FILE *logFile = fopen(nomeArquivoLog, "a");
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    inicio = clock();
    rewind(arq);
    while ((dvd = lerDvd(arq)) != NULL) {
        contComparacao++;

        if (dvd->id_dvd == chave) {
            achou = 1;
            break;
        }

        free(dvd);
    }
    fim = clock();

    tempoGasto = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;

    // Escrevendo no arquivo de log
    fprintf(logFile, "Busca pelo DVD com chave %d: Comparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (achou == 1) {
        return dvd;
    }

    return NULL;
}

//Locadora
TLocadora *criarLocadora(int id_locacao, int id_dvd, int id_cliente){

    TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

    if(locadora) memset(locadora, 0, sizeof(locadora));
        locadora->id_locacao = id_locacao;
        locadora->id_dvd = id_dvd;
        locadora->id_cliente = id_cliente;

        return locadora;
}

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora){
    fwrite(&locadora->id_dvd, sizeof(int), 1, arqLocadora);
    fwrite(&locadora->id_cliente, sizeof(int), 1, arqLocadora);
}

TLocadora *lerRegistrosLocadora(FILE *arqLocadora){
  TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

     if (0 >= fread(&locadora->id_dvd, sizeof(int), 1, arqLocadora)) {
        free(locadora);
        return NULL;
    }

    fread(&locadora->id_cliente, sizeof(int), 1, arqLocadora);

    return locadora;
}

void imprimeLocadora(TLocadora *locadora){
    printf("\nID do dvd: ");
    printf("%d", locadora->id_dvd);
    printf("\nCliente: ");
    printf("%d", locadora->id_cliente);
    printf("\n");
}

void criarBaseLocadora(FILE *arqLocadora, int tam){
int vet[tam];
    TLocadora *locadora;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        locadora = criarLocadora(i,i++,i+2);
        salvarLocadora(locadora, arqLocadora);
    }

    free(locadora);
}

void imprimirBaseLocadora(FILE *arqLocadora){
    rewind(arqLocadora);
    TLocadora *locadora;

    while ((locadora = lerRegistrosLocadora(arqLocadora)) != NULL)
        imprimeLocadora(locadora);

    free(locadora);
}


TLocadora *buscaBinariaLocacao(int chave, FILE *in, int inicio, int fim) {

        TLocadora *locadora = NULL;
        int cod = -1;

        while (inicio <= fim && cod != chave) {

            int meio = trunc((inicio + fim) / 2);
            //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
            fseek(in, (meio -1) * tamanhoRegistroLocadora(), SEEK_SET);
            locadora = lerRegistrosLocadora(in);
            cod = locadora->id_locacao;

            if (locadora) {
                if (cod > chave) {
                    fim = meio - 1;
                } else {
                    inicio = meio + 1;
                }
            }
        }

        if (cod == chave) {
            return locadora;
        }
        else return NULL;
}


//Operacoes
void dvdsDisponiveis(FILE *arq){

    TDvd *dvd;
    // Reseta o ponteito e volta ao inicio do arquivo
    rewind(arq);
    while ((dvd = lerDvd(arq)) != NULL){

        if(dvd->emprestimo == 0 ){
            imprimeDvd(dvd);
        }

    free(dvd);
    }

}

void alugaDvd(FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora) {
    int res;
    int idCliente, idDvd;
    TCliente *cliente;
    TLocadora *locadora;
    TDvd *dvd;

    if ((arqClientes = fopen("clientes.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqDvds = fopen("Dvds.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    do{
    imprimirBaseCliente(arqClientes);
    printf("---------------------------------------------------------\n");
    printf("Digite o id do cliente que deseja alugar o DVD\n");
    scanf("%d", &idCliente);

    cliente = buscaSequencialCliente(idCliente, arqClientes, "clientes-log.txt");

    dvdsDisponiveis(arqDvds);

    printf("---------------------------------------------------------\n");
    printf("Digite o id do DVD\n");
    scanf("%d", &idDvd);

    dvd = buscaSequencialDvds(idDvd, arqDvds, "buscaDvds-log.txt");

    if(dvd == NULL){
        printf("Dvd nao encontrado");
        exit(1);
    }
        dvd->emprestimo = 1;
        fseek(arqDvds, -sizeof(TDvd), SEEK_CUR);
        salvarDvd(dvd , arqDvds);
        locadora = criarLocadora(tamanhoRegistroLocadora()+1, idDvd, idCliente);
        salvarLocadora(locadora, arqLocadora);

        if(dvd->emprestimo == 1){
            printf("\nNAO FOI POSSIVEL REALIZAR O EMPRESTIMO, O DVD JA ESTA ALUGADO\n");

        }

    printf("\n*******************************************************\n");
    printf("DIGITE: 1 PARA ALUGAR MAIS FILMES \nDIGITE: 0 PARA SAIR ");
    scanf("%d",&res);

    }while(res != 0);

        fclose(arqClientes);
        fclose(arqDvds);
        free(cliente);
        free(dvd);

}


void imprimirDvdAlugado(FILE *arq, FILE *arqD, FILE *arqC){
rewind(arq);
    TLocadora *locadora;
    TDvd *dvd;
    TCliente *cliente;

    while ((locadora = lerRegistrosLocadora(arq)) != NULL){
        printf("***************DVD'S ALUGADOS*****************");
        dvd = buscaSequencialDvds(locadora->id_dvd, arqD, "buscaDvds-log.txt");
        imprimeDvd(dvd);

        cliente = buscaSequencialCliente(locadora->id_cliente, arqC, "clientes-log.txt");
        imprimeCliente(cliente);
    }
    free(locadora);
    free(cliente);
}

int excluiDvd(int chave, FILE *arqDvds) {
    TDvd *dvd;
    int encontrado = 0;

    // Abre o arquivo original para leitura e gravação binária
    if ((arqDvds = fopen("Dvds.dat", "r+")) == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Procura o registro pelo Id

    while ((dvd = lerDvd(arqDvds)) != NULL) {
        if (dvd->id_dvd == chave) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // Move o ponteiro do arquivo de volta para o início do registro
        fseek(arqDvds, -sizeof(TDvd), SEEK_CUR);

        // Preenche o registro com dados vazios
        TDvd dvdVazio;
        dvdVazio.id_dvd = 0;
        strcpy(dvdVazio.nome_dvd, "");
        strcpy(dvdVazio.genero, "");
        dvdVazio.emprestimo = 0;

        fwrite(&dvdVazio, sizeof(TDvd), 1, arqDvds);

        printf("Dvd excluido com sucesso.\n");
    } else {
        printf("Dvd nao encontrado.\n");
    }

    fclose(arqDvds); // Fecha o arquivo
    return 0; // Indica sucesso
}
int tamanhoRegistroLocadora() {
        return sizeof(int)  //id_transacao
               + sizeof(int) //id_dvd
               + sizeof(int); //id_cliente
}

int tamanho_arquivo(FILE *arq) {
        fseek(arq, 0, SEEK_END);
        int tam = trunc(ftell(arq) / tamanhoRegistroLocadora());
        return tam;
}


int excluiCliente(int chave, FILE *arqClientes) {
    TCliente *cliente;
    int encontrado = 0;

    // Procura o registro pelo Id
    while ((cliente = lerCliente(arqClientes)) != NULL) {
            cliente = buscaSequencialCliente(chave, arqClientes,"clientes-log.txt");
        if (cliente->idC == chave) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 1) {
        // Move o ponteiro do arquivo para a posição correta
        fseek(arqClientes, -sizeof(TCliente), SEEK_CUR);

        // Preenche o registro com dados vazios
        TCliente clienteVazio;
        clienteVazio.idC = 0;
        strcpy(clienteVazio.nomeC, "");
        strcpy(clienteVazio.cpfC, "");
        strcpy(clienteVazio.dataNascimentoC, "");
        strcpy(clienteVazio.telefoneC, "");

        fwrite(&clienteVazio, sizeof(TCliente), 1, arqClientes);

        printf("Cliente excluido com sucesso.\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }

    return 0; // Indica sucesso
}



