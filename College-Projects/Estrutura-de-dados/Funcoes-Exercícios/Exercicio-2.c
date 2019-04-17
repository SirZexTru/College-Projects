#include <stdio.h>

unsigned int max = 0;
int i = 0, j = 0;
float maior, menor;

float biggerAndSmaller(float a[], int max)
{
    for (j = 0; j < max; j++)
    {
        if (maior < a[j])
        {
            maior = a[j];
        }
        else if (menor > a[j])
        {
            menor = a[j];
        }
    }
}

main()
{
    printf("\nQuantos números serão inseridos: ");
    scanf("%i", &max);
    float numero[max];
    for (i = 0; i < max; i++)
    {
        printf("\nDigite %i valor: ", i + 1);
        scanf("%f", &numero[i]);
    }
    biggerAndSmaller(numero, max);
    printf("\nMaior: %f", maior);
    printf("\nMenor: %f", menor);
    getch();
}