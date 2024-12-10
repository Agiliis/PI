#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <loginFuncs.h>
#include <limparTela.h>

void ler_base_de_usuarios(char *pathToArq, User *usrArr, int *userCnt){
    FILE *userBase = fopen(pathToArq, "r");

    if(userBase == NULL){
        perror("Erro ao abrir arquivo res/userBase.txt");
        puts("Pressione qualquer tecla para fechar..."); getchar();
        exit(1);
    }

    while(fscanf(userBase, "%s %s", (*usrArr).email, (*usrArr).senha) == 2){
        (*userCnt)++;
        usrArr++;
    }

    fclose(userBase);
}

User tela_de_login(User usuarios[], int userCnt){
    char buffer[BUFSIZ];
    int ok;
    User user, no_user = {.email = "no_user"};

    // pegar email

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts("Email nao encontrado");
        }

        puts("Digite seu email institucional @poli.br ou 'ret' para retornar");

        fgets(buffer, BUFSIZ, stdin);

        if(strcmp(buffer, "ret\n\0") == 0){
            limpar_tela();
            return no_user;
        }

        char *aux = strtok(buffer, "\n");

        strcpy(user.email, aux);

        ok = (check_email(user.email) && check_user(&user, usuarios, userCnt));

    }while(!ok);

    limpar_tela();

    // pegar senha

    ok = 1;
    for(int i = 3; i > 0; i--){
        char tentativa[10];

        if(!ok){
            limpar_tela();
            printf("Senha errada! Voce tem %d tentativas restantes\n", i);
        }

        puts("Digite sua senha");

        fgets(buffer, BUFSIZ, stdin);
    
        char *aux = strtok(buffer, "\n");
        strcpy(tentativa, aux);

        ok = (strcmp(tentativa, user.senha) == 0);

        if(ok){
            limpar_tela();
            return user;
        }
    }

    limpar_tela();

    puts("Excesso de tentativas, voltando a tela inicial");

    return no_user;

}

User cadastrar_login(char *pathToUserBase, User *usuarios, int *userCnt){
    int ok;
    char buffer[BUFSIZ];
    User user, no_user = {.email = "no_user"};

    FILE *userBase = fopen(pathToUserBase, "a");

    if(userBase == NULL){
        perror("Erro ao abrir userBase.txt");
        puts("Pressione qualquer tecla para fechar..."); getchar();
        exit(1);
    }

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts("Email invalido!");
        }

        puts("Digite seu email institucional @poli.br ou 'ret' para retornar");

        fgets(buffer, BUFSIZ, stdin);

        if(strcmp(buffer, "ret\n\0") == 0){
            limpar_tela();
            return no_user;
        }

        char *aux = strtok(buffer, "\n");
        strcpy(user.email, aux);

        ok = (check_email(user.email) && !check_user(&user, usuarios, (*userCnt)));

    }while(!ok);

    limpar_tela();

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts("Senha invalida!");
        }

        puts("Digite uma senha entre 5 e 10 caracteres");

        fgets(buffer, BUFSIZ, stdin);

        char *aux = strtok(buffer, "\n");
        strcpy(user.senha, aux);

        ok = (check_senha(user.senha)); 

    }while(!ok);

    limpar_tela();

    printf("%s cadastrado com sucesso!\n\n", user.email);

    fprintf(userBase, "%s %s\n", user.email, user.senha);

    strcpy(usuarios[(*userCnt)].email, user.email);
    strcpy(usuarios[(*userCnt)].senha, user.senha);
    (*userCnt)++;

    fclose(userBase);

    return user;
}

/********************************************************************/

int check_user(User *user, User usuarios[], int userCnt){

    for(int i = 0; i < userCnt; i++){
        if(strcmp((*user).email, usuarios[i].email) == 0){
            strcpy((*user).senha, usuarios[i].senha);
            return 1;
        }
    }

    return 0;
}

int check_email(char email[]){
    int ok = 1;
    char *dominio;

    dominio = strtok(email, "@");
    dominio = strtok(NULL, "@");

    ok = (dominio != NULL && strcmp(dominio, "poli.br") == 0);

    return ok;
}

int check_senha(char senha[]){
    int ok = 1;
    int len = strlen(senha);

    ok = (5 <= len && len <= 10);

    return ok;
}