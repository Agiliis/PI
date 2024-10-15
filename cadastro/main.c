#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastroFuncs.c"

user usuarios[MAXN_USER];
int nUsuariosAtual = 0;

user *usuariosNewPtr = usuarios; 

int main(){
    
    // cadastro de usuarios
    printf(titulo1);
    while(1){
        printf(opcoes1);
        
        char opcao;
        scanf(" %c", &opcao);
            
        switch(opcao){
            case NEW:
                registrarCadastro(usuariosNewPtr);
                usuariosNewPtr++;
                nUsuariosAtual++;
                continue;
            case STOP:
                break;
            default:
                printf("%s", aviso);
                continue;
        }

        break;
    }

    if(nUsuariosAtual < 1){
        printf("Nenhum usuário foi cadastrado\n");
        return 0;
    }

    //atualizacao de cadastros
    printf(titulo2);
    while(1){
        printf(opcoes2);
        
        char opcao;
        scanf(" %c", &opcao);
            
        switch(opcao){
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