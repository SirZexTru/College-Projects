#include <stdio.h>

// Criar um codigo onde o usuario defina qunatos vertices ele possui, e quantas e quais adjacencias ele possui,
// construindo assim uma matriz booleana, onde as celulas que possuem "1" representam os vertices que se ligam

menu();
novaAresta();

main()
{
    int vertices = 0;
    printf("Informe quantos vertices existem: ");
    scanf("%i", &vertices);
    int matriz[vertices][vertices];
    system("cls");
    menu();
    return 0;
}

menu()
{


}
