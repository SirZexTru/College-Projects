Algoritmo "11"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
n,resto7,resto3:real
Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("digite o numero")
leia(n)
resto3 <- n mod 3;
resto7 <- n mod 7;
se ( resto3 = 0 ) e ( resto7 = 0 ) ent�o
escreval(n,"� divis�vel por 3 e por 7 ");
sen�o
escreval(n,"n�o � divis�vel por 3 e por 7");
fimse

Fimalgoritmo