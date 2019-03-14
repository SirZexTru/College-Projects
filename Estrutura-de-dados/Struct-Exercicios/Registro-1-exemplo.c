#include <stdio.h>

int main(void)
{
    struct fichaAluno
    // Posso usar typedef e dar um nome só após fechar o }, antes do ;
    {
        char nome[50];
        char disciplina[30];
        float notaPrimeiraProva;
        float notaSegundaProva;
    };
    struct fichaAluno aluno;
    printf("Cadastro de Aluno");
    printf("Nome do aluno: ");
    scanf("%s", &aluno.nome);
    printf("\nDisciplina: ");
    scanf("%s", &aluno.disciplina);
    printf("\nNota da primeira prova: ");
    scanf("%f", &aluno.notaPrimeiraProva);
    printf("\nNota da segunda prova: ");
    scanf("%f", &aluno.notaSegundaProva);
    printf("\nApresentando os dados:");
    printf("\nNome: %s", aluno.nome);
    printf("\n");
    printf("\n");
    printf("\n");
}