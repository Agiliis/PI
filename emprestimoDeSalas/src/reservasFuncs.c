#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <reservasFuncs.h>
#include <limparTela.h>
#include "dbg.h"

//Ultimo dia de cada mes
// ------------------------ J   F   M   A   M   J   J   A   S   O   N   D
const int ultimoDia[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

const char *horarios[] = {  "07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", 
                            "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", 
                            "20:30", "21:20", "22:10", "23:00"};

/****************************************
   
        ESTRUTURA
        - Mostra primeira das salas disponíveis
        - Pergunta se ele quer
            - Caso sim: chama funcao de reservar
            - Caso nao: chama listar_salas_disponiveis
        - Retorna a tela de confirmacao de sala

********************************************/

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

void ler_reservas(char *pathDoArq, Reserva *reservas, int *num_reservas){
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
        reservas[(*num_reservas)] = aux;
        (*num_reservas)++;
    }
    
    fclose(relacaoDasReservas);
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

void criar_reserva(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario) {
    int id_sala;
    int ok;

    listar_salas(salas, reservas, (*num_reservas), data, horario, "disponivel");

    ok = 1;
    do{
        char buffer[BUFSIZ];

        if(!ok){
            limpar_tela();
            listar_salas(salas, reservas, (*num_reservas), data, horario, "disponivel");
            puts("Opcao invalida!");
        }

        puts("Digite o ID da sala que deseja reservar");

        fgets(buffer, sizeof(buffer), stdin);

        char *aux = strtok(buffer, "\n");
        id_sala = strtol(buffer, NULL, 10);

        ok = id_sala != 0 && check_disponibilidade(reservas, (*num_reservas), id_sala, data, horario) == 1;
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

    fprintf(arquivo, "%d %s %s\n", id_sala, data, horario);
    fclose(arquivo);

    printf("Reserva da sala %d realizada com sucesso para a data %s no horário %s.\n", id_sala, data, horario);
}

void remover_reserva(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario){
    int id_sala;
    int ok;

    listar_salas(salas, reservas, (*num_reservas), data, horario, "indisponivel");

    ok = 1;
    do{
        char buffer[BUFSIZ];

        if(!ok){
            limpar_tela();
            listar_salas(salas, reservas, (*num_reservas), data, horario, "indisponivel");
            puts("Opcao invalida!");
        }

        puts("Digite o ID da sala que deseja remover");

        fgets(buffer, sizeof(buffer), stdin);

        char *aux = strtok(buffer, "\n");
        id_sala = strtol(buffer, NULL, 10);

        ok = id_sala != 0 && check_disponibilidade(reservas, (*num_reservas), id_sala, data, horario) == 0;
    }while(!ok);

    limpar_tela();

    Reserva aux[MAX_RESERVAS];
    for(int i = 0; i < (*num_reservas); i++){
        aux[i] = reservas[i];
    }
    
    memset(reservas, 0, sizeof(Reserva));

    for(int i = 0, j = 0; i < (*num_reservas); i++, j++){
        if(aux[i].id_sala == id_sala){
            j--;
            continue;
        }

        reservas[j] = aux[i];
    }

    (*num_reservas)--;

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas");
        return;
    }

    fprintf(arquivo, "ID_Sala Data Horario\n");
    for(int i = 1; i < (*num_reservas); i++){
        fprintf(arquivo, "%d %s %s\n", reservas[i].id_sala, reservas[i].data, reservas[i].horario);
    }
    
    fclose(arquivo);

    printf("Reserva da sala %d removida com sucesso para a data %s no horário %s.\n", id_sala, data, horario);
}

/**************************************/

void listar_horarios(){
    printf("Escolha um horario:\n");
    for (int i = 0; i < NUM_HORARIOS; i++) {
        printf("%d.\t%s\n", i + 1, horarios[i]);
    }
}

void listar_salas(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario, const char *modo) {
    int encontrou = 0;
    int modoCheck;

    if      (strcmp(modo, "disponivel")     == 0) modoCheck = 1;
    else if (strcmp(modo, "indisponivel")   == 0) modoCheck = 0;
    else{
        perror("Argumento para 'modo' invalido");
        exit(1);
    }

    printf("Salas %s\bis para a data %s no horario %s:\n", modo, data, horario);

    for (int i = 1; i < MAX_SALAS; i++) {
        if (check_disponibilidade(reservas, num_reservas, salas[i].id, data, horario) == modoCheck) {
            printf("ID: %d\t| Nome: %s\t| Tipo: %s\t| Bloco: %s\n",
                   salas[i].id, salas[i].nome, salas[i].tipo, salas[i].bloco);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma sala %s para o horario solicitado.\n", modo);
    }
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

int check_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario) {
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
