algoritmo "AR CONDICIONADO"
// Função : Calcular a quantidade de BTUS
// Autor : Giovani Pizzaia
// Data : 18/06/2018
var
   btus, metros, btupessoas, exposicao : real
   i, equip, pessoas, salas : inteiro
   sol : caracter
inicio
   escreval ("Digite a quantidade de salas existentes no campus:")
   leia (salas)
   repita
      i <- i + 1
      escreval ("A",i," sala fica exposta ao sol?")
      escreval ("(s)im /(n)ão:")
      leia (sol)
      se (sol = "s") entao
         metros <- metros*800
      senao
         metros <- metros*600
      fimse
      escreval ("Digite o tamanho da sala em metros quadrados:")
      leia (metros)
      escreval ("Digite a quantidade de pessoas que cabem na sala:")
      leia (pessoas)
      enquanto (pessoas < 0) faca
         escreval ("digite um valor maior ou igual a zero para continuar:")
         leia (pessoas)
      fimenquanto
      escreval ("Digite quantos equipamentos eletrônicos existem na sala:")
      leia (equip)
      se (pessoas >= 2) entao
         btupessoas <- (pessoas-1)*600
      senao
         btupessoas <- 0
      fimse
      equip <- equip*600
      btus <- btupessoas + equip + metros
      escreval ("O ar condicionado da",i, " sala precisa ter",btus," BTUs.")
   ate i = salas
fimalgoritmo

