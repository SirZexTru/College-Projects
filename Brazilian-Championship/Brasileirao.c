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
    char* teamName[20], teamInitials[20];
    int position[20], points[20], games[20], wins[20], draw[20], loses[20], goalsDone[20], goalsReceived[20], goalsBalance[20], gameRound;
};
struct tableColumns finalResultTable;

int insertTeamNamesOnTable(void)
{
    finalResultTable.teamName[0] = "Atlético - MG";
    finalResultTable.teamName[1] = "Atlético - PR";
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
}

void mapTeamInitials(void)
{
    finalResultTable.teamInitials[0] = "ATP";
    finalResultTable.teamInitials[1] = "ATM";
    finalResultTable.teamInitials[2] = "AVA";
    finalResultTable.teamInitials[3] = "BAH";
    finalResultTable.teamInitials[4] = "BOT";
    finalResultTable.teamInitials[5] = "CEA";
    finalResultTable.teamInitials[6] = "CHA";
    finalResultTable.teamInitials[7] = "COR";
    finalResultTable.teamInitials[8] = "CRU";
    finalResultTable.teamInitials[9] = "CSA";
    finalResultTable.teamInitials[10] = "FLA";
    finalResultTable.teamInitials[11] = "FLU";
    finalResultTable.teamInitials[12] = "FOR";
    finalResultTable.teamInitials[13] = "GOI";
    finalResultTable.teamInitials[14] = "GRE";
    finalResultTable.teamInitials[15] = "INT";
    finalResultTable.teamInitials[16] = "PAL";
    finalResultTable.teamInitials[17] = "SAN";
    finalResultTable.teamInitials[18] = "SPA";
    finalResultTable.teamInitials[19] = "VAS";
}

int adversariesLogic(void)
{
    int roundOne(void)
    {
        char team[20];
        team[0] = "ATP";
        team[1] = "VAS";
        team[2] = "ATM";
        team[3] = "AVA";
        team[4] = "BAH";
        team[5] = "COR";
        team[6] = "CEA";
        team[7] = "CSA";
        team[8] = "CHA";
        team[9] = "INT";
        team[10] = "FLA";
        team[11] = "CRU";
        team[12] = "FLU";
        team[13] = "GOI";
        team[14] = "GRE";
        team[15] = "SAN";
        team[16] = "PAL";
        team[17] = "FOR";
        team[18] = "SPA";
        team[19] = "BOT";
    }
    
    // char url1[] = "C:\\Users\\gusta\\Documents\\GitHub\\College-Projects\\Brazilian-Championship\\clube-nomes.txt";
    // char url2[] = "C:\\Users\\gusta\\Documents\\GitHub\\College-Projects\\Brazilian-Championship\\tabela-campeonato.txt";
    // char *token;
    // FILE* names;
    // FILE* table;
    
    // names = fopen(url1, "r");
    // if (names != NULL)
    // {
	// 	for (int i = 0; i < 20; i++)
	// 	{
	// 		char buf[255];

    //         if (names != NULL)
    //         {
	// 			fgets(buf, 255, (FILE*)names);
    //         }
    //         char* token = NULL;
	// 		char* next_token = NULL;
	// 		token = strtok(buf, ";");
	// 		strcpy(finalResultTable.teamName[i], token);
	// 		token = strtok(NULL, ";");
	// 		strcpy(finalResultTable.teamInitials[i], token);
    //         printf("Iniciais: %s", finalResultTable.teamInitials[i]);
    //     }

    //     table = fopen(url2, "r");
    //     for (int i = 0; i < 380; i++)
    //     {
    //         char buf[256];

    //         if (table != NULL)
    //         {
    //             fgets(buf, 256, (FILE*)table);
    //         }

    //         char* token = NULL;
    //         char* next_token = NULL;
    //         char* homeTeam = NULL;
    //         char* visitorTeam = NULL;

    //         token = strtok(buf, ";");
    //         homeTeam = token;
    //         token = strtok(NULL, ";");
    //         visitorTeam = token;
    //         token = strtok(NULL, ";");
    //         fscanf(token, "%d", &finalResultTable.gameRound);
    //         printf("%i", finalResultTable.gameRound);
    //     }
    // }
    // else (names == NULL);
    // {
    //     printf("Não foi possível abrir o arquivo\n");
    //     getch();
    //     return 0;
    // }
}

int roundResultsCalc(void)
{

}

int main(void)
{
    setlocale(LC_ALL, "Portuguese");
    insertTeamNamesOnTable();
    for (int i = 0; i < 20; i++)
    {
        // TODO: Implement archive ".csv" to show the the results
        printf("----------------\n");
        printf("%s\n", finalResultTable.teamName[i]);
    }
    // adversariesLogic();

    getch();
}
