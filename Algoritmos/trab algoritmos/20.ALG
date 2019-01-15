Algoritmo "20"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
N1,N2:real
Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o valor do primeiro numero")
leia(N1,N2);
se ( N1 < N2 ) então
escreval("Quadrado Menor: ",N1 ** 2);
se ( N2 >= 0 ) então
escreval("Raiz maior: ",raizQ(N2) );
senão
escreval("não é possível calcular a raiz do maior!");
fimse
senão
escreval("Quadrado Menor: ",N2 ** 2);
se ( N1 >= 0 ) então
escreval("Raiz maior: ",raizQ(N1) )
senão
escreval("não é possível calcular a raiz do maior!");
fimse
fimse

Fimalgoritmo