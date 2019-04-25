#include <stdio.h>
#include <locale.h>

int duracell[5], topo = 0;

void menu(void);

void empilha(void)
{
    if (topo == 5)
    {
        printf("\nNão é possível adicionar o item, pilha cheia.\n");
        getch();
        system("cls");
    }
    else
    {
        printf("\nDigite o número que deseja empilhar: ");
        scanf("%i", &duracell[topo]);
        topo++;
        system("cls");
    }
}

void despilha(void)
{
    if (topo == 0)
    {
        printf("\nNão é possível remover o item, pilha vazia.\n");
        getch();
        system("cls");
    }
    else
    {
        duracell[topo - 1] = 0;
        topo--;
        system("cls");
    }
}

void menu(void)
{
    int escolha = 5;
    while (escolha != 0)
    {
        printf("[");
        for (int i = 0; i < 5; i++)
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