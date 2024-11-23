#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SZ 256

char input[BUF_SZ];

float getNumValido(char *tipo){
    float num;
    char *charFinal;
    int ok;

    ok = 1;
    do{
        if(!ok)
            puts("Digite um numero");

        strcpy(input, "");
        fgets(input, BUF_SZ, stdin);

        if(strcmp(tipo, "int") == 0)
            num = strtol(input, &charFinal, 10);
        else if(strcmp(tipo, "float") == 0)
            num = strtof(input, &charFinal);
        else{
            fputs("Tipo invalido", stderr);
            exit(1);
        }

        ok = ( (strcmp(charFinal, "\n\0") == 0) && (num != 0) );
    }while(!ok);

    return num;
}

int main(){

    FILE *file;
    int qtdAlunos = 0;

    file = fopen("notas.txt", "w");
    if(file == NULL){
        puts("Erro ao criar/abrir o arquivo");
        exit(1);
    }
    
    puts("Digite a quantidade de alunos");
    
    qtdAlunos = getNumValido("int");

    for(int i = 1; i <= qtdAlunos; i++){
        float notas[2], media;

        for(int j = 1; j <= 2; j++){
            int ok;
            
            printf("Digite %da nota do aluno %d\n", j, i);

            ok = 1;
            do{
                if(!ok){
                    puts("Digite um numero entre 0 e 10");
                }
                
                notas[j-1] = getNumValido("float");

                ok = (0 <= notas[j-1] && notas[j-1] <= 10);
            }while(!ok);
        }

        media = (notas[0] + notas[1]) / 2;
    
        fprintf(file, "Aluno %d: 1a nota = %.2f, 2a nota = %.2f, media = %.2f\n", 
                i, notas[0], notas[1], media);
    }

    fclose(file);

    putchar('\n');

    file = fopen("notas.txt", "r");

    if(file == NULL){
        puts("Erro ao abrir o arquivo");
        exit(1);
    }

    char str[BUF_SZ];
    while(fgets(str, BUF_SZ, file) != NULL){
        fputs(str, stdout);
    }

    fclose(file);
    
}