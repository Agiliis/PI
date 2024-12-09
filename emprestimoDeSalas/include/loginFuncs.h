#ifndef LOGIN_FUNCS_H
#define LOGIN_FUNCS_H

#define USER_MAX_NUM 256

typedef struct {
    char    email[20],
            senha[10 + 2];
} User;

void ler_base_de_usuarios(char *pathToArq, User *usrArr, int *userCnt);

// retorna o usuario logado ou 'no_user' se nenhum usuario for logado
User tela_de_login(User usuarios[], int userCnt);

void cadastrar_login(User *usuarios, int *userCnt);

// funcoes internas
int check_user(User *user, User usuarios[], int userCnt);
int check_email(char email[]);
int check_senha(char senha[]);
//

#endif