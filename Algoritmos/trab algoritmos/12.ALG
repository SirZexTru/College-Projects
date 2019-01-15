Algoritmo "12"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
salario,prestacao,porcento:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o salario")
leia(salario)
porcento <- salario * (30/100);
se ( prestacao <= porcento ) então
escreval("O empréstimo pode ser concedido!");
senão
escreval("O empréstimo não pode ser concedido!");
fimse

Fimalgoritmo