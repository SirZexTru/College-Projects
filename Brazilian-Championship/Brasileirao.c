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
}

void main()
{
    insertValuesOnTable();
    getch();
}