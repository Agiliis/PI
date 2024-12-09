#ifndef LOGIN_FUNCS_H
#define LOGIN_FUNCS_H

#define USER_MAX_NUM 256

typedef struct {
    char    email[20],
            senha[10 + 2];
} User;

void ler_base_de_usuarios(char *pathToArq, User *usrArr, int *userCnt);

User tela_de_login();
void cadastrar_login();

// funcoes internas
int check_user(User *user);
int check_email(char email[]);
int check_senha(char senha[]);
//

#endif