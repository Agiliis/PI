#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <limparTela/limparTela.h>
#include <loginFuncs/loginFuncs.h>
#include <reservasFuncs/reservasFuncs.h>
#include "dbg.h"

#warning lol

// Variáveis globais
GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;
GtkComboBoxText *combobox_horarios;
GtkComboBoxText *combobox_salas;
GtkCalendar *calendario;

User usuario;
User usuarios[USER_MAX_NUM];
int userCnt = 0;   

Sala salas[MAX_SALAS];
Reserva reservas[MAX_RESERVAS];
int num_reservas = 0;

char data_calend[12];
char horario[6];

char    *pth_userBase   = "../res/userBase.txt",
        *pth_salas      = "../res/salas.csv",
        *pth_reservas   = "../res/reservas.csv";

// Funções GTK
void on_view_cancelar_reserva_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void on_button_novo_usu_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page2");
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
    GtkEntry *entry_email = GTK_ENTRY(gtk_builder_get_object(builder, "email_in"));
    GtkEntry *entry_senha = GTK_ENTRY(gtk_builder_get_object(builder, "senha_in"));

    const char *email = gtk_entry_get_text(entry_email);
    const char *senha = gtk_entry_get_text(entry_senha);

    User user;
    strcpy(user.email, email);

    if(check_email(user.email) && check_user(&user, usuarios, userCnt) && strcmp(user.senha, senha) == 0)
        gtk_stack_set_visible_child_name(stack, "page0");
}

void on_button_voltar_cad_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "view_login");
}

void on_button_cadastar_cad_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry *entry_email = GTK_ENTRY(gtk_builder_get_object(builder, "cpf_cadastro"));
    GtkEntry *entry_senha = GTK_ENTRY(gtk_builder_get_object(builder, "cad_senha"));

    const char *email = gtk_entry_get_text(entry_email);
    const char *senha = gtk_entry_get_text(entry_senha);

    User user;
    strcpy(user.email, email);
    strcpy(user.senha, senha);

    if(check_email(user.email) && !check_user(&user, usuarios, userCnt) && check_senha(user.senha)){
        FILE *userBase = fopen(pth_userBase, "a");

        fprintf(userBase, "%s %s\n", user.email, user.senha);

        strcpy(usuarios[userCnt].email, user.email);
        strcpy(usuarios[userCnt].senha, user.senha);
        userCnt++;

        fclose(userBase);

        gtk_stack_set_visible_child_name(stack, "view_login");
    }

}

void on_button_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page3");
}

void on_cancelar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page1");
}

void on_localizar_reserva_clicked(GtkWidget *widget, gpointer data) {
    int dia, mes, ano;
    calendario = GTK_CALENDAR(gtk_builder_get_object(builder, "calendar_reserva"));
    
    gtk_calendar_get_date(calendario, &ano, &mes, &dia); mes++; // mes retorna de 0 a 11 por algum motivo

    sprintf(data_calend, "%d-%d-%d", dia, mes, ano);

    strcpy(horario, gtk_combo_box_text_get_active_text(combobox_horarios)); 

    #warning completar if
    if(check_data(data_calend) /* e cpf digitado*/){

        gtk_combo_box_text_remove_all(combobox_salas);

        for(int i = 1; i < MAX_SALAS; i++){
            if (check_disponibilidade(reservas, num_reservas, salas[i].id, data_calend, horario) == 1) {
                gtk_combo_box_text_append_text(combobox_salas, salas[i].nome);
            }
        }

        gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_salas), 0);

        gtk_stack_set_visible_child_name(stack, "page4");
    }

}

void on_voltar_reserva_clicked(GtkWidget *widget, gpointer data) {
    gtk_stack_set_visible_child_name(stack, "page0");
}

void on_button_confirmar_clicked(GtkWidget *widget, gpointer data) {
    int id_sala;
    char *sala_nome = gtk_combo_box_text_get_active_text(combobox_salas); 

    for(int i = 1; i < MAX_SALAS; i++){
        if(strcmp(salas[i].nome, sala_nome) == 0){
            id_sala = salas[i].id;
            break;
        }
    }

    Reserva nova_reserva;
    nova_reserva.id_sala = id_sala;
    strcpy(nova_reserva.data, data_calend);
    strcpy(nova_reserva.horario, horario);


    reservas[num_reservas] = nova_reserva;
    num_reservas++;

    dbgi(num_reservas);
    dbgi(reservas[num_reservas-1].id_sala);


    FILE *arquivo = fopen(pth_reservas, "a");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de reservas. Verifique se ele se encontra em res/");
        puts("Pressione qualquer tecla para fechar..."); getchar();

        exit(1);
    }

    fprintf(arquivo, "%d %s %s\n", id_sala, data_calend, horario);
    fclose(arquivo);

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

    ler_base_de_usuarios
    (pth_userBase, usuarios, &userCnt);
    
    ler_relacao_das_salas   
    (pth_salas, salas);
    
    ler_reservas            
    (pth_reservas, reservas, &num_reservas);

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("../res/hemir.ui");

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

    combobox_horarios = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_horarios"));
    combobox_salas =    GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "combo_box_salas"));


    for(int i = 0; i < 20; i++){
        char *index = malloc(3);
        snprintf(index, sizeof(index), "%d", i);

        gtk_combo_box_text_append(combobox_horarios, index, horarios[i]);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(combobox_horarios), 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}