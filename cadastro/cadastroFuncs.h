#include <stdio.h>

#define dbgc(x) printf("%s = %c\n", #x, x);
#define dbgs(x) printf("%s = %s\n", #x, x);
#define dbgi(x) printf("%s = %d\n", #x, x);

#define BUFF_SZ 256
#define MAXN_USER 256

#define NEW '1'
#define ATT '2'
#define STOP '3'

const char *titulo1      = "\nCADASTRO DE USUÁRIOS \n\n";
const char *titulo2      = "\nATUALIZACAO DE CADASTROS \n\n";
const char *opcoes1      = "Digite: \n[1] para cadastrar um novo usuário \n[3] para finalizar os cadastros\n";
const char *opcoes2      = "Digite: \n[2] para atualizar algum cadastro \n[3] para encerrar o programa\n";
const char *opcoes2_2    = "[1] atualizar o nome \n[2] atualizar o telefone \n[3] atualizar o endereço \n[4] atualizar o login \n[5] atualizar a senha \n[6] para deslogar \n";
const char *aviso        = "Insira uma resposta válida!\n";

typedef struct {
    char    login[BUFF_SZ],
            senha[BUFF_SZ],
            nome[BUFF_SZ],
            endereco[BUFF_SZ],
            telefone[BUFF_SZ],
            nascimento[BUFF_SZ];
} user;

void registrarCadastro(user *);
void atualizarCadastro(user *, int);