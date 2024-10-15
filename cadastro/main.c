#include <stdio.h>
#include <stdlib.h>

#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);

#define BUFF_SZ 256
#define MAXN_USER 256

#define NEW '1'
#define ATT '2'
#define STOP '3'

typedef struct {
    char    login[BUFF_SZ],
            senha[BUFF_SZ],
            nome[BUFF_SZ],
            telefone[BUFF_SZ],
            nascimento[BUFF_SZ];
    char a;
} user;

user usuarios[MAXN_USER];

char saudacao[] = "Digite: \n[1] para cadastrar um novo usuário \n[2] para atualizar um cadastro \n[3] para finalizar o programa\n";

int main(){

    user *usuariosPtr = &usuarios;

    while(1){
        printf("%s", saudacao);
        
        char opcao;
        scanf("%c", &opcao);
            
        if(opcao == NEW){
            printf("Informe seu nome: ");
            scanf("%s", &(*usuariosPtr).login);

            printf("Informe seu telefone: ");
            scanf("%s", &(*usuariosPtr).telefone);

            printf("Informe sua data de nascimento (formato dd/mm/aaaa): ");
            scanf("%s", &(*usuariosPtr).nascimento);

            printf("Informe seu login (e-mail): ");
            scanf("%s", &(*usuariosPtr).login);

            printf("Cadastre uma senha: ");
            scanf("%s", &(*usuariosPtr).senha);

            printf("Usuário %s cadastrado com sucesso!\n", (*usuariosPtr).login);

            usuariosPtr++;
        }else if(opcao == ATT){
            printf("att\n");
        }else if(opcao == STOP){
            break;
        }else{
            printf("%d\n", opcao);
        }
    }

    return 0;
}