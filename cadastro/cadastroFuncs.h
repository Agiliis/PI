#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);
#define dbgi(x) printf("%s = %d\n", #x, x);

#define BUFF_SZ 256
#define MAXN_USER 256

#define NEW '1'
#define ATT '2'
#define STOP '3'

char saudacao1[]    = "Digite: \n[1] para cadastrar um novo usuário \n[2] para atualizar um cadastro \n[3] para finalizar o programa\n";
char saudacao2[]    = "[1] para atualizar o nome \n[2] para atualizar o telefone \n[3] para atualizar a data de nascimento \n[4] para atualizar o login \n[5] para atualizar a senha \n[6] para deslogar \n";
char aviso[]        = "Insira uma resposta válida!\n";

typedef struct {
    char    login[BUFF_SZ],
            senha[BUFF_SZ],
            nome[BUFF_SZ],
            telefone[BUFF_SZ],
            nascimento[BUFF_SZ];
} user;

void registrarCadastro(user *);
void atualizarCadastro(user *, int);

//void acharLogin(user *userPtr);

// void attNome(user *userPtr);
// void attTelefone(user *userPtr);
// void attNascimento(user *userPtr);
// void attLogin(user *userPtr);
// void attSenha(user *userPtr);