#include <stdio.h>

int main(void)
{
    float matriz[2][2], valor, maior = 0, media, soma;
    int  i, j;
    
    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            printf("Digite o valor a ser inserido na matriz");
            scanf("%f", &valor);
            matriz[i][j] = valor;
            printf("Matriz[%d][%d]", i, j);

            if (matriz[i][j] > maior)
            {
                maior = matriz[i][j];
            }

            soma = soma + matriz[i][j];
        }
    }
    media = soma/9;
}