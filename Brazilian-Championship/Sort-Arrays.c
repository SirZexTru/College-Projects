#include <stdio.h>
#include <stdlib.h>

int array1[] = {1, 7, 3, 9, 5};
double array2[] = {1.1, 7.7, 3.3, 9.9, 5.5};

int compare (const void * a, const void * b) {
    double diff = array2[*(int*)a] - array2[*(int*)b];
    return  (0 < diff) - (diff < 0);
}

int main(void) {
    int perm[5], i;
    int res[5];
    for (i = 0 ; i != 5 ; i++) {
        perm[i] = i;
    }
    qsort (perm, 5, sizeof(int), compare);
    for (i = 0 ; i != 5 ; i++) {
        res[i] = array1[perm[i]];
    }
    for (i = 0 ; i != 5 ; i++) {
        printf("%d\n", res[i]);
    }
    getch();
    return 0;
}