#include <stdio.h>

typedef struct
    {
        char nome[50];
        char disciplina[30];
        float notaPrimeiraProva;
        float notaSegundaProva;
    }cadastroAluno;

cadastroAluno aluno;

int main(void)
{   
    for (int i=1; i<4; i++)
    {
        printf("Cadastro de Aluno");
        printf("Nome do aluno: ");
        scanf("%s", &aluno.nome);
        printf("\nDisciplina: ");
        scanf("%s", &aluno.disciplina);
        printf("\nNota da primeira prova: ");
        scanf("%f", &aluno.notaPrimeiraProva);
        printf("\nNota da segunda prova: ");
        scanf("%f", &aluno.notaSegundaProva);
    }
    
    printf("\nApresentando os dados:");
    printf("\nNome: %s", aluno.nome);
    printf("\n");
    printf("\n");
    printf("\n");
}