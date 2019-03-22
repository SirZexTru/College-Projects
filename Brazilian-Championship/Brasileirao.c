// Gustavo Ausechi Furlan
// RA: 2576
// ECON3S
// Algoritmo que simula a execu��o do Campeonato Brasileiro

// Objetivo: simular as 38 rodadas do Campeonato Brasileiro de futebol, apresentando os seguintes dados de cada time:
// - Coloca��o
// - Nome
// - Pontos (P)
// - Jogos (J)
// - Vit�rias (V)
// - Empates (E)
// - Derrotas (D)
// - Gols feitos (GP)
// - Gols recebidos (GC)
// - Saldo de Gols (SG)

// 1: Construir tabela de resultados e preencher nomes dos times
// 2: Fazer primeira rodada manual
// 3: Fazer primeira rodada automatizada
// 4: Fazer 38 rodadas automatizadas

#include <stdio.h>
#include <conio.h>

void insertTeamNamesOnTable(void);
void adversariesLogic(void);
void roundResultsCalc(void);

struct tableColumns
{
    char teamName[20];
    int position[20], points[20], games[20], wins[20], draw[20], loses[20], goalsDone[20], goalsReceived[20], goalsBalance[20];
};
struct tableColumns finalResultTable;

void main()
{
    insertTeamNamesOnTable();
    for (int i=0; i<20; i++)
    {
        // TODO: Implement archive ".csv" to show the the results
        printf("%s\n", finalResultTable.teamName[i]);
        printf("----------------");
    }
    getch();
}

void insertTeamNamesOnTable(void)
{
    finalResultTable.teamName[0] = "Atl�tico - MG";
    finalResultTable.teamName[1] = "Atl�tico - PR";
    finalResultTable.teamName[2] = "Ava�";
    finalResultTable.teamName[3] = "Bahia";
    finalResultTable.teamName[4] = "Botafogo";
    finalResultTable.teamName[5] = "Cear�";
    finalResultTable.teamName[6] = "Chapecoense";
    finalResultTable.teamName[7] = "Corinthians";
    finalResultTable.teamName[8] = "Cruzeiro";
    finalResultTable.teamName[9] = "CSA";
    finalResultTable.teamName[10] = "Flamengo";
    finalResultTable.teamName[11] = "Fluminense";
    finalResultTable.teamName[12] = "Fortaleza";
    finalResultTable.teamName[13] = "Goi�s";
    finalResultTable.teamName[14] = "Gr�mio";
    finalResultTable.teamName[15] = "Internacional" ;
    finalResultTable.teamName[16] = "Palmeiras";
    finalResultTable.teamName[17] = "Santos";
    finalResultTable.teamName[18] = "S�o Paulo";
    finalResultTable.teamName[19] = "Vasco";
}

void adversariesLogic(void)
{
    finalResultTable.teamName[0], finalResultTable.teamName[1];
}

void roundResultsCalc(void)
{
    for (int i=0; i<=38; i++)
    {
        // TODO: Calculate all results and save the values
        finalResultTable.games[0];
    }
}
