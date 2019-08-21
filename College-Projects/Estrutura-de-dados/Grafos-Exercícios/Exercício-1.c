#include <stdio.h>

int main(void)
{
    int vertices = 0, menu = 3;
    printf("Informe quantos vertices existem: ");
    scanf("%i", &vertices);
    int matriz[vertices][vertices];
    
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
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
        int i, j;
        printf("Digite 1, 2 ou 0: ");
        scanf("%i", &menu);
        printf("Digite os valores das arestas: ");
        scanf("%i", &i);
        i = i < (vertices - 1) ? i : (vertices - 1);
        scanf("%i", &j);
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