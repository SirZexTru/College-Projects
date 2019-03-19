Algoritmo "3"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
n,resto:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o numero")
leia(n)
resto <- n mod 2
se ( resto = 0 ) então
escreval(n,"é PAR")
senão
imprima(n,"é ÍMPAR")
fimse
Fimalgoritmo