#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbg.h"

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

#if _WIN32
#include <windows.h>

// Credito: https://cplusplus.com/articles/4z18T05o/
void limpar_tela()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }
#elif unix
void limpar_tela(){
    #if DBG == 0
    printf(CONS_RESET); printf(CONS_CLEAR);
    #endif
}
#endif

#define MAX_SALAS 42
#define MAX_RESERVAS 100
#define NUM_HORARIOS (sizeof(horarios) / sizeof(horarios[0]))

#warning refactorizar struct de reserva em struct de salas (se der tempo eu tento)

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

const char *horarios[] = {  "07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", 
                            "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", 
                            "20:30", "21:20", "22:10", "23:00"};

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

int verificar_disponibilidade(Reserva reservas[], int id_sala, char *data, char *horario);
int check_data(char data[]);
void listar_salas_disponiveis(Sala salas[], Reserva reservas[], char *data, char *horario);
void escolher_horario(char *horario_escolhido);
void ler_relacao_das_salas(char *pathDoArq, Sala *salas);
void ler_reservas(char *pathDoArq, Reserva *reservas);
void escolher_data(char data[]);
void reservar_sala(Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);


int main() {

    ler_relacao_das_salas("../res/salas.csv", salas);
    ler_reservas("../res/reservas.csv", reservas);

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
        
        reservar_sala(reservas, &num_reservas, "../res/reservas.csv", data, horario);

        puts("Deseja reservar outra sala? (S/N)");
        scanf(" %c", &continuar);
        getchar(); // bruxaria pra data nao ler '\n'

        limpar_tela();
    }

    printf("Obrigado por usar o sistema de reservas!\n");

    return 0;
}

void reservar_sala(Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario) {
    int id_sala;
    int ok;

    listar_salas_disponiveis(salas, reservas, data, horario);

    ok = 1;
    do{
        char buffer[BUFSIZ];

        if(!ok){
            limpar_tela();
            listar_salas_disponiveis(salas, reservas, data, horario);
            puts("Opcao invalida!");
        }

        puts("Digite o ID da sala que deseja reservar");

        fgets(buffer, sizeof(buffer), stdin);

        char *aux = strtok(buffer, "\n");
        id_sala = strtol(buffer, NULL, 10);

        ok = id_sala != 0 && verificar_disponibilidade(reservas, id_sala, data, horario);
    }while(!ok);

    limpar_tela();

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

    fprintf(arquivo, "\n%d %s %s", id_sala, data, horario);
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
        char *aux = strtok(data, "\n");
        strcpy(data, aux);

        //dbgs(data)

        ok = check_data(data);

    }while(!ok);

    limpar_tela();
}

int check_data(char data[]){
    int dia, mes, ano;
    int ok = 1;
    char *token;

    // time.h: settar a data atual
    time_t lt = time(NULL);
    struct tm *currTime = localtime(&lt);
    int diaAtual = (*currTime).tm_mday;
    int mesAtual = (*currTime).tm_mon+1;
    int anoAtual = (*currTime).tm_year+1900;

    token = malloc(12);
    strcpy(token, data);

    token = strtok(token, "-");
    if(token == NULL) return 0; // checagem pra o primeiro caracter (ou o unico n sei) ser '-'
    dia = strtol(token, NULL, 10); 
    
    token = strtok(NULL, "-");
    if(token == NULL) return 0; // checagem pra se não contem '-' na data
    mes = strtol(token, NULL, 10); 
    
    token = strtok(NULL, "-");
    if(token == NULL) return 0; // checagem pra se contem so 1 '-'
    ano = strtol(token, NULL, 10);

    //dbgi(dia) dbgi(mes) dbgi(ano)

    int limInf = 1;
    if(mes == mesAtual) limInf = diaAtual;

    if(ano != anoAtual) ok = 0;
    if(mes < mesAtual || 12 < mes) ok = 0;
    if(dia < limInf || ultimoDia[mes] < dia) ok = 0;

    return ok;
}

void ler_relacao_das_salas(char *pathDoArq, Sala *salas){
    FILE *relacaoDasSalas = fopen(pathDoArq, "r");

    if(relacaoDasSalas == NULL){
        perror("Erro ao abrir arquivo com salas");
        puts("Aperte qualquer tecla para fechar...");
        getchar();
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

void ler_reservas(char *pathDoArq, Reserva *reservas){
    FILE *relacaoDasReservas = fopen(pathDoArq, "r");

    if(relacaoDasReservas == NULL){
        puts("Erro ao abrir arquivo com reservas");
        puts("Aperte qualquer tecla para fechar...");
        getchar();
        exit(1);
    }

    Reserva aux;
    char id[20];
    while(fscanf(relacaoDasReservas, "%s %s %s", id, aux.data, aux.horario) == 3){
        aux.id_sala = strtol(id, NULL, 10);
        reservas[num_reservas] = aux;
        num_reservas++;
    }
    
    fclose(relacaoDasReservas);
}

int verificar_disponibilidade(Reserva reservas[], int id_sala, char *data, char *horario) {
    // dbgi(num_reservas)
    // dbgi(id_sala)
    
    for (int i = 0; i < num_reservas; i++) {
        if (reservas[i].id_sala == id_sala &&
            strcmp(reservas[i].data, data) == 0 &&
            strcmp(reservas[i].horario, horario) == 0) {
            return 0;
        }
    }

    return 1;
}

void listar_salas_disponiveis(Sala salas[], Reserva reservas[], char *data, char *horario) {
    int encontrou_disponivel = 0;
    
    printf("Salas disponiveis para a data %s no horario %s:\n", data, horario);

    for (int i = 1; i < MAX_SALAS; i++) {
        if (verificar_disponibilidade(reservas, salas[i].id, data, horario) == 1) {
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
