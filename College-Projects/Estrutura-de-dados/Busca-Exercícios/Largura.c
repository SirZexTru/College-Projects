#include <stdio.h>

int fila[5], posicao = 0, guarda, ponteiro = 0;

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
        fila[posicao] = ponteiro;
        posicao++;
        system("cls");
    }
}

void desenfileira(void)
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
        printf("\n\nO que deseja fazer?\n1 - Enfileirar\n2 - desenfileirar\n0 - Sair\n");
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
                desenfileira();
                break;
        }
    }
}

void main(void) {
    int matriz[15][15] = {
           //a  b  c  d  e  f  g  h  i  j  k  l  m  n  o
    /*a 00*/  { 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    /*b 01*/  { 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    /*c 02*/  { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    /*d 03*/  { 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    /*e 04*/  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    /*f 05*/  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
    /*g 06*/  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
    /*h 07*/  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
    /*i 08*/  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
    /*j 09*/  { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
    /*k 10*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
    /*l 11*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
    /*m 12*/  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
    /*n 13*/  { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
    /*o 14*/  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    };

    int i = 0;
    while (i != 1)
    {
        menu();
    }
}
