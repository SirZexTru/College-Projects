Algoritmo "16"
//  
//  
// Descrição   : Aqui você descreve o que o programa faz! (função)
// Autor(a)    : Nome do(a) aluno(a)
// Data atual  : 29/03/2018
Var
// Seção de Declarações das variáveis 
A,B,C,inter,maior,menor:real

Inicio
// Seção de Comandos, procedimento, funções, operadores, etc... 
escreval("digite o valtor de A")
leia(A)
escreval("digite o valtor de B")
leia(B)
escreval("digite o valtor de C")
leia(C)
se ( A < B ) e ( A < C ) então
menor <- A;
se ( B < C ) então
inter <- B;
maior <- C;
senão
inter <- C;
maior <- B;
fimse
fimse
se ( B < A ) e ( B < C ) então
menor <- B;
se ( A < C ) então
inter <- A;
maior <- C;
senão
inter <- C;
maior <- A;
fimse
fimse
se ( C < A ) e ( C < B ) então
menor <- C;
se ( A < B ) então
inter <- A;
maior <- B;
senão
inter <- B;
maior <- A;
fimse
fimse

Fimalgoritmo