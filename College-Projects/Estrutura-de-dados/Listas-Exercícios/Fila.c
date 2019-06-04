#include <stdio.h>
#include <locale.h>

int fila[5], posicao = 0, guarda;

void menu(void);
void reordena(void);

void enfileira(void)
{
    if (posicao == 5)
    {
        printf("\nNão é possível adicionar o item, fila cheia.\n");
        getch();
        system("cls");
    }
    else
    {
        printf("\nDigite o número que deseja empilhar: ");
        scanf("%i", &fila[posicao]);
        posicao++;
        system("cls");
    }
}

void desfileira(void)
{
    if (posicao == 0)
    {
        printf("\nNão é possível remover o item, fila vazia.\n");
        getch();
        system("cls");
    }
    else
    {
        fila[0] = 0;
        reordena();
        getch();
        system("cls");
    }
}

void reordena(void)
{
    int i = 0;
    guarda = posicao;
    while (i != guarda)
    {
        fila[i] = fila[i + 1];
        i++;
        posicao--;
    }
    printf("\nPosição: %i", posicao);
}

void menu(void)
{
    int escolha = 5;
    while (escolha != 0)
    {
        printf("[");
        for (int i = 0; i < 5; i++)
        {
            printf(" %i ", fila[i]);
        }
        printf("]");
        printf("\n\nO que deseja fazer?\n1 - Enfileirar\n2 - Desfileirar\n0 - Sair\n");
        scanf("%i", &escolha);

        switch (escolha)
        {
            case 0:
                return 0;
                break;
            case 1:
                enfileira();
                break;
            case 2:
                desfileira();
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
