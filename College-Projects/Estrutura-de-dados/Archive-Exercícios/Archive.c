#include <stdio.h>

main()
{
    char url[] = "Archive.txt", ch;
    FILE *arq;
    
    arq = fopen(url, "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo\n");
    }
    else
    {
        while((ch = fgetc(arq)) != EOF )
        {
            putchar(ch);
        }
        fclose(arq);
    }
    getchar();
    return 0;
}
