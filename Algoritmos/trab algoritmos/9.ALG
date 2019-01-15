Algoritmo "9"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
a,b,resto:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o valor do primeiro numero")
leia(a)
escreval("digite o valor do segundo numero")
leia(b)
se ( b = 0 ) então
escreval("Impossível verificar, pois B é zero")
senão
resto <- a mod b
se ( resto = 0 ) então
escreval(a,"é divisível por ",b)
senão
escreval(a,"não é divisível por ",b)
fimse
fimse

Fimalgoritmo