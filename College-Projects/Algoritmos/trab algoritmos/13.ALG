Algoritmo "13"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
A,B,C,D:real

Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o valor  A")
leia(A)
escreval("digite o valor  B")
leia(B)
escreval("digite o valor  C")
leia(C)
escreval("digite o valor  D")
leia(D)
se ( A > B ) e ( A > C ) e ( A > D ) então
escreval("Maior: ",A);
fimse
se ( B > A ) e ( B > C ) e ( B > D ) então
escreval("Maior: ",B);
fimse
se ( C > A ) e ( C > B ) e ( C > D ) então
escreval("Maior: ",C);
fimse
se ( D > A ) e ( D > B ) e ( D > C ) então
escreval("Maior: ",D);
fimse
se ( A < B ) e ( A < C ) e ( A < D ) então
escreval("Menor: ",A);
fimse
se ( B < A ) e ( B < C ) e ( B < D ) então
escreval("Menor: ",B);
fimse
se ( C < A ) e ( C < B ) e ( C < D ) então
escreval("Menor: ",C);
fimse
se ( D < A ) e ( D < B ) e ( D < C ) então
escreval("Menor: ",D);
fimse

Fimalgoritmo