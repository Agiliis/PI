#include <stdio.h>

typedef struct {
    char nome[50];
    float renda_mensal;
    int ano_nascimento;
    int possui_carro;
} Cliente;

int main() {

    int n;
    printf("Digite o número de clientes: ");
    scanf("%d", &n);

    Cliente clientes[n];

  
    for (int i = 0; i < n; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: ");
        getchar(); // Limpa o buffer
        fgets(clientes[i].nome, 50, stdin);
        printf("Renda mensal: ");
        scanf("%f", &clientes[i].renda_mensal);
        printf("Ano de nascimento: ");
        scanf("%d", &clientes[i].ano_nascimento);
        printf("Possui carro (1 - Sim, 0 - Não): ");
        scanf("%d", &clientes[i].possui_carro);
    }

    
    float soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += clientes[i].renda_mensal;
    }
    float media_renda = soma / n;


    int acima_media = 0;
    int com_carro = 0;
    int nascidos_60_80 = 0;

 
    for (int i = 0; i < n; i++) {
        if (clientes[i].renda_mensal > media_renda) {
            acima_media++;
        }
        if (clientes[i].possui_carro) {
            com_carro++;
        }
        if (clientes[i].ano_nascimento >= 1960 && clientes[i].ano_nascimento <= 1980) {
            nascidos_60_80++;
        }
    }


    printf("Quantidade de clientes com renda mensal acima da média: %d\n", acima_media);
    printf("Quantidade de clientes com carro: %d\n", com_carro);
    printf("Quantidade de clientes nascidos entre 1960 e 1980: %d\n", nascidos_60_80);

    return 0;
}
