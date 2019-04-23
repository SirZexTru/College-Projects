#include <stdio.h>
#include <locale.h>

int duracell[5], topo = 0;

void menu(void);

void empilha(void)
{
    int numero;
    if (duracell[4] == topo - 1)
    {
        printf("\nNão é possível adicionar o item, pilha cheia.\n");
    }
    else
    {
        printf("Digite o número que deseja empilhar: ");
        scanf("%i", &duracell[topo]);
        topo++;
        system("cls");
    }
}

void despilha(void)
{
    if (duracell[0] == topo)
    {
        printf("\nNão é possível remover o item, pilha vazia.\n");
    }
    else
    {
        duracell[topo] = NULL;
        topo--;
        system("cls");
    }
}

void menu(void)
{
    int escolha = 1;
    while (escolha != 0)
    {
        printf("[");
        for (int i; i < 5; i++)
        {
            printf(" %i ", duracell[i]);
        }
        printf("]");
        printf("\n\nO que deseja fazer?\n1 - Empilhar\n2 - Despilhar\n0 - Sair\n");
        scanf("%i", &escolha);

        switch (escolha)
        {
        case 0:
            return 0;
            break;

        case 1:
            empilha();
            break;
        
        case 2:
            despilha();
            break;
        }
    }
}

void main(void)
{
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}