Algoritmo "15"
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
escreval("Digite o valor de A")
leia(A)
escreval("Digite o valor de B")
leia(B)
escreval("Digite o valor de C")
leia(C)
se ( A > B ) e ( A > C ) então
escreval("1º - ",A);
se ( B > C ) então
escreval("2º - ",B);
escreval("3º - ",C);
senão
escreval("2º - ",C);
escreval("3º - ",B);
fimse
fimse
se ( B > A ) e ( B > C ) então
escreval("1º - ",B);
se ( A > C ) então
escreval("2º - ",A);
escreval("3º - ",C);
senão
escreval("2º - ",C);
escreval("3º - ",A);
fimse
fimse
se ( C > A ) e ( C > B ) então
escreval("1º - ",C);
se ( A > B ) então
escreval("2º - ",A);
escreval("3º - ",B);
senão
escreval("2º - ",B);
escreval("3º - ",A);
fimse
fimse

Fimalgoritmo