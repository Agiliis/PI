#ifndef RESERVAS_FUNCS_H
#define RESERVAS_FUNCS_H

#define MAX_SALAS       42
#define MAX_RESERVAS    100
#define NUM_HORARIOS    (sizeof(horarios) / sizeof(horarios[0]))

#warning refactorizar struct de reserva em struct de salas (se der tempo eu tento)

typedef struct {
    int     id;
    char    nome[20];
    char    tipo[50];
    char    bloco[50];
} Sala;

typedef struct {
    int     id_sala;
    char    data[12];
    char    horario[6];
} Reserva;


void ler_relacao_das_salas(char *pathDoArq, Sala *salas);
void ler_reservas(char *pathDoArq, Reserva *reservas, int *num_reservas);

void escolher_data(char data[]);
void escolher_horario(char *horario_escolhido);

void reservar_sala(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);

// funcoes internas de outras funcoes
void listar_horarios();
void listar_salas_disponiveis(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario);

int check_data(char data[]);
int check_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);
//



#endif