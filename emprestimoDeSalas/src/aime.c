#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbg.h"

#define MAX_SALAS 42
#define MAX_RESERVAS 100
#define NUM_HORARIOS (sizeof(horarios) / sizeof(horarios[0]))

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

typedef struct {
    int     id;
    char    nome[20];
    char    tipo[50];
    char    bloco[50];
} Sala;

typedef struct {
    int     id_sala;
    char    data[12];
    char    horario[6];
} Reserva;

//Ultimo dia de cada mes
// ------------------------ J   F   M   A   M   J   J   A   S   O   N   D
const int ultimoDia[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

const char *horarios[] = {"07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", "20:30", "21:20", "22:10", "23:00"};

int diaAtual, mesAtual, anoAtual;

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

#warning universalizar funcao
void limpar_tela(){
    #if DBG == 0
    printf(CONS_RESET); printf(CONS_CLEAR);
    #endif
}

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);
int check_data(char data[]);
void listar_salas_disponiveis(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario);
void escolher_horario(char *horario_escolhido);
void ler_relacao_das_salas(char *localDoArquivoCsv, Sala *salas);
void escolher_data(char data[]);

#warning otimizar
void reservar_sala(Reserva reservas[], int *num_reservas, const char *nome_arquivo, int id_sala, char *data, char *horario);


int main() {

    time_t lt = time(NULL);
    struct tm *currTime = localtime(&lt);
    diaAtual = (*currTime).tm_mday;
    mesAtual = (*currTime).tm_mon+1;
    anoAtual = (*currTime).tm_year+1900;

    ler_relacao_das_salas("../res/salas.csv", salas);

    /*
        ESTRUTURA
        - Mostra primeira das salas disponíveis
        - Pergunta se ele quer
            - Caso sim: chama funcao de reservar
            - Caso nao: chama listar_salas_disponiveis
        - Retorna a tela de confirmacao de sala
    */

    char continuar = 'S';
    while (continuar == 'S' || continuar == 's') {
        char data[12];
        escolher_data(data);

        char horario[6];
        escolher_horario(horario);

        listar_salas_disponiveis(salas, reservas, num_reservas, data, horario);
        
        #warning realocar bloco pra funcao
        int id_sala;
        printf("Digite o ID da sala que deseja reservar: ");
        scanf("%d", &id_sala);
        getchar();
        reservar_sala(reservas, &num_reservas, "reservas.txt", id_sala, data, horario);

        #warning sanitizar leitura
        printf("Deseja reservar outra sala? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
    }

    printf("Obrigado por usar o sistema de reservas!\n");

    return 0;
}

void reservar_sala(Reserva reservas[], int *num_reservas, const char *nome_arquivo, int id_sala, char *data, char *horario) {
    if (!verificar_disponibilidade(reservas, *num_reservas, id_sala, data, horario)) {
        printf("Erro: Sala já reservada para a data %s no horário %s.\n", data, horario);
        return;
    }


    Reserva nova_reserva = {id_sala, "", ""};
    strcpy(nova_reserva.data, data);
    strcpy(nova_reserva.horario, horario);


    reservas[*num_reservas] = nova_reserva;
    (*num_reservas)++;


    FILE *arquivo = fopen(nome_arquivo, "a");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas");
        return;
    }

    fprintf(arquivo, "%d %s %s\n", id_sala, data, horario);
    fclose(arquivo);

    printf("Reserva da sala %d realizada com sucesso para a data %s no horário %s.\n", id_sala, data, horario);
}

void listar_horarios(){
    printf("Escolha um horario:\n");
    for (int i = 0; i < NUM_HORARIOS; i++) {
        printf("%d.\t%s\n", i + 1, horarios[i]);
    }
}

void escolher_data(char data[]){
    int ok;

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            printf("Data invalida\n");
        }

        printf("Digite a data (DD-MM-AAAA): ");

        fgets(data, 12, stdin);

        dbgs(data)

        ok = check_data(data);

    }while(!ok);

    limpar_tela();
}

int check_data(char data[]){
    int dia, mes, ano;
    int ok = 1;
    char *token;

    // token = malloc(12);
    // strcpy(token, data);

    #warning resolver esse tal de segfault

    token = strtok(data, "-");
    dia = strtol(token, NULL, 10); 
    
    token = strtok(NULL, "-");
    mes = strtol(token, NULL, 10); 
    
    token = strtok(NULL, "-");
    ano = strtol(token, NULL, 10);

    dbgi(dia) dbgi(mes) dbgi(ano)

    int limInf = 1;
    if(mes == mesAtual) limInf = diaAtual;

    if(ano != anoAtual) ok = 0;
    if(mes < mesAtual || 12 < mes) ok = 0;
    if(dia < limInf || ultimoDia[mes] < dia) ok = 0;

    return ok;
}

void ler_relacao_das_salas(char *localDoArquivoCsv, Sala *salas){
    FILE *relacaoDasSalas = fopen(localDoArquivoCsv, "r");

    if(relacaoDasSalas == NULL){
        puts("Erro ao abrir arquivo com salas");
        exit(1);
    }

    for(int i = 0; i < MAX_SALAS; i++){
        Sala aux;

        aux.id = i;
        fscanf(relacaoDasSalas, "%s %s %s", aux.nome, aux.tipo, aux.bloco);

        salas[i] = aux;
    }
    
    fclose(relacaoDasSalas);
}

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario) {
    for (int i = 0; i < num_reservas; i++) {
        if (reservas[i].id_sala == id_sala &&
            strcmp(reservas[i].data, data) == 0 &&
            strcmp(reservas[i].horario, horario) == 0) {
            return 0;
        }
    }

    return 1;
}

void listar_salas_disponiveis(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario) {
    int encontrou_disponivel = 0;
    
    printf("Salas disponiveis para a data %s no horario %s:\n", data, horario);

    for (int i = 1; i < MAX_SALAS; i++) {
        if (verificar_disponibilidade(reservas, num_reservas, salas[i].id, data, horario) == 1) {
            printf("ID: %d\t| Nome: %s\t| Tipo: %s\t| Bloco: %s\n",
                   salas[i].id, salas[i].nome, salas[i].tipo, salas[i].bloco);
            encontrou_disponivel = 1;
        }
    }

    if (!encontrou_disponivel) {
        printf("Nenhuma sala disponivel para o horario solicitado.\n");
    }
}

void escolher_horario(char *horario_escolhido) {
    char escolha[4];
    int escolhaNum;
    int ok;

    listar_horarios();

    ok = 1;
    do {
        if(!ok){
            limpar_tela();
            listar_horarios();
            printf("Opcao invalida! (Digite o numero a esquerda do horario)\n");
        }

        printf("Digite o numero do horario desejado: ");
        
        fgets(escolha, 4, stdin);
        //scanf("%d", &escolha);

        escolhaNum = atoi(escolha);
        ok = (1 <= escolhaNum && escolhaNum <= NUM_HORARIOS);
    } while (!ok);

    limpar_tela();

    strcpy(horario_escolhido, horarios[escolhaNum - 1]);
}
