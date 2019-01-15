Algoritmo "baskara"
Var
x1,x2,a,b,c,delta:real
inicio
escreva ("digite o valor de a:")
leia (a)
escreva ("digite o valor de b:")
leia (b)
escreva ("digite o valor de c:")
leia (c)
delta <- (b^2-4*a*c)
se delta < 0 entao
escreva ("o delta é menor que zero")
senao
escreval ("o valor de delta é:",delta)
fimse
x1 <- (-b+(raizQ(delta)))/(2*a)
x2 <- (-b-(raizQ(delta)))/(2*a)
escreval ("X1 e igual a:",x1)
escreva ("X2 e igual a:",x2)
Fimalgoritmo