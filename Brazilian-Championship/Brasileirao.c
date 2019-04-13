// Aluno: Gustavo Ausechi Furlan
// RA: 2576
// Turma: ECON3S
// Algoritmo que simula a execução do Campeonato Brasileiro.

// Objetivo: simular as 38 rodadas do Campeonato Brasileiro de futebol, apresentando os seguintes dados de cada time:
// - Colocação
// - Nome
// - Pontos (P)
// - Jogos (J)
// - Vitórias (V)
// - Empates (E)
// - Derrotas (D)
// - Gols feitos (GP)
// - Gols recebidos (GC)
// - Saldo de Gols (SG)

// TODO: Fazer primeira rodada manual
// TODO: Fazer primeira rodada automatizada
// TODO: Fazer 38 rodadas automatizadas

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>

struct tableColumns
{
    char* teamName[20], teamInitial[20], bestFour[4], worstFour[4], champion;
    int id[20], position[20], points[20], games[20], wins[20], draw[20], loses[20], goalsDone[20], goalsReceived[20], goalsBalance[20];
};
struct tableColumns finalResultTable;

struct roundData
{
    char team1, team2;
    int round;
};
struct roundData rounds[380];

int insertTeamDataOnTable(void)
{
    finalResultTable.teamName[0] = "Atlético-MG";
    finalResultTable.teamName[1] = "Atlético-PR";
    finalResultTable.teamName[2] = "Avaí";
    finalResultTable.teamName[3] = "Bahia";
    finalResultTable.teamName[4] = "Botafogo";
    finalResultTable.teamName[5] = "Ceará";
    finalResultTable.teamName[6] = "Chapecoense";
    finalResultTable.teamName[7] = "Corinthians";
    finalResultTable.teamName[8] = "Cruzeiro";
    finalResultTable.teamName[9] = "CSA";
    finalResultTable.teamName[10] = "Flamengo";
    finalResultTable.teamName[11] = "Fluminense";
    finalResultTable.teamName[12] = "Fortaleza";
    finalResultTable.teamName[13] = "Goiás";
    finalResultTable.teamName[14] = "Grêmio";
    finalResultTable.teamName[15] = "Internacional" ;
    finalResultTable.teamName[16] = "Palmeiras";
    finalResultTable.teamName[17] = "Santos";
    finalResultTable.teamName[18] = "São Paulo";
    finalResultTable.teamName[19] = "Vasco";

    for (int i = 0; i < 20; i++)
    {
        finalResultTable.id[i] = i;
    }
}

void matchesLogic(void)
{
    char url[] = "C:\\Users\\gusta\\Documents\\GitHub\\College-Projects\\Brazilian-Championship\\tabela-campeonato.txt", team;
    FILE *table;

    table = fopen(url, "r");
    if (table == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getch();
    }
    else
    {
        // Print file content for checkup
        char c = fgetc(table); 
        while (c != EOF) 
        { 
            printf ("%c", c); 
            c = fgetc(table); 
        }
        getch();
        system("cls");

        int i = 0, a, b;
        while ((fscanf(table, "%s %s %i", rounds[i].team1, rounds[i].team2, &rounds[i].round)) != EOF)
        {
            printf("%s vs %s round: %i", rounds[i].team1, rounds[i].team2, rounds[i].round);
            for (int i = 0; i < 20; i++)
            {
                if (rounds[i].team1 == finalResultTable.teamInitial)
                {
                   a = i; 
                }
                if (rounds[i].team2 == finalResultTable.teamInitial)
                {
                    b = i;
                }
            }
            i++;
        }
    }
}

void roundResultsCalc()
{

}

void reorderArrays()
{
    for (int i = 0; i < 20; ++i) 
    {
        for (int j = i + 1; j < 20; ++j)
        {
            if (finalResultTable.points[i] > finalResultTable.points[j]) 
            {
                int a =  finalResultTable.points[i];
                finalResultTable.points[i] = finalResultTable.points[j];
                finalResultTable.points[j] = a;
            }
        }
    }
} 
int compare(const void * a, const void * b) 
{
    double diff = finalResultTable.points[*(int*)a] - finalResultTable.points[*(int*)b];
    return  (0 < diff) - (diff < 0);
    sortTeamsByPoints(finalResultTable.games);
    sortTeamsByPoints(finalResultTable.wins);
    sortTeamsByPoints(finalResultTable.draw);
    sortTeamsByPoints(finalResultTable.loses);
    sortTeamsByPoints(finalResultTable.goalsDone);
    sortTeamsByPoints(finalResultTable.goalsReceived);
    sortTeamsByPoints(finalResultTable.goalsBalance);
}

int sortTeamsByPoints(int arrayToBeOrdered[])
{
    int perm[20];
    int res[20];
    for (int i = 0; i < 20; i++) 
    {
        perm[i] = i;
    }
    qsort (perm, 20, sizeof(int), compare);
    for (int i = 0; i < 20; i++) {
        res[i] = arrayToBeOrdered[perm[i]];
    }
}

void printResults(void)
{
    printf("Pos | Nome | P | J | V | E | D | GP | GC | SG |\n");
    for (int i = 0; i < 20; i++)
    {
        printf("---------------------------------------------\n");
        printf("%i | ", i + 1);
        printf("%s | ", finalResultTable.teamInitial[i]);
        printf("%i | ", finalResultTable.points[i]);
        printf("%i | ", finalResultTable.games[i]);
        printf("%i | ", finalResultTable.wins[i]);
        printf("%i | ", finalResultTable.draw[i]);
        printf("%i | ", finalResultTable.loses[i]);
        printf("%i | ", finalResultTable.goalsDone[i]);
        printf("%i | ", finalResultTable.goalsReceived[i]);
        printf("%i |\n", finalResultTable.goalsBalance[i]);
    }
    printf("---------------------------------------------");

    printf("\n\n----------------------------------------\n");
    printf("Times que vão para a libertadores: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("%i - %s\n", i+1, finalResultTable.bestFour[i]);
    }
    printf("----------------------------------------\n");
    printf("Times que serão rebaixados: \n");
    for (int i = 0; i < 4; i++)
    {
        printf("%i - %s\n", i+1, finalResultTable.worstFour[i]);
    }
    printf("----------------------------------------\n\n");

    printf("O campeão é: %s\n\n", finalResultTable.champion);
    printf("----------------------------------------\n\n");
    printf("Pressione enter para finalizar...");
    getch();
}

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    insertTeamDataOnTable();
    matchesLogic();
    roundResultsCalc();
    // compare();
    printResults();
}
