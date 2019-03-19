#include <stdio.h>
int main(void)
{
    unsigned char i, j, valor;
    float notas[3][4];
    for (i=0; i<3; i++)
    {
        for (j=0; j<4; j++)
        {
            notas[i][j] = (i*4)+j+1;
        }
    }
    for (i=0; i<3; i++)
    {
        for (j=0; j<4; j++)
        {
            printf("%5d \n", notas[i][j]);
        }
    }
    getchar();
}