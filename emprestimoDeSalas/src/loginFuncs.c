#include <stdio.h>
#include <loginFuncs.h>
#include <limparTela.h>

User usuarios[USER_MAX_NUM];
int userCnt = 0;

void ler_base_de_usuarios(char *pathToArq, User *usrArr, int *userCnt){
    FILE *userBase = fopen(pathToArq, "r");

    if(userBase == NULL){
        perror("Erro ao abrir arquivo res/userBase.txt");
        exit(1);
    }

    while(fscanf(userBase, "%s %s", (*usrArr).email, (*usrArr).senha) == 2){
        (*userCnt)++;
        usrArr++;
    }

    fclose(userBase);
}

User tela_de_login(){
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

        puts("Digite seu email ou 'ret' para retornar");

        fgets(buffer, BUFSIZ, stdin);

        if(strcmp(buffer, "ret\n\0") == 0){
            limpar_tela();
            return no_user;
        }

        char *aux = strtok(buffer, "\n");

        strcpy(user.email, aux);

        ok = (check_email(user.email) && check_user(&user));

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

void cadastrar_login(){
    int ok;
    char buffer[BUFSIZ];
    User user;

    FILE *userBase = fopen("../res/userBase.txt", "a");

    if(userBase == NULL){
        perror("Erro ao abrir res/userBase.txt");
        exit(0);
    }

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts("Email invalido!");
        }

        puts("Digite seu email institucional @poli.br");

        fgets(buffer, BUFSIZ, stdin);

        char *aux = strtok(buffer, "\n");
        strcpy(user.email, aux);

        ok = (check_email(user.email) && !check_user(&user));

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

    fprintf(userBase, "%s %s\n", user.email, user.senha);

    strcpy(usuarios[userCnt].email, user.email);
    strcpy(usuarios[userCnt].senha, user.senha);
    userCnt++;

    fclose(userBase);
}

int check_user(User *user){

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