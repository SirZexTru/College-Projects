#include <stdio.h>

float total;

float multiplicacao(float a, float b)
{
    total = a*b;
}

main()
{
    float a, b;

    printf("Digite o primeiro número: ");
    scanf("%d", &a);
    printf("Digite o segundo número: ");
    scanf("%d", &b);
    multiplicacao(a,b);
    printf("O resultado é: %d", total);
}