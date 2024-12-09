#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <loginFuncs.h>
#include <reservasFuncs.h>
#include <limparTela.h>
#include "dbg.h"

int pedido_em_intervalo(char *opcoes[], int numOpcoes, char *pedido);
void listar_opcoes(char *opcoes[], int numOpcoes);

int main(){

    User usuario;
    User usuarios[USER_MAX_NUM];
    int userCnt = 0;   

    Sala salas[MAX_SALAS];
    Reserva reservas[MAX_RESERVAS];
    int num_reservas = 0;

    char data[12];
    char horario[6];

    ler_base_de_usuarios
    ("../res/userBase.txt", usuarios, &userCnt);
    
    ler_relacao_das_salas   
    ("../res/salas.csv", salas);
    
    ler_reservas            
    ("../res/reservas.csv", reservas, &num_reservas);

    while(1){
        char *opcoes[] = {"Fazer login", "Cadastrar login", "Sair do programa"};
        
        int resposta = pedido_em_intervalo(opcoes, 3, "Digite a opcao");

        switch(resposta){
        case 1:
            usuario = tela_de_login(usuarios, userCnt);

            if(strcmp(usuario.email, "no_user") == 0) continue;
            break;
        case 2:
            cadastrar_login(usuarios, &userCnt);
            
            continue;
        case 3:
            puts("adios");
            exit(0);
        }

        // Usuario logado

        while(1){
            printf("Logado como %s\n\n", usuario.email);

            char *opcoes[] = {"Reservar sala", "Remover reservas", "Sair do usuario"};

            int resposta = pedido_em_intervalo(opcoes, 3, "O que deseja fazer?");  

            switch(resposta){
            case 1:
                escolher_data(data);

                escolher_horario(horario);
                
                criar_reserva(salas, reservas, &num_reservas, "../res/reservas.csv", data, horario);

                continue;
            case 2:
                escolher_data(data);

                escolher_horario(horario);
                
                remover_reserva(salas, reservas, &num_reservas, "../res/reservas.csv", data, horario);
                
                continue;
            case 3:
                break;
            }  

            // sair do usuario
            break;
        }

        limpar_tela();
    }

}

int pedido_em_intervalo(char *opcoes[], int numOpcoes, char *pedido){
    int ok;
    char buffer[BUFSIZ];
    int resposta;

    listar_opcoes(opcoes, numOpcoes);

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts("Opcao invalida!");
            listar_opcoes(opcoes, numOpcoes);
        }

        printf("%s\n", pedido);

        fgets(buffer, sizeof(buffer), stdin);

        resposta = atoi(buffer);
        ok = (1 <= resposta && resposta <= numOpcoes);

    }while(!ok);

    limpar_tela();

    return resposta;
}

void listar_opcoes(char *opcoes[], int numOpcoes){
    for(int i = 0; i < numOpcoes; i++){
        printf("%d. %s\n", i+1, opcoes[i]);
    }
}
