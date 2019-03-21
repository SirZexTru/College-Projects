//  Autor: Gustavo Ausechi Furlan RA: 2576 Turma: ECON2S

//  IMPORTANTE:
//  Código do mesário: 1234

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

main() {
    
    int candidatoX=0, candidatoY=0, candidatoZ=0, candidatoW=0, eleitores, i=0, voto, securityCode, confirm;
    float percentX, percentY, percentZ, percentW;
    
    setlocale(LC_ALL, "Portuguese");
    printf("  ---------------------------------------------------------------------------");
    printf("\n  |                              Atenção                                    |");
    printf("\n  |          É necessário digitar o código do mesário para continuar        |");
    printf("\n  ---------------------------------------------------------------------------\n");
    scanf("%i", &securityCode);
    system("cls");
    while (securityCode!=1234) {
        printf("Código do mesário inválido, digite corretamente para continuar.\n");
        scanf("%i", &securityCode);
        system("cls");
    }
    printf("Quantos eleitores irão votar nesta seção eleitoral?\n");
    scanf("%i", &eleitores);
    if (eleitores == 0) {
        system("cls");
        printf("Esta seção de votação não tem eleitores, portanto está encerrada.");
        printf("Pressione qualquer tecla para finalizar...");
        getch();
        return 0;
    }
    system("cls");

    while (i < eleitores) {
        i++;
        voto:
        printf("                    Bem vindo as Eleições 2018\n");
        printf("         Digite o número do seu candidato e pressione Enter:\n");
        scanf("%i", &voto);
        getchar();
        while ((voto<1)||(voto>4)) {
            system("cls");
            printf("\n      Número inválido. Por favor digite seu voto novamente:");
            scanf("%i", &voto);
            getchar();
            system("cls");
        }
        switch (voto) {
            case 1:
                printf("Confirma o voto no candidato X? (1)Confirma  (2)Corrige\n");
                scanf("%i", &confirm);
                while ((confirm<1)||(confirm>2)) {
                    system("cls");
                    printf("O número inserido não é válido. Por favor digite (1)Confirma ou (2)Corrige:");
                    scanf("%i", &confirm);
                    system("cls");
                }
                switch (confirm) {
                    case 1:
                        candidatoX++;
                        printf("Voto computado. Por favor chame o próximo eleitor e pressione Enter.");
                        getchar();
                    break;
                    default:
                        system("cls");
                        goto voto;
                }
            break;
            case 2:
                printf("Confirma o voto no candidato Y? (1)Confirma  (2)Corrige\n");
                scanf("%i", &confirm);
                while ((confirm<1)||(confirm>2)) {
                    system("cls");
                    printf("O número inserido não é válido. Por favor digite (1)Confirma ou (2)Corrige:");
                    scanf("%i", &confirm);
                    system("cls");
                }
                switch (confirm) {
                    case 1:
                        candidatoY++;
                        printf("Voto computado. Por favor chame o próximo eleitor e pressione Enter.");
                        getchar();
                    break;
                    default:
                        system("cls");
                        goto voto;
                }
            break;
            case 3:
                printf("Confirma o voto no candidato Z? (1)Confirma  (2)Corrige\n");
                scanf("%i", &confirm);
                while ((confirm<1)||(confirm>2)) {
                    system("cls");
                    printf("O número inserido não é válido. Por favor digite (1)Confirma ou (2)Corrige:");
                    scanf("%i", &confirm);
                    system("cls");
                }
                switch (confirm) {
                    case 1:
                        candidatoZ++;
                        printf("Voto computado. Por favor chame o próximo eleitor e pressione Enter.");
                        getchar();
                    break;
                    default:
                        system("cls");
                        goto voto;
                }
            break;
            case 4:
                printf("Confirma o voto no candidato W? (1)Confirma  (2)Corrige:\n");
                scanf("%i", &confirm);
                while ((confirm<1)||(confirm>2)) {
                    system("cls");
                    printf("O número inserido não é válido. Por favor digite (1)Confirma ou (2)Corrige:");
                    scanf("%i", &confirm);
                    system("cls");
                }
                switch (confirm) {
                    case 1:
                        candidatoW++;
                        printf("Voto computado. Por favor chame o próximo eleitor e pressione Enter.");
                        getchar();
                    break;
                    default:
                        system("cls");
                        goto voto;
                }
        }
        system("cls");
        printf("Voto computado.\n");
        printf("Seção de votação encerrada. Por favor chame o próximo eleitor e pressione Enter.");
        getchar();
        system("cls");
    }
    printf("\n---------------------------------------------------------------------------");
    printf("\n|                              Atenção                                    |");
    printf("\n|          É necessário digitar o código do mesário para continuar        |");
    printf("\n---------------------------------------------------------------------------\n");
    scanf("%i", &securityCode);
    system("cls");
    while (securityCode!=1234) {
        printf("Código do mesário inválido, digite corretamente para continuar.\n");
        scanf("%i", &securityCode);
        system("cls");
    }
    percentX = ((float)candidatoX/eleitores)*100.0;
    percentY = ((float)candidatoY/eleitores)*100.0;
    percentZ = ((float)candidatoZ/eleitores)*100.0;
    percentW = ((float)candidatoW/eleitores)*100.0;

    printf("\n-------------------------------------------");
    printf("\n| Estatísticas e dados das Eleições 2018: |");
    printf("\n-------------------------------------------");

    printf("\n    Candidato X\n");
    printf("Total de votos: %i\n", candidatoX);
    printf("Porcentagem de votos: %0.2f%%\n\n", percentX);
   
    printf("    Candidato Y\n");
    printf("Total de votos: %i\n", candidatoY);
    printf("Porcentagem de votos: %0.2f%%\n\n", percentY);

    printf("    Candidato Z\n");
    printf("Total de votos: %i\n", candidatoZ);
    printf("Porcentagem de votos: %0.2f%%\n\n", percentZ);

    printf("    Candidato W\n");
    printf("Total de votos: %i\n", candidatoW);
    printf("Porcentagem de votos: %0.2f%%\n\n", percentW);
    
    if ((candidatoX > candidatoY) && (candidatoX > candidatoZ) && (candidatoX > candidatoW)) {
        printf("Resultado: Candidato X é o vencedor das Eleições 2018.");
    }
    else if ((candidatoY > candidatoX) && (candidatoY > candidatoZ) && (candidatoY > candidatoW)) {
        printf("Resultado: Candidato Y é o vencedor das Eleições 2018.");
    }
    else if ((candidatoZ > candidatoX) && (candidatoZ > candidatoY) && (candidatoZ > candidatoW)) {
        printf("Resultado: Candidato Z é o vencedor das Eleições 2018.");
    }
    else if ((candidatoW > candidatoX) && (candidatoW > candidatoY) && (candidatoW > candidatoZ)) {
        printf("Resultado: Candidato W é o vencedor das Eleições 2018.");
    }
    else if ((candidatoX == candidatoY) && (candidatoX == candidatoZ) && (candidatoX == candidatoW) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X, Y, Z e W.");
    }
    else if ((candidatoX == candidatoY) && (candidatoX == candidatoZ) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X, Y e Z.");
    }
    else if ((candidatoX == candidatoY) && (candidatoX == candidatoW) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X, Y e W.");
    }
    else if ((candidatoX == candidatoZ) && (candidatoX == candidatoW) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X, Z e W.");
    }
    else if ((candidatoY == candidatoZ) && (candidatoY == candidatoW) && (candidatoY != 0)) {
        printf("Resultado: Há um empate entre os candidatos Y, Z e W.");
    }
    else if ((candidatoX == candidatoY) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X e Y.");
    }
    else if ((candidatoX == candidatoZ) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X e Z.");
    }
    else if ((candidatoX == candidatoW) && (candidatoX != 0)) {
        printf("Resultado: Há um empate entre os candidatos X e W.");
    }
    else if ((candidatoY == candidatoZ) && (candidatoY != 0)) {
        printf("Resultado: Há um empate entre os candidatos Y e Z.");
    }
    else if ((candidatoY == candidatoW) && (candidatoY != 0)) {
        printf("Resultado: Há um empate entre os candidatos Y e W.");
    }
    else if ((candidatoZ == candidatoW) && (candidatoZ != 0)) {
        printf("Resultado: Há um empate entre os candidatos Z e W."); 
    }
    else if ((candidatoX == 0) && (candidatoY == 0) && (candidatoZ == 0) && (candidatoW == 0)) {
        printf("Resultado: Não há um vencedor, pois todos os candidatos tem 0 votos.");
    }
    printf("\n\nPressione qualquer tecla para finalizar...");
    getch();
    return 0;
}
