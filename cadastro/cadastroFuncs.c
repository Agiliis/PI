#include "cadastroFuncs.h"

user *retomarUsuarios(user *userPtr, int *nUsuariosAtual){
    registroUsuarios = fopen("registroUsuarios.txt", "r");

    while(fscanf(registroUsuarios, "%s %s %s %s %s", (*userPtr).nome, (*userPtr).telefone, (*userPtr).nascimento, (*userPtr).login, (*userPtr).senha) == 5){
        dbgs((*userPtr).login)
        (*nUsuariosAtual)++;
        userPtr++; 
    }

    fclose(registroUsuarios);

    return userPtr;
}

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

    registroUsuarios = fopen("registroUsuarios.txt", "a");

    fprintf(registroUsuarios, "%s %s %s %s %s\n", (*userPtr).nome, (*userPtr).telefone, (*userPtr).nascimento, (*userPtr).login, (*userPtr).senha);

    printf("Usuário %s cadastrado com sucesso!\n", (*userPtr).login);

    fclose(registroUsuarios);
}

void atualizarCadastro(user *userPtr, int nUsuariosAtual){
    user *userPermutPtr = userPtr;

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
    scanf("%s", &senhaTentativa);

    if(strcmp((*userPtr).senha, senhaTentativa) != 0){
        printf("Senha errada\n");
        return;
    }

    printf("Bem vindo %s! O que deseja atualizar?\n", (*userPtr).nome);

    while(1){   
        printf("%s", saudacao2);

        char opcao;
        scanf(" %c", &opcao);

        char aux[BUFF_SZ];

        switch(opcao){
            case '1':
                strcpy(aux, (*userPtr).nome);

                printf("Digite seu novo nome: ");
                scanf("%s", &(*userPtr).nome);
                printf("Nome atualizado de %s para %s\n", aux, (*userPtr).nome);

                continue;
            case '2':
                strcpy(aux, (*userPtr).telefone);

                printf("Digite seu novo telefone: ");
                scanf("%s", &(*userPtr).telefone);
                printf("Telefone atualizado de %s para %s\n", aux, (*userPtr).telefone);

                continue;
            case '3':
                strcpy(aux, (*userPtr).nascimento);

                printf("Digite sua nova data de nascimento (formato dd/mm/aaaa): ");
                scanf("%s", &(*userPtr).nascimento);
                printf("Data de nascimento atualizada de %s para %s\n", aux, (*userPtr).nascimento);

                continue;
            case '4':
                strcpy(aux, (*userPtr).login);

                printf("Digite seu novo login (e-mail): ");
                scanf("%s", &(*userPtr).login);
                printf("Login atualizado de %s para %s\n", aux, (*userPtr).login);
                
                continue;
            case '5':
                strcpy(aux, (*userPtr).senha);

                printf("Digite sua nova senha: ");
                scanf("%s", &(*userPtr).senha);
                printf("Senha atualizada de %s para %s\n", aux, (*userPtr).senha);
                
                continue;
            case '6':
                break;
            default:
                printf("%s", aviso);
                continue;
        }

        break;
    }

    registroUsuarios = fopen("registroUsuarios.txt", "w");

    for(int i = 0; i < nUsuariosAtual; i++){
        fprintf(registroUsuarios, "%s %s %s %s %s\n", (*userPermutPtr).nome, (*userPermutPtr).telefone, (*userPermutPtr).nascimento, (*userPermutPtr).login, (*userPermutPtr).senha);
        userPermutPtr++;
    }

    fclose(registroUsuarios);
}