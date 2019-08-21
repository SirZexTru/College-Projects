#include <stdio.h>

struct dadosDoAluno
{
    const char *nome;
    const char *turma;
    const char *turno;
    int ra;
    int notas[2][2];
};

struct dadosDoAluno registroDoAluno[6];

void menu(int i)
{
    int escolha;
    printf("\nEscolha a opção desejada: ");
    printf("\n1 - Cadastrar aluno");
    printf("\n2 - Ver alunos cadastrados");
    printf("\n3 - Sair");
    scanf("%i", &escolha);
    switch (escolha)
    {
        case 1:
            dadosDoAluno(i);
            notas(i);
            break;
        case 2:
            mostrarAlunos(i);
        case 3:
            sair();
            break;
    }
}

void dadosDoAluno(int i)
{
    printf("\nPor favor, insira os dados do %i aluno: ", i+1);
    printf("\nNome do aluno: ");
    scanf("%s", &registroDoAluno[i].nome);
    printf("\nTurma: ");
    scanf("%s", &registroDoAluno[i].turma);
    printf("\nTurno: ");
    scanf("%s", &registroDoAluno[i].turno);
    printf("\nRA: ");
    scanf("%s", &registroDoAluno[i].ra);
    printf("\nDados salvos com sucesso.");
}

void notas(int i)
{
    printf("\nPor favor, informe as notas do %i aluno", i + 1);
    for (int j = 0; j < 2; j++)
    {
        for (int k = 0; k < 2; k++)
        {
            printf("\n%i bimestre - %i nota: ", j + 1, k+1);
            scanf("%i", &registroDoAluno[i].notas[j][k]);
        }
    }
    printf("\nNotas cadastradas com sucesso.");
}

void mostrarAlunos(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("\nNome: %s", registroDoAluno[j].nome);
        printf("\nTurma: %s");
        printf("\nTurno: %s");
        printf("\nRA: %i");
    }
    for (int k = 0; k < 2; k++)
    {
        for (int a = 0; a < 2; a++)
        {
            printf("\n%i bimestre - %i nota: ", k + 1, a + 1);
            scanf("%i", &registroDoAluno[i].notas[k][a]);
        }
    }
}

void sair()
{
    return 0;
}

int main(void)
{
    int j;
    printf("Bem vindo ao sistema de cadastro de aluno!");
    printf("\nQuantos alunos serão cadastrados? ");
    scanf("%i", &j);
    for (int i = 0; i <= j; i++)
    {
        menu(i);
    }
    return 0;
}