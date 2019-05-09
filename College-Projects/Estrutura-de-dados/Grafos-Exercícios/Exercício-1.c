#include <stdio.h>

// Criar um codigo onde o usuario defina qunatos vertices ele possui, e quantas e quais adjacencias ele possui,
// construindo assim uma matriz booleana, onde as celulas que possuem "1" representam os vertices que se ligam

int main(void)
{
    int vertices = 0, menu = 3;
    printf("Informe quantos vertices existem: ");
    scanf("%i", &vertices);
    int matriz[vertices][vertices];
    
    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
        {
            matriz[i][j] = 0;
        }  
    }
    system("cls");
    
    for (int m = 0; m < vertices; m++)
    {
        printf("[");
        for (int n = 0; n < vertices; n++)
        {
            printf(" %i", matriz[m][n]);
        }
        printf(" ] \n");
    }
    
    while (menu != 0)
    {
        size_t i, j;
        printf("Digite 1, 2 ou 0: ");
        scanf("%i", &menu);
        printf("Digite os valores das arestas: ");
        scanf("%zu", &i);
        i = i < (vertices - 1) ? i : (vertices - 1);
        scanf("%zu", &j);
        j = j < (vertices - 1) ? j : (vertices - 1);
        
        switch (menu)
        {
        case 1:
            matriz[i][j] = 1;
            matriz[j][i] = 1;
            break;
        case 2:
            matriz[i][j] = 0;
            matriz[j][i] = 0;
            break;
        }
    }

    return 0;
}