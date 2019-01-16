#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dataPresenter.h"
#include "cpfValidator.h"

int main(int cpfResult)
{
    char personDocument[11], personBirth[10], name[50], gender[10], profession[40];
    
    setlocale(LC_ALL, "Portuguese");
    
    printf("Bem vindo ao Cadastro Fácil!\nPor favor informe seus dados pessoais:\n");
    
    printf("Digite seu CPF: ");
    gets(personDocument);

    if (cpfResult = 0)
    {
        printf("Por favor insira um CPF válido");
    }
    
    printf("\nDigite sua data de nascimento: ");
    gets(personBirth);

    printf("\nDigite seu nome completo: ");
    gets(name);
    
    printf("\nDigite seu gênero: ");
    gets(gender);
    
    printf("\nDigite sua profissão: ");
    gets(profession);
}