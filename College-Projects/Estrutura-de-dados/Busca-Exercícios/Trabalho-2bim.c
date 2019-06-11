#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define MAX 14
 
void dijkstra(int G[MAX][MAX], int v, int startnode);
 
int main()
{
	int i, j, v = 38, u;

	int G[MAX][MAX] = {
		{   0, 20,   0,   0,   0,   0,   0,   0,  20,   0,  0,  0,   0, 205 },
		{  20,  0,   0,   0,   0,   0,   0,   0,   0,  30, 25,  0,   0,   0 },
		{   0,  0,   0, 150,   0,   0, 175,   0,   0,   0,  0, 90,   0,   0 },
		{   0,  0, 150,   0,   0, 125, 200,   0,   0,   0,  0,  0,   0,   0 },
		{   0,  0,   0,   0,   0,   0,   0, 135,   0,   0,  0,  0,   0, 110 },
		{   0,  0,   0, 125,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0 },
		{   0,  0, 175, 200,   0,   0,   0,  90, 220,   0,  0,  0,   0, 150 },
		{   0,  0,   0,   0, 135,   0,  90,   0,   0,   0,  0,  0,   0,   0 },
		{  20,  0,   0,   0,   0,   0, 220,   0,   0,   0, 10,  0,   0,   0 },
		{   0, 30,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0, 125,   0 },
		{   0, 25,   0,   0,   0,   0,   0,   0,  10,   0,  0, 35,   0,   0 },
		{   0,  0,  90,   0,   0,   0,   0,   0,   0,   0, 35,  0,   0,   0 },
		{   0,  0,   0,   0,   0,   0,   0,   0,   0, 125,  0,  0,   0, 275 },
		{ 205,  0,   0,   0, 110,   0, 150,   0,   0,   0,  0,  0, 275,   0 },
	};

	char cidades[14][20] = 
	{
		"Apucarana",
		"Arapongas",
		"C. Mourão",
		"Cascavel",
		"Curitiba",
		"Foz Iguaçu", 
		"Guarapuava",
		"Irati",
		"Jandaia do Sul", 
		"Londrina",
		"Mandaguari", 
		"Maringá", 
		"Ourinhos",
		"Ponta Grossa"
	};
	
	printf("\nEnter the starting node:");
	scanf("%d", &u);
	dijkstra(G, v, u);
	
	return 0;
}
 
void dijkstra(int G[MAX][MAX], int v, int startnode)
{
 
	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for(i = 0; i < v; i++)
	{
		for(j = 0; j < v; j++)
		{
			if(G[i][j] == 0)
			{
				cost[i][j] = INFINITY;
			}
			else
			{
				cost[i][j] = G[i][j];
			}
		}
	}
	
	//initialize pred[],distance[] and visited[]
	for(i = 0; i < v; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	
	while(count < v-1)
	{
		mindistance = INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i = 0; i < v; i++)
		{
			if(distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}
		}

		//check if a better path exists through nextnode			
		visited[nextnode] = 1;
		for(i = 0; i < v; i++)
		{
			if(!visited[i])
			{
				if(mindistance+cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
			}
		}
		count++;
	}
 
	//print the path and distance of each node
	for(i = 0; i < v; i++)
	{
		if(i != startnode)
		{
			printf("\nDistance of node%d=%d", i, distance[i]);
			printf("\nPath=%d", i);
			
			j = i;
			do
			{
				j = pred[j];
				printf("<-%d",j);
			}
			while(j != startnode);
		}
	}
}