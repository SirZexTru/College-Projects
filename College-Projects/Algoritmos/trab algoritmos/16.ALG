Algoritmo "16"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
A,B,C,inter,maior,menor:real

Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("digite o valtor de A")
leia(A)
escreval("digite o valtor de B")
leia(B)
escreval("digite o valtor de C")
leia(C)
se ( A < B ) e ( A < C ) ent�o
menor <- A;
se ( B < C ) ent�o
inter <- B;
maior <- C;
sen�o
inter <- C;
maior <- B;
fimse
fimse
se ( B < A ) e ( B < C ) ent�o
menor <- B;
se ( A < C ) ent�o
inter <- A;
maior <- C;
sen�o
inter <- C;
maior <- A;
fimse
fimse
se ( C < A ) e ( C < B ) ent�o
menor <- C;
se ( A < B ) ent�o
inter <- A;
maior <- B;
sen�o
inter <- B;
maior <- A;
fimse
fimse

Fimalgoritmo