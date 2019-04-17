// Aluno: Gustavo Ausechi Furlan
// RA: 2576
// Turma: ECON3S
// Algoritmo que simula a execução do Campeonato Brasileiro de Futebol.

// Objetivo: simular as 38 rodadas do Campeonato Brasileiro de futebol, apresentando os seguintes dados de cada time:
// Colocação, nome, pontos (P), jogos (J), empates (E), derrotas (D), gols pró (GP), gols contra (GC) e o saldo de gols (SG).

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <time.h>

struct tableColumns
{
	char teamName[20][20], teamInitial[20][4], bestFour[4][20], worstFour[4][20], champion[20];
	int dataTable[21][9]; // points=0, games=1, wins=2 draws=3 loses=4 GP=5, GC=6, SG=7, id=8.
};
struct tableColumns finalResultTable;

struct roundData
{
	char team1[4], team2[4];
	int round;
};
struct roundData rounds[380];

void insertTeamDataOnTable(void)
{
	strcpy(finalResultTable.teamName[0], "Atlético-MG");
	strcpy(finalResultTable.teamName[1], "Atlético-PR");
	strcpy(finalResultTable.teamName[2], "Avaí");
	strcpy(finalResultTable.teamName[3], "Bahia");
	strcpy(finalResultTable.teamName[4], "Botafogo");
	strcpy(finalResultTable.teamName[5], "Ceará");
	strcpy(finalResultTable.teamName[6], "Chapecoense");
	strcpy(finalResultTable.teamName[7], "Corinthians");
	strcpy(finalResultTable.teamName[8], "Cruzeiro");
	strcpy(finalResultTable.teamName[9], "CSA");
	strcpy(finalResultTable.teamName[10], "Flamengo");
	strcpy(finalResultTable.teamName[11], "Fluminense");
	strcpy(finalResultTable.teamName[12], "Fortaleza");
	strcpy(finalResultTable.teamName[13], "Goiás");
	strcpy(finalResultTable.teamName[14], "Grêmio");
	strcpy(finalResultTable.teamName[15], "Internacional");
	strcpy(finalResultTable.teamName[16], "Palmeiras");
	strcpy(finalResultTable.teamName[17], "Santos");
	strcpy(finalResultTable.teamName[18], "São Paulo");
	strcpy(finalResultTable.teamName[19], "Vasco");

	strcpy(finalResultTable.teamInitial[0], "ATM");
	strcpy(finalResultTable.teamInitial[1], "ATP");
	strcpy(finalResultTable.teamInitial[2], "AVA");
	strcpy(finalResultTable.teamInitial[3], "BAH");
	strcpy(finalResultTable.teamInitial[4], "BOT");
	strcpy(finalResultTable.teamInitial[5], "CEA");
	strcpy(finalResultTable.teamInitial[6], "CHA");
	strcpy(finalResultTable.teamInitial[7], "COR");
	strcpy(finalResultTable.teamInitial[8], "CRU");
	strcpy(finalResultTable.teamInitial[9], "CSA");
	strcpy(finalResultTable.teamInitial[10], "FLA");
	strcpy(finalResultTable.teamInitial[11], "FLU");
	strcpy(finalResultTable.teamInitial[12], "FOR");
	strcpy(finalResultTable.teamInitial[13], "GOI");
	strcpy(finalResultTable.teamInitial[14], "GRE");
	strcpy(finalResultTable.teamInitial[15], "INT");
	strcpy(finalResultTable.teamInitial[16], "PAL");
	strcpy(finalResultTable.teamInitial[17], "SAN");
	strcpy(finalResultTable.teamInitial[18], "SPA");
	strcpy(finalResultTable.teamInitial[19], "VAS");

	for (int i = 0; i < 20; i++)
	{
		finalResultTable.dataTable[i][8] = i;
	}
}

int randomValue(void)
{
	int r = rand() % 3;
	return r;
}

void roundResultsCalc(int round, int teamOne, int scoreTeamOne, int teamTwo, int scoreTeamTwo)
{
	if (scoreTeamOne > scoreTeamTwo)
	{
		finalResultTable.dataTable[teamOne][0] = finalResultTable.dataTable[teamOne][0] + 3;
		finalResultTable.dataTable[teamOne][2] = finalResultTable.dataTable[teamOne][2] + 1;
		finalResultTable.dataTable[teamTwo][4] = finalResultTable.dataTable[teamTwo][4] + 1;
	}
	else if (scoreTeamOne < scoreTeamTwo)
	{
		finalResultTable.dataTable[teamTwo][0] = finalResultTable.dataTable[teamTwo][0] + 3;
		finalResultTable.dataTable[teamTwo][2] = finalResultTable.dataTable[teamTwo][2] + 1;
		finalResultTable.dataTable[teamOne][4] = finalResultTable.dataTable[teamTwo][4] + 1;
	}
	else
	{
		finalResultTable.dataTable[teamOne][0]++;
		finalResultTable.dataTable[teamOne][3]++;
		finalResultTable.dataTable[teamTwo][0]++;
		finalResultTable.dataTable[teamTwo][3]++;
	}
	finalResultTable.dataTable[teamOne][5] += scoreTeamOne;
	finalResultTable.dataTable[teamOne][6] += scoreTeamTwo;
	finalResultTable.dataTable[teamOne][7] += scoreTeamOne - scoreTeamTwo;

	finalResultTable.dataTable[teamTwo][5] += scoreTeamTwo;
	finalResultTable.dataTable[teamTwo][6] += scoreTeamOne;
	finalResultTable.dataTable[teamTwo][7] += scoreTeamTwo - scoreTeamOne;
}

