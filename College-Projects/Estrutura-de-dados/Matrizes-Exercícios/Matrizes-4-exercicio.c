#include <stdio.h>
#include <conio.h>

main(void)
{
    float nota, matriz[5][4], media, soma;
    int aluno, bimestre;

    for (aluno=0; aluno<5; aluno++)
    {
        for (bimestre=0; bimestre<4; bimestre++)
        {
            printf("Digite a nota do %i bimestre do %i aluno: ", bimestre + 1, aluno + 1);
            scanf("%f", &nota);
            matriz[aluno][bimestre] = nota;

            soma = soma + matriz[aluno][bimestre];
        }
        media = soma/4;
        soma = 0;
            
        printf("A media do %i aluno e: %.2f.\n", aluno + 1, media);
    }
    getch();
}