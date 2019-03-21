
// Exercises from the link:
// https://www.kelvinsantiago.com.br/exercicios-resolvidos-em-linguagem-c-lista-d/

/*
#include <stdio.h>

main()
{
    int vetor[5], numero, cont, posicao = 0 ;

    while (posicao < 5)
    {
        printf("Digite o n�mero da matr�cula: ");
        scanf("%d", &numero);
 
        if (posicao == 0)
        {
            vetor[posicao] = numero;
            printf("Seu n�mero �: %d\n", vetor[posicao]);
            posicao++;
        }
        else
        {
            for (cont = 0; (cont < posicao) && (vetor[cont]!= numero); cont++);

            if (cont >= posicao)
            {
                vetor[posicao] = numero;
                printf("%d\n",vetor[posicao]);
                posicao++;
            }
        }
    }
    getch();
    return 0;
}
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

main()
{
    int number, index = 10;
    char array[5];

    printf("Digite seu n�mero: ");
    scanf("%i", &number);

    while (number != 999)
    {
        if (index == 4)
        {
            printf("It's over bois\nyour number is");
        }
    }
}