Algoritmo "15"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
A,B,C:real
Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("Digite o valor de A")
leia(A)
escreval("Digite o valor de B")
leia(B)
escreval("Digite o valor de C")
leia(C)
se ( A > B ) e ( A > C ) ent�o
escreval("1� - ",A);
se ( B > C ) ent�o
escreval("2� - ",B);
escreval("3� - ",C);
sen�o
escreval("2� - ",C);
escreval("3� - ",B);
fimse
fimse
se ( B > A ) e ( B > C ) ent�o
escreval("1� - ",B);
se ( A > C ) ent�o
escreval("2� - ",A);
escreval("3� - ",C);
sen�o
escreval("2� - ",C);
escreval("3� - ",A);
fimse
fimse
se ( C > A ) e ( C > B ) ent�o
escreval("1� - ",C);
se ( A > B ) ent�o
escreval("2� - ",A);
escreval("3� - ",B);
sen�o
escreval("2� - ",B);
escreval("3� - ",A);
fimse
fimse

Fimalgoritmo