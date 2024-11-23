#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define ARRAY_SZ(x) (sizeof(x) / sizeof(x[0]))

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

void listar_opcoes(char *opcoes[], int numOpcoes){
    for(int i = 0; i < numOpcoes; i++){
        printf("[%d] %s\n", i+1, opcoes[i]);
    }
}

void pedido_em_intervalo(char *opcoes[], int numOpcoes, char buffer[], int buffSz, char *pedido, char *aviso){
    int ok;

    listar_opcoes(opcoes, numOpcoes);

    ok = 1;
    do{
        if(!ok){
            printf(CONS_RESET); printf(CONS_CLEAR);
            puts(aviso);
            listar_opcoes(opcoes, numOpcoes);
        }

        printf("%s", pedido);

        fgets(buffer, buffSz, stdin);

        int aux = atoi(buffer);
        ok = (1 <= aux && aux <= numOpcoes);

    }while(!ok);

    printf(CONS_RESET); printf(CONS_CLEAR);
}

int main(){
    char op[3];
    char *opcoes[] = {"Fazer login", "Cadastrar login"};
    
    pedido_em_intervalo(opcoes, 2, op, 3, "Digite a opcao: ", "Opcao invalida!");

    //printf("O que deseja fazer?\n");

    
    //pedido_em_intervalo("[1] Reservar salas \n[2] Remover reservas", op, 3, "Digite a opcao: ", 1, 2, "Opcao invalida!");

}