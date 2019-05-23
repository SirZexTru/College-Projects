#include <stdio.h>
#include <locale.h>

int topo = 0;
char letra, pilha[10];

void empilha(int repeticao);
void desempilha(int repeticao);

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    int matriz[15][15] = {
        //a  b  c  d  e  f  g  h  i  j  k  l  m  n  o
        { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    };
    
    // for (int m = 0; m < 15; m++)
    // {
    //     printf("[");
    //     for (int n = 0; n < 15; n++)
    //     {
    //         printf(" %i", matriz[m][n]);
    //     }
    //     printf(" ] \n");
    // }

    // TODO: implementar busca

    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            if (matriz[i][j] = 1)
            {
                empilha(1);
                printf("\n%i com %i", i, j);
            }
            else
            {
                desempilha(topo);
            }
        }
    }
    
    getch();
    system("cls");
}

void empilha(int repeticao)
{
    for (int i; i < repeticao; i++)
    {    
        pilha[topo] = letra;
        topo++;
    }
}

void desempilha(int repeticao)
{
    for (int i; i <= repeticao; i++)
    {
        pilha[topo - 1] = 0;
        topo--;
    }
}
