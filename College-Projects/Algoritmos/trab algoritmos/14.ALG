Algoritmo "14"
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
escreval("digite o valor A")
leia(A)
escreval("digite o valor B")
leia(B)
escreval("digite o valor C")
leia(C)
se ( A < B ) e ( A < C ) entao
escreval("1� - ",A)
se ( B < C ) entao
escreval("2� - ",B)
escreval("3� - ",C)
senao
escreval("2� - ",C)
escreval("3� - ",B)
fimse
fimse
se ( B < A ) e ( B < C ) entao
escreval("1� - ",B)
se ( A < C ) entao
escreval("2� - ",A)
escreval("3� - ",C)
senao
escreval("2� - ",C)
escreval("3� - ",A)
fimse
fimse
se ( C < A ) e ( C < B ) entao
escreval ("1� - ",C)
se ( B < A ) entao
escreval ("2� - ",B)
escreval ("3� - ",A)
senao
escreval ("2� - ",A)
escreval ("3� - ",B)
fimse
fimse
Fimalgoritmo