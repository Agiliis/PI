#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <stdbool.h>

// Variáveis globais
GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;

#define CONS_UP         "\033[A"
#define CONS_DEL_LINE   "\033[2K"
#define CONS_CLEAR      "\033[2J"
#define CONS_RESET      "\033[f"

#if _WIN32
#include <windows.h>
void limpar_tela() {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    COORD homeCoords = {0, 0};
    DWORD count;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, &count);
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
#elif defined(unix)
void limpar_tela() {
    printf("%s%s", CONS_RESET, CONS_CLEAR);
}
#endif

#define MAX_SALAS 42
#define MAX_RESERVAS 100
#define NUM_HORARIOS (sizeof(horarios) / sizeof(horarios[0]))

typedef struct {
    int id;
    char nome[20];
    char tipo[50];
    char bloco[50];
} Sala;

typedef struct {
    int id_sala;
    char data[12];
    char horario[6];
} Reserva;

const int ultimoDia[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *horarios[] = {"07:10", "08:00", "08:50", "09:40", "10:30", "11:20", "12:10", "13:00",
                          "13:50", "14:40", "15:30", "16:20", "17:10", "18:00", "18:50", "19:40",
                          "20:30", "21:20", "22:10", "23:00"};

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

int verificar_disponibilidade(Reserva reservas[], int id_sala, char *data, char *horario);
int check_data(char data[]);
void listar_salas_disponiveis(Sala salas[], Reserva reservas[], char *data, char *horario);
void escolher_horario(char *horario_escolhido);
void ler_relacao_das_salas(const char *pathDoArq, Sala *salas);
void ler_reservas(const char *pathDoArq, Reserva *reservas);
void escolher_data(char data[]);
void reservar_sala(Reserva reservas[], int *num_reservas, const char *nome_arquivo, char *data, char *horario);

// Funções GTK
void on_view_cancelar_reserva_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void on_button_novo_usu_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_exit_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}


void on_lembrar_usu_toggled(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void on_cadastro_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page2"); 
}

void on_login_button_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}

void on_button_voltar_cad_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "view_inicial");
}

void on_button_cadastar_cad_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "view_login");
}

void on_button_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page3");
}

void on_cancelar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page1");
}

void on_localizar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page4");
}

void on_voltar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}

void on_button_confirmar_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}

void on_button_volta_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page3");
}

void on_confirmar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}

void on_excluir_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}


int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("hemir.ui");

    gtk_builder_add_callback_symbols(builder,
    "on_view_cancelar_reserva_destroy", G_CALLBACK(on_view_cancelar_reserva_destroy),
    "on_login_button_clicked",          G_CALLBACK(on_login_button_clicked),
    "on_button_novo_usu_clicked",       G_CALLBACK(on_button_novo_usu_clicked),
    "on_lembrar_usu_toggled",           G_CALLBACK(on_lembrar_usu_toggled),
    "on_cadastro_button_clicked",       G_CALLBACK(on_cadastro_button_clicked),
    "on_exit_button_clicked",           G_CALLBACK(on_exit_button_clicked),
    "on_button_voltar_cad_clicked",     G_CALLBACK(on_button_voltar_cad_clicked),
    "on_button_cadastar_cad_clicked",   G_CALLBACK(on_button_cadastar_cad_clicked),
    "on_button_reserva_clicked",        G_CALLBACK(on_button_reserva_clicked),
    "on_cancelar_reserva_clicked",      G_CALLBACK(on_cancelar_reserva_clicked),
    "on_localizar_reserva_clicked",     G_CALLBACK(on_localizar_reserva_clicked),
    "on_voltar_reserva_clicked",        G_CALLBACK(on_voltar_reserva_clicked),
    "on_button_confirmar_clicked",      G_CALLBACK(on_button_confirmar_clicked),
    "on_button_volta_clicked",          G_CALLBACK(on_button_volta_clicked),
    "on_confirmar_reserva_clicked",     G_CALLBACK(on_confirmar_reserva_clicked),
    "on_excluir_reserva_clicked",       G_CALLBACK(on_excluir_reserva_clicked),
                                     NULL);
    gtk_builder_connect_signals(builder, NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}

void ler_relacao_das_salas(const char *pathDoArq, Sala *salas) {
    FILE *arquivo = fopen(pathDoArq, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de salas");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < MAX_SALAS; i++) {
        fscanf(arquivo, "%s %s %s", salas[i].nome, salas[i].tipo, salas[i].bloco);
        salas[i].id = i;
    }
    fclose(arquivo);
}

void ler_reservas(const char *pathDoArq, Reserva *reservas) {
    FILE *arquivo = fopen(pathDoArq, "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas");
        exit(EXIT_FAILURE);
    }
    while (fscanf(arquivo, "%d %s %s", &reservas[num_reservas].id_sala,
                  reservas[num_reservas].data, reservas[num_reservas].horario) == 3) {
        num_reservas++;
    }
    fclose(arquivo);
}
