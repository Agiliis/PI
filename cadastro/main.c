#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastroFuncs.c"

user usuarios[MAXN_USER];
int nUsuariosAtual = 0;

user *usuariosNewPtr = usuarios; 

int main(){

    while(1){
        printf("%s", saudacao1);
        
        char opcao;
        scanf(" %c", &opcao);
            
        switch(opcao){
            case NEW:
                registrarCadastro(usuariosNewPtr);
                usuariosNewPtr++;
                nUsuariosAtual++;
                continue;
            case ATT:
                atualizarCadastro(usuarios, nUsuariosAtual);
                continue;
            case STOP:
                break;
            default:
                printf("%s", aviso);
                continue;
        }

        break;
    }

    return 0;
}