#include <stdio.h>
#include <string.h>
#define MAX_SALAS 45
#define MAX_RESERVAS 100

typedef struct {
    int id;
    char nome[50];
    char tipo[20];
    char bloco[20];
} Sala;

typedef struct {
    int id_sala;
    char data[11];
    char horario[6];
} Reserva;

const char *horarios[] = {"07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", "20:30", "21:20", "22:10", "23:00"};
#define NUM_HORARIOS (sizeof(horarios) / sizeof(horarios[0]))

int verificar_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);
void listar_salas_disponiveis(Sala salas[], int num_salas, Reserva reservas[], int num_reservas, char *data, char *horario);
void escolher_horario(char *horario_escolhido);

int main() {
    Sala salas[MAX_SALAS] = {
        {1, "LIP-04", "LIP", "Bloca A"},
        {2, "B01", "Sala de Aula", "Bloco B"},
        {3, "B02", "Sala de Aula", "Bloco B"},
        {4, "B03", "Sala de Aula", "Bloco B"},
        {5, "B04", "Sala de Aula", "Bloco B"},
        {6, "B05", "Sala de Aula", "Bloco B"},
        {7, "B06", "Sala de Aula", "Bloco B"},
        {8, "B07", "Sala de Aula", "Bloco B"},
        {9, "B08", "Sala de Aula", "Bloco B"},
        {10, "B09", "Sala de Aula", "Bloco B"},
        {11, "LIP-01", "LIP", "Bloco F"},
        {12, "LIP-02", "LIP", "Bloco F"},
        {13, "LIP-07", "LIP", "Bloco G"},
        {14, "LIP-03", "LIP", "Bloco H"},
        {15, "LIP-05", "LIP", "Bloco J"},
        {16, "LIP-06", "LIP", "Bloco J"},
        {17, "K03", "Sala de Aula", "Bloco K"},
        {18, "K04", "Sala de Aula", "Bloco K"},
        {19, "K05", "Sala de Aula", "Bloco K"},
        {20, "K06", "Sala de Aula", "Bloco K"},
        {21, "K07", "Sala de Aula", "Bloco K"},
        {22, "K08", "Sala de Aula", "Bloco K"},
        {23, "K09", "Sala de Aula", "Bloco K"},
        {24, "K10", "Sala de Aula", "Bloco K"},
        {25, "K11", "Sala de Aula", "Bloco K"},
        {26, "K12", "Sala de Aula", "Bloco K"},
        {27, "K13", "Sala de Aula", "Bloco K"},
        {28, "K14", "Sala de Aula", "Bloco K"},
        {29, "IO3", "Sala de Aula", "Bloco I"},
        {30, "I04", "Sala de Aula", "Bloco I"},
        {31, "I05", "Sala de Aula", "Bloco I"},
        {32, "I06", "Sala de Aula", "Bloco I"},
        {33, "I07", "Sala de Aula", "Bloco I"},
        {34, "I08", "Sala de Aula", "Bloco I"},
        {35, "I09", "Sala de Aula", "Bloco I"},
        {36, "I10", "Sala de Aula", "Bloco I"},
        {37, "I11", "Sala de Aula", "Bloco I"},
        {38, "I12", "Sala de Aula", "Bloco I"},
        {39, "I13", "Sala de Aula", "Bloco I"},
        {40, "I14", "Sala de Aula", "Bloco I"},
        {41, "I15", "Sala de Aula", "Bloco I"}
    };
    int num_salas = 41;
    };
    int num_reservas = 2;

    char data[11];
    printf("Digite a data (DD-MM-AAAA): ");
    scanf("%s", data);

    char horario[6];
    escolher_horario(horario);

    listar_salas_disponiveis(salas, num_salas, reservas, num_reservas, data, horario);

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
    printf("Salas dispon�veis para a data %s no hor�rio %s:\n", data, horario);
    int encontrou_disponivel = 0;

    for (int i = 0; i < num_salas; i++) {
        if (verificar_disponibilidade(reservas, num_reservas, salas[i].id, data, horario)) {
            printf("ID: %d | Nome: %s | Tipo: %s | Bloco: %s\n",
                   salas[i].id, salas[i].nome, salas[i].tipo, salas[i].bloco);
            encontrou_disponivel = 1;
        }
    }

    if (!encontrou_disponivel) {
        printf("Nenhuma sala dispon�vel para o hor�rio solicitado.\n");
    }
}

void escolher_horario(char *horario_escolhido) {
    printf("Escolha um hor�rio:\n");
    for (int i = 0; i < NUM_HORARIOS; i++) {
        printf("%d. %s\n", i + 1, horarios[i]);
    }

    int escolha;
    do {
        printf("Digite o n�mero do hor�rio desejado: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > NUM_HORARIOS);

    strcpy(horario_escolhido, horarios[escolha - 1]);
}
