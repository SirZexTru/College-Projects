#include <stdio.h>

typedef struct
    {
        int codigo;
        char nome[30];
        float valor;
        int quantidade;
    }cadastroProdutos;

cadastroProdutos produto[100];

int main(void)
{   
    for (int i=1; i<4; i++)
    {
        printf("Cadastro de Aluno");
        printf("Codigo do produto: ");
        scanf("%s", &produto[i].codigo);
        printf("\nNome do produto: ");
        scanf("%s", &produto[i].nome);
        printf("\nValor da unidade do produto: ");
        scanf("%f", &produto[i].valor);
        printf("\nQuantidade do produto em estoque: ");
        scanf("%f", &produto[i].quantidade);
    }
    for (int i=1; i<3; i++)
    {
        printf("\nApresentando os dados:");
        printf("\nCodigo do produto: %s", produto[i].codigo);
        printf("\n");
        printf("\n");
        printf("\n");
    }
}