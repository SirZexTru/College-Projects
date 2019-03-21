#include <stdio.h>

int result;

int factorial(int num)
{
    if (num == 1)
    {
        result = 1;
    }
    else
    {
        result = num * factorial(num - 1);
    }
}

main()
{
    int num;

    printf("Digite o número para calcular seu fatorial: ");
    scanf("%i", &num);
    factorial(num);
    printf("O resultado é: %i", result);
    getch();
}