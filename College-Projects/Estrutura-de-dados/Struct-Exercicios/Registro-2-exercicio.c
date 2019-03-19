#include <stdio.h>
#include <string.h>

typedef struct
    {
        char modelo[30];
        int ano;
        float valor;
        char placa[7];
    }cadastroCarro;

cadastroCarro carro[5];

int main(void)
{   
    int barato = 0, i, j, tamanho = 0;

    for (i = 1; i < 5; i++)
    {
        printf("Cadastro de carros:");
        printf("\n\nModelo: ");
        scanf("%s", &carro[i].modelo);
        printf("\nAno: ");
        scanf("%i", &carro[i].ano);
        printf("\nValor: ");
        scanf("%f", &carro[i].valor);
        printf("\nPlaca: ");
        scanf("%s", &carro[i].placa);

        tamanho = strlen(carro[i].modelo);
        if (tamanho > strlen(carro[4].modelo))
        {
            carro[4].ano = carro[i].ano;
        }
        // if (carro[i].valor > barato) 
        // {
        //     barato = carro[i].valor;
        //     strcpy(carro[4].modelo, carro[i].modelo);
        //     carro[4].ano = carro[i].ano;
        // }
        system("cls");
    }

    // printf("\nApresentando os dados:");
    // printf("\nModelo do carro: %s", carro[4].modelo);
    // printf("\nAno do carro: %i", carro[4].ano);

    printf("Ano do carro com maior nome: %i", carro[4].ano);
    getch();
}