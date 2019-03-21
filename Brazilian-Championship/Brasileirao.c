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

// TODO: Implement with struct, considering each column an array of 21 spaces (1 for title, 20 for data)
char finalResultTable[21][10];

char insertValuesOnTable()
{
    for (int i=1; i<=21; i++)
    {
        finalResultTable[i][1] = i;
    }
    
    finalResultTable[0][0] = "Colocação | ";
    finalResultTable[0][1] = "Classificação | ";
    finalResultTable[0][2] = "P | ";
    finalResultTable[0][3] = "J | ";
    finalResultTable[0][4] = "V | ";
    finalResultTable[0][5] = "E | ";
    finalResultTable[0][6] = "D | ";
    finalResultTable[0][7] = "GP | ";
    finalResultTable[0][8] = "GC | ";
    finalResultTable[0][9] = "SG | ";

    for (int i=0; i<20; i++)
    {
        for (int j=0; j<10; j++)
        {
            printf("%s\n", finalResultTable[i][j]);
        }
    }
}

void main()
{
    insertValuesOnTable();
    getch();
}