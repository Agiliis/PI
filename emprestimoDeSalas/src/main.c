#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <loginFuncs.h>
#include <reservasFuncs.h>
#include <limparTela.h>
#include "dbg.h"

void listar_opcoes(char *opcoes[], int numOpcoes){
    for(int i = 0; i < numOpcoes; i++){
        printf("%d. %s\n", i+1, opcoes[i]);
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

int main(){

    User usuario;

    retomar_usuarios();

    while(1){
        char *opcoes[] = {"Fazer login", "Cadastrar login", "Sair do programa"};
        
        int resposta = pedido_em_intervalo(opcoes, 3, "Digite a opcao");

        switch(resposta){
        case 1:
            usuario = tela_de_login();

            if(strcmp(usuario.email, "no_user") == 0) continue;
            break;
        case 2:
            cadastrar_login();
            
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
                //reservar_salas();
                continue;
            case 2:
                //remover_salas();
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