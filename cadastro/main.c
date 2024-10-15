#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cadastroFuncs.h"

#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);
#define dbgi(x) printf("%s = %d\n", #x, x);

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
} user;

user usuarios[MAXN_USER];
int nUsuariosAtual = 0;

user    *usuariosNewPtr = usuarios, 
        *usuariosAttPtr = usuarios;

char saudacao[] = "Digite: \n[1] para cadastrar um novo usuário \n[2] para atualizar um cadastro \n[3] para finalizar o programa\n";
char aviso[]    = "Insira uma resposta válida!\n";

void registrarCadastro(user *userPtr){
    printf("Informe seu nome: ");
    scanf("%s", (*userPtr).nome);

    printf("Informe seu telefone: ");
    scanf("%s", (*userPtr).telefone);

    printf("Informe sua data de nascimento (formato dd/mm/aaaa): ");
    scanf("%s", (*userPtr).nascimento);

    printf("Informe seu login (e-mail): ");
    scanf("%s", (*userPtr).login);

    printf("Cadastre uma senha: ");
    scanf("%s", (*userPtr).senha);

    printf("Usuário %s cadastrado com sucesso!\n", (*userPtr).login);
}

void atualizarCadastro(){
    while(1){
        user *userPtr = usuarios;

        char    loginTentativa[BUFF_SZ],
                senhaTentativa[BUFF_SZ];

        printf("Insira seu login cadastrado (e-mail): ");
        scanf("%s", loginTentativa);

        dbgs(loginTentativa)

        int cnt = 1;
        while(strcmp((*userPtr).login, loginTentativa) != 0 && cnt <= nUsuariosAtual){
            userPtr++;
            cnt++;
        }

        dbgi(cnt)
        dbgs((*userPtr).login)

        if(cnt > nUsuariosAtual){
            printf("Login %s não encontrado\n", loginTentativa);
            continue;
        }

        printf("Insira sua senha cadastrada: ");
        scanf("%s", &senhaTentativa);

        if(strcmp((*userPtr).senha, senhaTentativa) != 0){
            printf("Senha errada\n");
            continue;
        }

        printf("Bem vindo %s! O que deseja atualizar?\n", (*userPtr).nome);

        while(1){   
            printf("[1] para atualizar o nome \n[2] para atualizar o telefone \n[3] para atualizar a data de nascimento (formato dd/mm/aaaa) \n[4] para atualizar o login \n[5] para atualizar a senha \n");

            char opcao;
            scanf(" %c", &opcao);

            char aux[BUFF_SZ];

            switch(opcao){
                case '1':
                    strcpy(aux, (*userPtr).nome);

                    printf("Digite seu novo nome: ");
                    scanf("%s", &(*userPtr).nome);
                    printf("Nome atualizado de %s para %s\n", aux, (*userPtr).nome);

                    break;
                case '2':
                    strcpy(aux, (*userPtr).telefone);

                    printf("Digite seu novo telefone: ");
                    scanf("%s", &(*userPtr).telefone);
                    printf("Telefone atualizado de %s para %s\n", aux, (*userPtr).telefone);

                    break;
                case '3':
                    strcpy(aux, (*userPtr).nascimento);

                    printf("Digite sua nova data de nascimento (formato dd/mm/aaaa): ");
                    scanf("%s", &(*userPtr).nascimento);
                    printf("Data de nascimento atualizada de %s para %s\n", aux, (*userPtr).nascimento);

                    break;
                case '4':
                    strcpy(aux, (*userPtr).telefone);

                    printf("Digite seu novo login (e-mail): ");
                    scanf("%s", &(*userPtr).login);
                    printf("Login atualizado de %s para %s\n", aux, (*userPtr).login);
                    
                    break;
                case '5':
                    strcpy(aux, (*userPtr).senha);

                    printf("Digite sua nova senha: ");
                    scanf("%s", &(*userPtr).senha);
                    printf("Senha atualizada de %s para %s\n", aux, (*userPtr).senha);
                    
                    break;
                default:
                    printf("%s", aviso);
                    continue;
            }

            printf("Deseja atualizar mais algum dado %s? [S/n]\n", (*userPtr).nome);

            scanf(" %c", &opcao);

            if(opcao == 'n' || opcao == 'N') break;
        }

        break;
    }
}

int main(){

    while(1){
        printf("%s", saudacao);
        
        char opcao;
        scanf(" %c", &opcao);
            
        switch(opcao){
            case NEW:
                registrarCadastro(usuariosNewPtr);
                usuariosNewPtr++;
                nUsuariosAtual++;
                continue;
            case ATT:
                atualizarCadastro(usuariosAttPtr);
                continue;
            case STOP:
                break;
            default:
                printf("%s", aviso);
                continue;
        }

        dbgs(usuarios[0].login)

        break;
    }

    return 0;
}