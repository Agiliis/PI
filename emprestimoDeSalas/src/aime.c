#include <stdio.h>
#include <string.h>
#define MAX_SALAS 42
#define MAX_RESERVAS 100
#define NUM_HORARIOS (sizeof(horarios) / sizeof(horarios[0]))

typedef struct {
    int     id;
    char    nome[20];
    char    tipo[50];
    char    bloco[50];
} Sala;

typedef struct {
    int     id_sala;
    char    data[11];
    char    horario[6];
} Reserva;

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
const char *horarios[] = {"07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", "20:30", "21:20", "22:10", "23:00"};

#warning pq tem uma variavel e uma definicao ambos com a qtd de salas?
int num_salas = 41;
int num_reservas = 2;

FILE *relacaoDasSalas;

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);
void listar_salas_disponiveis(Sala salas[], int num_salas, Reserva reservas[], int num_reservas, char *data, char *horario);
void escolher_horario(char *horario_escolhido);

int main() {

    #warning implementar leitura do csv em funcao
    relacaoDasSalas = fopen("../res/salas.csv", "r");
    for(int i = 0; i < MAX_SALAS; i++){
        Sala aux;

        aux.id = i;
        fscanf(relacaoDasSalas, "%s %s %s", aux.nome, aux.tipo, aux.bloco);

        salas[i] = aux;
    }
    fclose(relacaoDasSalas);

    #warning add checagem de input pra data
    char data[11];
    printf("Digite a data (DD-MM-AAAA): ");
    scanf("%s", data);

    char horario[6];
    escolher_horario(horario);

    #warning necessario modificar se for seguir com o fluxo de "mostrar primeira sala disponível"
    listar_salas_disponiveis(salas, num_salas, reservas, num_reservas, data, horario);

    #warning add funcao de reservar salas

    return 0;
}

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario) {
    for (int i = 0; i < num_reservas; i++) {
        if (reservas[i].id_sala == id_sala &&
            strcmp(reservas[i].data, data) == 0 &&
            strcmp(reservas[i].horario, horario) == 0) {
            return 0;
        }
    }

    return 1;
}

void listar_salas_disponiveis(Sala salas[], int num_salas, Reserva reservas[], int num_reservas, char *data, char *horario) {
    int encontrou_disponivel = 0;
    
    printf("Salas disponiveis para a data %s no horario %s:\n", data, horario);

    for (int i = 1; i < num_salas; i++) {
        if (verificar_disponibilidade(reservas, num_reservas, salas[i].id, data, horario) == 1) {
            printf("ID: %d\t| Nome: %s\t| Tipo: %s\t| Bloco: %s\n",
                   salas[i].id, salas[i].nome, salas[i].tipo, salas[i].bloco);
            encontrou_disponivel = 1;
        }
    }

    if (!encontrou_disponivel) {
        printf("Nenhuma sala disponivel para o horario solicitado.\n");
    }
}

void escolher_horario(char *horario_escolhido) {
    int escolha = 1;

    printf("Escolha um horario:\n");
    for (int i = 0; i < NUM_HORARIOS; i++) {
        printf("%d.\t%s\n", i + 1, horarios[i]);
    }

    do {
        #warning melhorar aviso
        if(escolha < 1 || escolha > NUM_HORARIOS) printf("Horário inválido!\n");
        printf("Digite o numero do horario desejado: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > NUM_HORARIOS);

    strcpy(horario_escolhido, horarios[escolha - 1]);
}
