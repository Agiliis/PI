#ifndef RESERVAS_FUNCS_H
#define RESERVAS_FUNCS_H

#define MAX_SALAS       42
#define MAX_RESERVAS    100
#define NUM_HORARIOS    (sizeof(horarios) / sizeof(horarios[0]))

// refactorizar struct de reserva em struct de salas (se der tempo eu tento)

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

//Ultimo dia de cada mes
// -------------------------------- J   F   M   A   M   J   J   A   S   O   N   D
static const int ultimoDia[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

static const char *horarios[] = {   "07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00", 
                                    "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40", 
                                    "20:30", "21:20", "22:10", "23:00"};

void ler_relacao_das_salas(char *pathDoArq, Sala *salas);
void ler_reservas(char *pathDoArq, Reserva *reservas, int *num_reservas);

void escolher_data(char data[]);
void escolher_horario(char *horario_escolhido);

void criar_reserva(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);
void remover_reserva(Sala salas[], Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);

/******** funcoes internas de outras funcoes *******/

void listar_horarios();

/*
"disponivel": lista salas disponiveis
"indisponivel": lista salas indisponiveis
*/
void listar_salas(Sala salas[], Reserva reservas[], int num_reservas, char *data, char *horario, const char *modo);

int check_data(char data[]);
int check_disponibilidade(Reserva reservas[], int num_reservas, int id_sala, char *data, char *horario);

/**************************************************/



#endif