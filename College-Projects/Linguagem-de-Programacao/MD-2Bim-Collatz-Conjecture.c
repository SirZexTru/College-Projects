// Gustavo Ausechi Furlan
// RA: 2576
// ECON2S
// Conjectura de Collatz

#include <stdio.h>
#include <locale.h>
main(){
    setlocale(LC_ALL, "Portuguese");
    printf("Escreva um número para calcular a Conjectura de Collatz:\n"); int num;
    scanf("%i", &num);
    if (num > 0){
        while (num != 1){
            if (num%2 == 0){
                num = num/2;
            }
            else {
                num = num*3+1;
            }
            printf("\nO número é: %i", num);   
        }
        printf("\n\nPressione qualquer tecla para encerrar a execução do programa...");
        getch();
    }
    else{
        printf("\nNão é possí­vel aplicar a Conjectura de Collatz pois o número é menor ou igual a 0.");
        printf("\n\nPressione qualquer tecla para encerrar a execução do programa...");
        getch();
        return 0;
    }
}