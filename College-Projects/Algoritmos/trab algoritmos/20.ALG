Algoritmo "20"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
N1,N2:real
Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("digite o valor do primeiro numero")
leia(N1,N2);
se ( N1 < N2 ) ent�o
escreval("Quadrado Menor: ",N1 ** 2);
se ( N2 >= 0 ) ent�o
escreval("Raiz maior: ",raizQ(N2) );
sen�o
escreval("n�o � poss�vel calcular a raiz do maior!");
fimse
sen�o
escreval("Quadrado Menor: ",N2 ** 2);
se ( N1 >= 0 ) ent�o
escreval("Raiz maior: ",raizQ(N1) )
sen�o
escreval("n�o � poss�vel calcular a raiz do maior!");
fimse
fimse

Fimalgoritmo