#include <stdio.h>

int a = 0, b = 1; 
int r = 1;
int calculo(int n)
{
    printf("%i", r);
    for (int i = 0; i < (n - 1); i++)
    {
        {
            r += a;
            a = b;
            b = r;
            printf(", %i", r);
        }     
    }
}

int main(void)
{
    int n;
    printf("Digite o numero a ser calculado: ");
    scanf("%i", &n);
    calculo(n
    );
    getch();
    return 0;
}
