#include <stdio.h>
#include <math.h>
#include <conio.h>

int main () {

	int a, b;
	unsigned long soma;
	char cpf[11];
	
	printf("Digite seu cpf (sem pontos e hifens): ");
	scanf("%s", cpf);
	
	int j = 10;
	
	for (int i = 0; i < 9; i++){
		soma += j * (cpf[i] - 48);
		j--;
	}
	
	if ((soma * 10) % 11 == 10)
        a = 0;
    else
        a = (soma * 10) % 11;
		
	soma = 0;
	
	j = 11;
	for (int i = 0; i < 10; i++)
	{
		soma += j * (cpf[i] - 48);
		j--;
	}
		
	if ((soma * 10) % 11 == 10)
        b = 0;
    else
        b = (soma * 10) % 11;
		
	if ((a == (cpf[9] - 48)) && (b == (cpf[10] - 48)))
		printf("\nCPF valido!");
	else
		printf("\nCPF invalido!");
	
	getch();
}
