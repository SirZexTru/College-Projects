Algoritmo "13"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
A,B,C,D:real

Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("digite o valor  A")
leia(A)
escreval("digite o valor  B")
leia(B)
escreval("digite o valor  C")
leia(C)
escreval("digite o valor  D")
leia(D)
se ( A > B ) e ( A > C ) e ( A > D ) ent�o
escreval("Maior: ",A);
fimse
se ( B > A ) e ( B > C ) e ( B > D ) ent�o
escreval("Maior: ",B);
fimse
se ( C > A ) e ( C > B ) e ( C > D ) ent�o
escreval("Maior: ",C);
fimse
se ( D > A ) e ( D > B ) e ( D > C ) ent�o
escreval("Maior: ",D);
fimse
se ( A < B ) e ( A < C ) e ( A < D ) ent�o
escreval("Menor: ",A);
fimse
se ( B < A ) e ( B < C ) e ( B < D ) ent�o
escreval("Menor: ",B);
fimse
se ( C < A ) e ( C < B ) e ( C < D ) ent�o
escreval("Menor: ",C);
fimse
se ( D < A ) e ( D < B ) e ( D < C ) ent�o
escreval("Menor: ",D);
fimse

Fimalgoritmo