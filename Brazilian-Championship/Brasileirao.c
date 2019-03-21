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

#include <stdio.h>
#include <conio.h>

// 1: Construir tabela de resultados e preencher nomes dos times
// 2: Fazer primeira rodada manual
// 3: Fazer primeira rodada automatizada
// 4: Fazer 38 rodadas automatizadas

// TODO: Implement with struct, considering each column an array of 20 spaces
struct tableData
{
    char name[20];
    int position[20], points[20], games[20], wins[20], draw[20], loses[20], goalsDone[20], goalsReceived[20], goalsBalance[20];
};
struct tableData finalResultTable;

char insertValuesOnTable()
{
    finalResultTable.name[0] = "São paulo";
    finalResultTable.name[1] = "Atlético";
    finalResultTable.name[2] = "Atlético";
    finalResultTable.name[3] = "Avaí";
    finalResultTable.name[4] = "Bahia";
    finalResultTable.name[5] = "Botafogo";
    finalResultTable.name[6] = "Ceará";
    finalResultTable.name[7] = "Chapecoense";
    finalResultTable.name[8] = "Corinthians";
    finalResultTable.name[9] = "Cruzeiro";
    finalResultTable.name[10] = "CSA";
    finalResultTable.name[11] = "Flamengo";
    finalResultTable.name[12] = "Fluminense";
    finalResultTable.name[13] = "Fortaleza";
    finalResultTable.name[14] = "Goiás ";
    finalResultTable.name[15] = "Grêmio";
    finalResultTable.name[16] = "Internacional" ;
    finalResultTable.name[17] = "Palmeiras ";
    finalResultTable.name[18] = "Santos ";
    finalResultTable.name[19] = "São Paulo ";
    finalResultTable.name[20] = "Vasco";
}

void main()
{
    insertValuesOnTable();
    getch();
}