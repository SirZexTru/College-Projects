Algoritmo "9"
//  
//  
// Descri��o   : Aqui voc� descreve o que o programa faz! (fun��o)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Se��o de Declara��es das vari�veis 
a,b,resto:real
Inicio
// Se��o de Comandos, procedimento, fun��es, operadores, etc... 
escreval("digite o valor do primeiro numero")
leia(a)
escreval("digite o valor do segundo numero")
leia(b)
se ( b = 0 ) ent�o
escreval("Imposs�vel verificar, pois B � zero")
sen�o
resto <- a mod b
se ( resto = 0 ) ent�o
escreval(a,"� divis�vel por ",b)
sen�o
escreval(a,"n�o � divis�vel por ",b)
fimse
fimse

Fimalgoritmo