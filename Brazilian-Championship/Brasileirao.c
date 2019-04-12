// Gustavo Ausechi Furlan
// RA: 2576
// ECON3S
// Algoritmo que simula a execução do Campeonato Brasileiro

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

// 1: Construir tabela de resultados e preencher nomes dos times
// 2: Fazer primeira rodada manual
// 3: Fazer primeira rodada automatizada
// 4: Fazer 38 rodadas automatizadas

#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

struct tableColumns
{
    char* teamName[20], teamInitial[20], bestFour[4], worstFour[4], champion;
    int id[20], position[20], points[20], games[20], wins[20], draw[20], loses[20], goalsDone[20], goalsReceived[20], goalsBalance[20], matchesPerRound[20];
};
struct tableColumns finalResultTable;

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

    finalResultTable.teamInitial[0] = "ATM";
    finalResultTable.teamInitial[1] = "ATP";
    finalResultTable.teamInitial[2] = "AVA";
    finalResultTable.teamInitial[3] = "BAH";
    finalResultTable.teamInitial[4] = "BOT";
    finalResultTable.teamInitial[5] = "CEA";
    finalResultTable.teamInitial[6] = "CHA";
    finalResultTable.teamInitial[7] = "COR";
    finalResultTable.teamInitial[8] = "CRU";
    finalResultTable.teamInitial[9] = "CSA";
    finalResultTable.teamInitial[10] = "FLA";
    finalResultTable.teamInitial[11] = "FLU";
    finalResultTable.teamInitial[12] = "FOR";
    finalResultTable.teamInitial[13] = "GOI";
    finalResultTable.teamInitial[14] = "GRE";
    finalResultTable.teamInitial[15] = "INT";
    finalResultTable.teamInitial[16] = "PAL";
    finalResultTable.teamInitial[17] = "SAN";
    finalResultTable.teamInitial[18] = "SPA";
    finalResultTable.teamInitial[19] = "VAS";

    for (int i = 0; i < 20; i++)
    {
        finalResultTable.id[i] = i;
    }
}

int matchesLogic(void)
{
    char url[] = "C:\\Users\\gusta\\Documents\\GitHub\\College-Projects\\Brazilian-Championship\\tabela-campeonato.txt";
    FILE *table;

    table = fopen(url, "r");
    if (table == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        getch();
    }
    // else
    // {
    //     while (fscanf(table) != EOF)
    //     {
    //         finalResultTable.matchesPerRound = 
    //     }
    // }
}

int roundResultsCalc(void)
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
    // Function to reorder elements of arr[] according 
    // to index[] 
    // void reorder(int arr[], int index[], int n) 
    // { 
    // int temp[n]; 
  
    // // arr[i] should be present at index[i] index 
    // for (int i=0; i<n; i++) 
    //     temp[index[i]] = arr[i]; 
  
    // // Copy temp[] to arr[] 
    // for (int i=0; i<n; i++) 
    // {  
    //    arr[i]   = temp[i]; 
    //    index[i] = i; 
    // } 
} 

void printResults(void)
{
    printf("Pos |    Nome    | P | J | V | E | D | GP | GC | SG |\n");
    for (int i = 0; i < 20; i++)
    {
        printf("-----------------------------------------------------\n");
        printf(" %i | ", i + 1);
        printf("%s | ", finalResultTable.teamName[i]);
        printf("%i | ", finalResultTable.points[i]);
        printf("%i | ", finalResultTable.games[i]);
        printf("%i | ", finalResultTable.wins[i]);
        printf("%i | ", finalResultTable.draw[i]);
        printf("%i | ", finalResultTable.loses[i]);
        printf("%i | ", finalResultTable.goalsDone[i]);
        printf("%i | ", finalResultTable.goalsReceived[i]);
        printf("%i |\n", finalResultTable.goalsBalance[i]);
    }

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
    printf("Pressione Enter para encerrar o programa...");
    getch();
}

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    insertTeamDataOnTable();
    matchesLogic();
    roundResultsCalc();
    printResults();
}
