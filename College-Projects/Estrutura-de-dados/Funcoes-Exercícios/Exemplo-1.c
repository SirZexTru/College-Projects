#include <stdio.h>
#include <locale.h>

int imparPar(int x)
{
    setlocale(LC_ALL, "");
    if (x % 2 == 1)
    {
        printf("%i é í­mpar",x);
    }
    else
    {
        printf("%i é par", x);
    }
    printf("\n\n");
}

main()
{
    setlocale(LC_ALL, "");
    int a, i;
    printf("Digite 10 números: \n");
    for (i=1;i<=10;i++)
    {
        printf("Digite o número %i: \n", i);
        scanf("%i", &a);
        imparPar(a);
    }
}