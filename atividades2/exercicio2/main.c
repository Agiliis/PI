#include <stdio.h>
#include <stdlib.h>

#define BUF_SZ 256

FILE *file;
char texto[BUF_SZ];
int charCnt = 0;

int main(){

    file = fopen("arquivo.txt", "w+");
    if(file == NULL){
        puts("Erro ao criar/ler o arquivo");
        exit(1);
    }

    puts("Digite um texto para gravar no arquivo: ");
    fgets(texto, BUF_SZ, stdin);

    fputs(texto, file);

    rewind(file);

    while(fgetc(file) != EOF) charCnt++;

    // Pra desconsiderar o caractere de nova linha
    // charCnt--;

    printf("Numero de caracteres: %d\n", charCnt);

    fclose(file);

}