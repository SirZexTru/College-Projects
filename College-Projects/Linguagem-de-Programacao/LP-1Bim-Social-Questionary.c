	// Gustavo Ausechi Furlan   
	// Engenharia da Computação
	// RA:2576
	// ECON2S
	// FEITEP
	
	//Declaração de bibliotecas
	#include <stdio.h>
	#include <math.h>
	#include <locale.h>
	
	//Começo do código com a abertura da funcão main
	main () {
		
		//Declarando as variáveis
		//Explicação:"Banheiro" (por exemplo) é o que armazena a resposta e "PBanheiro" é o que armazena a pontuação.
		int Banheiro, Empregado, Automovel, Computador, LavaLouca, Geladeira, Freezer, LavaRoupa, Dvd, MicroOndas, Moto, SecadoraRoupa; 
	    int PontosTotal, Pontos1, Pontos2, Escolaridade, Agua, Pavimentacao;
	    int PBanheiro, PEmpregado, PAutomovel, PComputador, PLavaLouca, PGeladeira, PFreezer, PLavaRoupa, PDvd;
	    int PMicroOndas, PMoto, PSecadoraRoupa, PEscolaridade, PAgua, PPavimentacao;
	    
	    //Alterando o idioma para PT-BR.
	    setlocale (LC_ALL, "Portuguese");
	    
		//Introdução e explicação de como responder.
	    printf("*Bem vindo ao Senso IBGE 2018*");
	    printf("\n-Temos um pequeno questionário e um sistema de avaliação que varia de 0 a 100 pontos.");
	    printf("\n-Ao final do questionário, apresentaremos qual sua classe social e sua pontuação");
	    printf("\n-A maneira de responder é:");
	    printf("\n-Primeira parte: é necessário apenas digitar qual o número que responde a pergunta corretamente e apertar enter.");
	    
	    //Seção de perguntas (Parte 1).
		printf("\n-Perguntas:\n");
	    printf("\nPergunta 1) Quantos banheiros existem na casa?\n");
	    scanf("%i", &Banheiro);
	    
		//While para impedir o usuário de prosseguir com um valor inválido.
		while (Banheiro<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Banheiro);
	    }
		//Estrutura switch/case para fazer a lógica de pontuações.
		switch (Banheiro) {
	        case 0:
	            PBanheiro=0;
	        	break;
	        case 1:
	            PBanheiro=3;
	        	break;
	        case 2:
	            PBanheiro=7;
	        	break;
	        case 3:
	            PBanheiro=10;
	        	break;
	        default:
	            PBanheiro=14;
	    }
	    
	    //A estrutura de: print(pergunta), scan(resposta), while{condicao} e switch{lógica dos pontos} se repete por toda a parte 1 das perguntas.
	    printf("Pergunta 2) Quantos empregados domésticos existem na casa?\n");
	    scanf("%i", &Empregado);
	    while (Empregado<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero");
	        scanf("%i", &Empregado);
	    } 
	    switch (Empregado) {
	        case 0:
	            PEmpregado=0;
	        	break;
	        case 1:
	            PEmpregado=3;
	        	break;
	        case 2:
	            PEmpregado=7;
	        	break;
	        case 3:
	            PEmpregado=10;
	        	break;
	        default:
	            PEmpregado=13;
	    }
	     
	    printf("Pergunta 3) Quantos automóvelis existem na casa?\n");
	    scanf("%i", &Automovel);
	    while (Automovel<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Automovel);
	    } 
	    switch (Automovel) {
	        case 0:
	            PAutomovel=0;
	        	break;
	        case 1:
	            PAutomovel=3;
	        	break;
	        case 2:
	            PAutomovel=5;
	        	break;
	        case 3:
	            PAutomovel=8;
	        	break;
	        default:
	        	PAutomovel=11;
	    }
	    
	    printf("Pergunta 4) Quantos computadores/notebooks existem na casa?\n");
	    scanf("%i", &Computador);
	  	while (Computador<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Computador);
	    } 
	    switch (Computador) {
	        case 0:
	            PComputador=0;
	        	break;
	        case 1:
	            PComputador=3;
	        	break;
	        case 2:
	            PComputador=6;
	        	break;
	        case 3:
	            PComputador=8;
	        	break;
	        default:
	            PComputador=11;
	    }
	    
	    printf("Pergunta 5) Quantas lavadoras de louça existem na casa?\n");
	    scanf("%i", &LavaLouca);
	    while (LavaLouca<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &LavaLouca);
	    }
	    switch (LavaLouca) {
	        case 0:
	            PLavaLouca=0;
	        	break;
	        case 1:
	            PLavaLouca=3;
	        	break;
	        case 2:
	            PLavaLouca=6;
	        	break;
	        default:
	            PLavaLouca=6;
	    }
	    
	    printf("Pergunta 6) Quantas geladeiras existem na casa?\n");
	    scanf("%i", &Geladeira);
	    while (Geladeira<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Geladeira);
	    }
	    switch (Geladeira) {
	        case 0:
	            PGeladeira=0;
	        	break;
	        case 1:
	            PGeladeira=2;
	        	break;
	        case 2:
	            PGeladeira=3;
	        	break;
	        default:
	            PGeladeira=5;
	    }
	    
	    printf("Pergunta 7) Quantos freezers existem na casa?\n");
	    scanf("%i", &Freezer);
	    while (Freezer<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Freezer);
	    }
	    switch (Freezer) {
	        case 0:
	            PFreezer=0;
	        	break;
	        case 1:
	            PFreezer=2;
	        	break;
	        case 2:
	            PFreezer=4;
	        	break;
	        default:
	            PFreezer=6;
		}
		
	    printf("Pergunta 8) Quantas Lavadoras de Louça existem na casa?\n");
	    scanf("%i", &LavaRoupa);
	    while (LavaRoupa<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &LavaRoupa);
	    }
	    switch (LavaRoupa) {
	        case 0:
	            PLavaRoupa=0;
	        	break;
	        case 1:
	            PLavaRoupa=2;
	        	break;
	        case 2:
	            PLavaRoupa=4;
	        	break;
	        default:
	            PLavaRoupa=6;
	    }
	    
	    printf("Pergunta 9) Quantos aparelhos de DVD existem na casa?\n");
	    scanf("%i", &Dvd);
	    while (Dvd<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Dvd);
	    }
	    switch (Dvd) {
	        case 0:
	            PDvd=0;
	        	break;
	        case 1:
	            PDvd=1;
	        	break;
	        case 2:
	            PDvd=3;
	        	break;
	        case 3:
	            PDvd=4;
	        	break;
	        default:
	            PDvd=6;
	    } 
		
	    printf("Pergunta 10) Quantos aparelhos Micro-Ondas existem na casa?\n");
	    scanf("%i", &MicroOndas);
	    while (MicroOndas<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &MicroOndas);
	    }
	    switch (MicroOndas) {
	        case 0:
	            PMicroOndas=0;
	        	break;
	        case 1:
	            PMicroOndas=2;
	        	break;
	        default:
	        	PMicroOndas=4;
	    }
	    
	    printf("Pergunta 11) Quantas Motocicletas existem na casa?\n");
	    scanf("%i", &Moto);
	    while (Moto<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Moto);
	    }
	    switch (Moto) {
	        case 0:
	            PMoto=0;
	        	break;
	        case 1:
	            PMoto=1;
	        	break;
	        default:
	            PMoto=3;
	    }
	    
	    printf("Pergunta 12) Quantas Secadoras de Roupa existem na casa?\n");
	    scanf("%i", &SecadoraRoupa);
	    while (SecadoraRoupa<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &SecadoraRoupa);
	    }
	    switch (SecadoraRoupa) {
	        case 0:
	            PSecadoraRoupa=0;
	        	break;
	    default:
	            PSecadoraRoupa=2;
		}
		
		//Início da Parte 2
		//Aqui, apresentei todas as alternativas com o respectivo número da resposta, junto com um tutorial de como responder corretamente.
		//A estrutura utilizada é: printf(pergunta), scanf(resposta), while(condição){mecânica em loop} para verificar a validade da resposta e
		//switch(condição){case-break} compondo a lógica de tratamento/salvamento de pontos.
	    printf("\n\nSegunda parte\n");
	    printf("\nPara responder a partir de agora, basta digitar o número da resposta desejada e apertar enter");
	    printf("\nO número estará indicado antes do texto da resposta");
	    printf("\n\nPergunta 13) Qual o grau de escolaridade do chefe da família?");
	    printf("\n(1) Analfabeto/Fundamental I Incompleto");
	    printf("\n(2) Fundamental I completo/Fundamental II incompleto");
	    printf("\n(3) Fundamental II Completo/Médio incompleto");
	    printf("\n(4) Médio Completo/Superior Incompleto");
	    printf("\n(5) Superior Completo\n");
	    scanf("%i", &Escolaridade);
	    while (Escolaridade<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Escolaridade);
	    }
	    switch (Escolaridade) {
	        case 1:
	            PEscolaridade=0;
	        	break;
	        case 2:
	            PEscolaridade=1;
	            break;
	        case 3:
	            PEscolaridade=2;
	            break;
	        case 4:
	            PEscolaridade=4;
	            break;
		default:
	            PEscolaridade=7;
		}
	    
	    printf("\nSua casa possui água encanada?");
	    printf("\n(1) Sim");
	    printf("\n(2) Não\n");
	    scanf("%i", &Agua);
	    while (Agua<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Agua);
	    }
		switch (Agua) {
	        case 1:
	            PAgua=4;
	            break;
	    default:
	    		PAgua=0;
	    }
	    
	    printf("\nExiste pavimentação asfáltica na rua de sua casa?");
	    printf("\n(1) Sim");
	    printf("\n(2) Não\n");
	    scanf("%i", &Pavimentacao);
	    while (Pavimentacao<0) {
	        printf("\nValor inválido! Por favor digite um valor maior que zero\n");
	        scanf("%i", &Pavimentacao);
	    }
		switch (Pavimentacao) {
	        case 1:
	            PPavimentacao=2;
	            break;
	    default:
	    		PPavimentacao=0;
	    }		
	    
		//Soma dos pontos
		Pontos1=PBanheiro + PEmpregado + PAutomovel + PComputador + PLavaLouca + PGeladeira + PFreezer + PLavaRoupa + PDvd + PMicroOndas + PMoto + PSecadoraRoupa;
		Pontos2=PEscolaridade+PAgua+PPavimentacao;
	    PontosTotal=Pontos1+Pontos2;
	    
	    //Apresentação dos resultados finais (Pontuação, Classe), agradecimentos e autoria.
	    printf("\nSua pontuação final é: %i", PontosTotal);
	    if ((PontosTotal>44) && (PontosTotal<101)){
	        printf("\nVocê é Classe A");
	    } 
	    else if ((PontosTotal>37) && (PontosTotal<45)){
	        printf("\nVocê é Classe B1");
	    } 
	    else if ((PontosTotal>28) && (PontosTotal<38)){
	        printf("\nVocê é Classe B2");
	    }
	    else if ((PontosTotal>22) && (PontosTotal<29)){
	        printf("\nVocê é Classe C1");
	    }
	    else if ((PontosTotal>16) && (PontosTotal<23)){
	        printf("\nVocê é Classe C2");
	    }
	    else if ((PontosTotal>4) && (PontosTotal<17)){
	        printf("\nVocê é Classe D");
	    }
	    else if ((PontosTotal>-1) && (PontosTotal<5)){
	        printf("\nVocê é Classe E");
	    }
	    printf("\nO Governo Federal agradece pela contribuição com o Senso IBGE 2018.");
	    printf("\nPowered by Gustavo Furlan");
	} 
