#include "cadastroFuncs.h"

void registrarCadastro(user *userPtr){
    printf("Cadastre seu login: ");
    scanf("%s", (*userPtr).login);

    printf("Cadastre sua senha: ");
    scanf("%s", (*userPtr).senha);
    
    printf("Informe seu nome: ");
    scanf("%s", (*userPtr).nome);

    printf("Informe seu endereço: ");
    scanf("%s", (*userPtr).endereco);

    printf("Informe seu telefone: ");
    scanf("%s", (*userPtr).telefone);

    printf("Informe sua data de nascimento (formato dd/mm/aaaa) (NÃO PODE SER ALTERADA): ");
    scanf("%s", (*userPtr).nascimento);

    printf("Usuário %s cadastrado com sucesso!\n", (*userPtr).login);
}

void atualizarCadastro(user *userPtr, int nUsuariosAtual){
    char    loginTentativa[BUFF_SZ],
            senhaTentativa[BUFF_SZ];

    printf("Insira seu login cadastrado (e-mail): ");
    scanf("%s", loginTentativa);

    int cnt = 1;
    while(strcmp((*userPtr).login, loginTentativa) != 0 && cnt <= nUsuariosAtual){
        userPtr++;
        cnt++;
    }

    if(cnt > nUsuariosAtual){
        printf("Login %s não encontrado\n", loginTentativa);
        return;
    }

    printf("Insira sua senha cadastrada: ");
    scanf("%s", senhaTentativa);

    if(strcmp((*userPtr).senha, senhaTentativa) != 0){
        printf("Senha errada\n");
        return;
    }

    printf("Bem vindo %s! O que deseja fazer?\n", (*userPtr).nome);

    while(1){   
        printf(opcoes2_2);

        char opcao;
        scanf(" %c", &opcao);

        char aux[BUFF_SZ];

        switch(opcao){
            case '1':
                strcpy(aux, (*userPtr).nome);

                printf("Digite seu novo nome: ");
                scanf("%s", (*userPtr).nome);
                printf("Nome atualizado de %s para %s\n", aux, (*userPtr).nome);

                continue;
            case '2':
                strcpy(aux, (*userPtr).telefone);

                printf("Digite seu novo telefone: ");
                scanf("%s", (*userPtr).telefone);
                printf("Telefone atualizado de %s para %s\n", aux, (*userPtr).telefone);

                continue;
            case '3':
                strcpy(aux, (*userPtr).endereco);

                printf("Digite seu novo endereço: ");
                scanf("%s", (*userPtr).endereco);
                printf("Endereco atualizado de %s para %s\n", aux, (*userPtr).endereco);

                continue;
            case '4':
                strcpy(aux, (*userPtr).login);

                printf("Digite seu novo login: ");
                scanf("%s", (*userPtr).login);
                printf("Login atualizado de %s para %s\n", aux, (*userPtr).login);
                
                continue;
            case '5':
                strcpy(aux, (*userPtr).senha);

                printf("Digite sua nova senha: ");
                scanf("%s", (*userPtr).senha);
                printf("Senha atualizada de %s para %s\n", aux, (*userPtr).senha);
                
                continue;
            case '6':
                break;
            default:
                printf(aviso);
                continue;
        }

        break;
    }
}