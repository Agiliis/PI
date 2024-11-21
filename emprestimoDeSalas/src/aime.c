#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    char    data[11];
    char    horario[6];
} Reserva;

//Ultimo dia de cada mes
// ------------------------ J   F   M   A   M   J   J   A   S   O   N   D
const int ultimoDia[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

const char *horarios[] = {"07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", "20:30", "21:20", "22:10", "23:00"};

#warning integrar variaveis de data com calendario
const int   diaAtual = 1,
            mesAtual = 1,
            anoAtual = 2024;

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);
int check_data(char data[]);
void listar_salas_disponiveis(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario);
void escolher_horario(char *horario_escolhido);
void ler_relacao_das_salas(char *localDoArquivoCsv, Sala *salas);
void escolher_data(char data[]);

int main() {

    #warning ver caso de ser windows
    ler_relacao_das_salas("../res/salas.csv", salas);

    char data[12];
    escolher_data(data);

    printf(CONS_RESET); printf(CONS_CLEAR);

    char horario[6];
    escolher_horario(horario);

    #warning necessario modificar se for seguir com o fluxo de "mostrar primeira sala disponível"
    listar_salas_disponiveis(salas, reservas, num_reservas, data, horario);

    #warning add funcao de reservar salas (aime ta fazendo)

    return 0;
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
            printf(CONS_RESET); printf(CONS_CLEAR);
            printf("Data invalida\n");
        }

        printf("Digite a data (DD-MM-AAAA): ");

        fgets(data, 12, stdin);

        ok = check_data(data);

    }while(!ok);
}

int check_data(char data[]){
    int dia, mes, ano;
    int ok = 1;
    char *token;
    
    token = strtok(data, "-");
    dia = atoi(token); 
    
    token = strtok(NULL, "-");
    mes = atoi(token); 
    
    token = strtok(NULL, "-");
    ano = atoi(token);

    if( mes < mesAtual || 12 < mes ||
        dia < diaAtual || ultimoDia[mes] < dia ||
        ano < anoAtual || anoAtual+1 < ano) ok = 0;

    return ok;
}

void ler_relacao_das_salas(char *localDoArquivoCsv, Sala *salas){
    #warning add wrapper de seguranca
    FILE *relacaoDasSalas = fopen(localDoArquivoCsv, "r");

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
            printf(CONS_CLEAR); printf(CONS_RESET);
            listar_horarios();
            printf("Opcao invalida! (Digite o numero a esquerda do horario)\n");
        }

        printf("Digite o numero do horario desejado: ");
        
        fgets(escolha, 4, stdin);
        //scanf("%d", &escolha);

        escolhaNum = atoi(escolha);
        ok = (1 <= escolhaNum && escolhaNum <= NUM_HORARIOS);
    } while (!ok);

    printf(CONS_CLEAR); printf(CONS_RESET);

    strcpy(horario_escolhido, horarios[escolhaNum - 1]);
}
