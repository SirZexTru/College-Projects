#include <stdio.h>
#include <locale.h>

int topo = 0;
char letra, pilha[10];

void empilha(int repeticao);
void desempilha(int repeticao);
void visitante(void);

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

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    
    // for (int m = 0; m < 15; m++)
    // {
    //     printf("[");
    //     for (int n = 0; n < 15; n++)
    //     {
    //         printf(" %i", matriz[m][n]);
    //     }
    //     printf(" ] \n");
    // }

    visitante();
    getch();
    system("cls");
}

void visitante(void)
{
    int i = 0, j = 0;
    if (matriz[i][j] == 1)
    {
        empilha(1);
        visitante();
        matriz[i][j];
    }
    else if (matriz[i+1][j] == 1)
    {
        empilha(1);
        visitante();
        matriz[i+1][j] = 0;
    }
    else if (matriz[i][j+1] == 1)
    {
        empilha(1);
        visitante();
        matriz[i][j+1] = 0;
    }
    else
    {
        desempilha(topo);
    }
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
