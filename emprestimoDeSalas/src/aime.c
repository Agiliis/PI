#include <stdio.h>
#include <string.h>
#define MAX_SALAS 42
#define MAX_RESERVAS 100

typedef struct {
    int id;
    char nome[20];
    char tipo[50];
    char bloco[50];
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

FILE *csvFile;

int main() {
    Sala salas[MAX_SALAS];
    Reserva reservas[MAX_RESERVAS];
    int num_salas = 41;
    int num_reservas = 2;

    csvFile = fopen("../res/salas.csv", "r");
    for(int i = 0; i < MAX_SALAS; i++){
        Sala aux;
        aux.id = i+1;
        
        fscanf(csvFile, "%s %s %s", aux.nome, aux.tipo, aux.bloco);

        salas[i] = aux;
    }
    fclose(csvFile);

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
    printf("Escolha um horario:\n");
    for (int i = 0; i < NUM_HORARIOS; i++) {
        printf("%d. %s\n", i + 1, horarios[i]);
    }

    int escolha;
    do {
        printf("Digite o numero do horario desejado: ");
        scanf("%d", &escolha);
    } while (escolha < 1 || escolha > NUM_HORARIOS);

    strcpy(horario_escolhido, horarios[escolha - 1]);
}
