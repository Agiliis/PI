#include <stdio.h>
#include <stdlib.h>
#include <reservasFuncs.h>
#include <string.h>
#include <limparTela.h>
#include "dbg.h"

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

void remover_reserva(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);

int main(){

    ler_relacao_das_salas("../res/salas.csv", salas);
    ler_reservas("../res/reservas.csv", reservas, &num_reservas);

    while(1){
        char data[12];
        escolher_data(data);

        char horario[6];
        escolher_horario(horario);

        remover_reserva(salas, reservas, &num_reservas, "../res/reservas.csv", data, horario);
    }
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