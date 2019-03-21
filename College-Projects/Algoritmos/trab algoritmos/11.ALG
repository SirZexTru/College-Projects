Algoritmo "11"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
n,resto7,resto3:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o numero")
leia(n)
resto3 <- n mod 3;
resto7 <- n mod 7;
se ( resto3 = 0 ) e ( resto7 = 0 ) então
escreval(n,"é divisível por 3 e por 7 ");
senão
escreval(n,"não é divisível por 3 e por 7");
fimse

Fimalgoritmo