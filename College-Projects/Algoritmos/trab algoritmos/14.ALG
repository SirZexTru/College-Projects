Algoritmo "14"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
A,B,C:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o valor A")
leia(A)
escreval("digite o valor B")
leia(B)
escreval("digite o valor C")
leia(C)
se ( A < B ) e ( A < C ) entao
escreval("1º - ",A)
se ( B < C ) entao
escreval("2º - ",B)
escreval("3º - ",C)
senao
escreval("2º - ",C)
escreval("3º - ",B)
fimse
fimse
se ( B < A ) e ( B < C ) entao
escreval("1º - ",B)
se ( A < C ) entao
escreval("2º - ",A)
escreval("3º - ",C)
senao
escreval("2º - ",C)
escreval("3º - ",A)
fimse
fimse
se ( C < A ) e ( C < B ) entao
escreval ("1º - ",C)
se ( B < A ) entao
escreval ("2º - ",B)
escreval ("3º - ",A)
senao
escreval ("2º - ",A)
escreval ("3º - ",B)
fimse
fimse
Fimalgoritmo