void matchesLogic(void)
{
	char url[] = "C:\\Users\\gusta\\Documents\\GitHub\\College-Projects\\Brazilian-Championship\\tabela-campeonato.txt";
	FILE* table;

	table = fopen(url, "r");
	if (table == NULL)
	{
		printf("Não foi possível abrir o arquivo\n");
	}
	else
	{
		int i = 0, teamOne, teamTwo, scoreTeamOne, scoreTeamTwo;
		while ((fscanf(table, "%s %s %i", rounds[i].team1, rounds[i].team2, &rounds[i].round)) != EOF)
		{
			printf("%s vs %s in round: %i\n", rounds[i].team1, rounds[i].team2, rounds[i].round);
			for (int j = 0; j < 20; j++)
			{
				if ((strcmp(rounds[i].team1, finalResultTable.teamInitial[j])) == 0)
				{
					teamOne = finalResultTable.dataTable[j][8];
					finalResultTable.dataTable[j][1]++;
				}
				else if ((strcmp(rounds[i].team2, finalResultTable.teamInitial[j])) == 0)
				{
					teamTwo = finalResultTable.dataTable[j][8];
					finalResultTable.dataTable[j][1]++;
				}
			}
			scoreTeamOne = randomValue();
			scoreTeamTwo = randomValue();
			roundResultsCalc(rounds[i].round, teamOne, scoreTeamOne, teamTwo, scoreTeamTwo);
			i++;
		}
		system("cls");
	}
}

void reorderTeams()
{
	int rows = 20, columns = 9, k = 0, x = 0, temporary1;
	char temporary2[4], temporary3[20];
	for (int i = 0; i < rows; i++)
	{
		for (int j = i + 1; j < rows; j++)
		{
			if (finalResultTable.dataTable[i][k] > finalResultTable.dataTable[j][k])
			{
				for (x = 0; x < 9; x++)
				{
					temporary1 = finalResultTable.dataTable[i][x];
					finalResultTable.dataTable[i][x] = finalResultTable.dataTable[j][x];
					finalResultTable.dataTable[j][x] = temporary1;

					strcpy(temporary2, finalResultTable.teamInitial[i]);
					strcpy(finalResultTable.teamInitial[i], finalResultTable.teamInitial[j]);
					strcpy(finalResultTable.teamInitial[j], temporary2);

					strcpy(temporary3, finalResultTable.teamName[i]);
					strcpy(finalResultTable.teamName[i], finalResultTable.teamName[j]);
					strcpy(finalResultTable.teamName[j], temporary3);
				}
			}
		}
	}
}

void defineWinnersAndLosers(void)
{
	strcpy(finalResultTable.champion, finalResultTable.teamName[19]);
	for (int i = 19; i > 15; i--)
	{
		strcpy(finalResultTable.bestFour[19 - i], finalResultTable.teamName[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		strcpy(finalResultTable.worstFour[i], finalResultTable.teamName[i]);
	}
}

void printResults(void)
{
	printf("Pos | Nome | P | J | V | E | D | GP | GC | SG |\n");
	for (int i = 19; i >= 0; i--)
	{
		printf("-----------------------------------------------------\n");
		if (i > 10)
		{
			printf(" %02i | ", 20 - i);
		}
		else
		{
			printf(" %i | ", 20 - i);
		}
		printf("%s  | ", finalResultTable.teamInitial[i]);
		printf("%i | ", finalResultTable.dataTable[i][0]);
		printf("%i | ", finalResultTable.dataTable[i][1]);
		printf("%i | ", finalResultTable.dataTable[i][2]);
		printf("%i | ", finalResultTable.dataTable[i][3]);
		printf("%i | ", finalResultTable.dataTable[i][4]);
		printf("%i | ", finalResultTable.dataTable[i][5]);
		printf("%i | ", finalResultTable.dataTable[i][6]);
		printf("%i |\n", finalResultTable.dataTable[i][7]);
	}
	printf("-----------------------------------------------------");

	printf("\n\n----------------------------------------\n");
	printf("Times que vão para a libertadores: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%i - %s\n", i + 1, finalResultTable.bestFour[i]);
	}
	printf("----------------------------------------\n");
	printf("Times que serão rebaixados: \n");
	for (int i = 0; i < 4; i++)
	{
		printf("%i - %s\n", i + 1, finalResultTable.worstFour[i]);
	}
	printf("----------------------------------------\n\n");

	printf("O campeão é: %s\n\n", finalResultTable.champion);
	printf("----------------------------------------\n\n");
	printf("Pressione enter para finalizar...");
	getch();
}

int main(void)
{
	srand((unsigned int)time(NULL));
	setlocale(LC_ALL, "Portuguese");
	insertTeamDataOnTable();
	matchesLogic();
	reorderTeams();
	defineWinnersAndLosers();
	printResults();
}