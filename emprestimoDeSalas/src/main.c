#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"


#define USER_MAX_NUM 256

#define ARRAY_SZ(x) (sizeof(x) / sizeof(x[0]))

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

typedef struct {
    char    email[20],
            senha[10 + 2];
} User;

User usuarios[USER_MAX_NUM];
int userCnt = 0;

void retomar_usuarios(){
    FILE *userBase = fopen("../res/userBase.txt", "r");

    User *usrArr = usuarios;

    if(userBase == NULL){
        perror("Erro ao abrir arquivo res/userBase.txt");
        exit(1);
    }

    while(fscanf(userBase, "%s %s", (*usrArr).email, (*usrArr).senha) == 2){
        userCnt++;
        usrArr++;
    }

    fclose(userBase);
}

void limpar_tela(){ 
    #if DBG_MODE == 0
        printf(CONS_RESET); printf(CONS_CLEAR); 
    #endif
}

void listar_opcoes(char *opcoes[], int numOpcoes){
    for(int i = 0; i < numOpcoes; i++){
        printf("%d. %s\n", i+1, opcoes[i]);
    }
}

int validar_email(char email[]){
    int ok = 1;
    char *dominio;

    dominio = strtok(email, "@");
    dominio = strtok(NULL, "@");

    ok = (dominio != NULL && strcmp(dominio, "poli.br") == 0);

    return ok;
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

int pedido_em_intervalo(char *opcoes[], int numOpcoes, char *pedido, char *aviso){
    int ok;
    char buffer[BUFSIZ];
    int resposta;

    listar_opcoes(opcoes, numOpcoes);

    ok = 1;
    do{
        if(!ok){
            limpar_tela();
            puts(aviso);
            listar_opcoes(opcoes, numOpcoes);
        }

        printf("%s", pedido);

        fgets(buffer, sizeof(buffer), stdin);

        resposta = atoi(buffer);
        ok = (1 <= resposta && resposta <= numOpcoes);

    }while(!ok);

    limpar_tela();

    return resposta;
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

        ok = (validar_email(user.email) && check_user(&user));

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

int validar_senha(char senha[]){
    int ok = 1;
    int len = strlen(senha);

    ok = (5 <= len && len <= 10);

    return ok;
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

        ok = (validar_email(user.email) && !check_user(&user));

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

        ok = (validar_senha(user.senha)); 

    }while(!ok);

    limpar_tela();

    fprintf(userBase, "%s %s\n", user.email, user.senha);

    strcpy(usuarios[userCnt].email, user.email);
    strcpy(usuarios[userCnt].senha, user.senha);
    userCnt++;

    fclose(userBase);
}

int main(){

    User usuario;

    retomar_usuarios();

    while(1){
        char *opcoes[] = {"Fazer login", "Cadastrar login", "Sair do programa"};
        
        int resposta = pedido_em_intervalo(opcoes, 3, "Digite a opcao: ", "Opcao invalida!");

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

            int resposta = pedido_em_intervalo(opcoes, 3, "O que deseja fazer?\n", "Opcao invalida!");  

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