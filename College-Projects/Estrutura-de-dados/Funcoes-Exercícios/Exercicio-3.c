#include <stdio.h>

int operacao, i=0;

struct fichaAluno
    {
        char nome[100];
        int ra;
        float nota;
    };
    struct fichaAluno aluno[100];

int menu()
{
    printf("\nQual operacao deseja realizar?");
    printf("\n1 - Incluir");
    printf("\n2 - Listar");
    printf("\n3 - Sair\n");
    scanf("%i", &operacao);
    system("cls");
    switch (operacao)
    {
    case 1:
        i++;
        insert();
        break;
    case 2:
        list();
        break;
    case 3:
        return 0;
        break;
    }
}

int insert()
{
    printf("Digite o nome do aluno: ");
    scanf("%s", &aluno[i].nome);
    printf("\nDigite o RA do aluno: ");
    scanf("%i", &aluno[i].ra);
    printf("\nDigite a nota do aluno: ");
    scanf("%f", &aluno[i].nota);
    system("cls");
    printf("Aluno cadastrado com sucesso.");
    printf("\nPressione enter para voltar para a tela de escolha de acoes.");
    getch();
    system("cls");
    menu();
}

int list()
{
    for (int j=0; j<=i; j++)
    {
        printf("\n%i Aluno: Nome: %s - RA: %i - Nota: %f", j+1, aluno[j].nome, aluno[j].ra, aluno[j].nota);
    }
    printf("\n\n\nTodos os alunos foram listados com sucesso.");
    printf("\nPressione enter para voltar para a tela de escolha de acoes");
    getch();
    menu();
}

main()
{  
    printf("Bem vindo ao sistema de registro de alunos!");
    menu();
    return 0;
}