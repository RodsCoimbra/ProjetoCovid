#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct linha {
    int n_inf;
    int n_mort;
    int popu;
    int week_count;
    int n_week;
    int lastfteen;
    char pais;
    char cod_pais[3];
    char indic[6]; // 6? porque deaths é o maior que pode ser escrito lá???
    struct linha * next; 
} linha;


int main (int argc, char* argv[]){
    linha root, elemt2, elemt3, elemt4;
    root.n_inf = 1000;
    root.next = &elemt2;
    elemt2.n_inf = 2000;
    elemt2.next = &elemt3;
    elemt3.n_inf = 3000;
    elemt3.next = &elemt4;
    elemt4.n_inf = 4000;
    elemt4.next = NULL;

    printf("Root: %d \n", root.n_inf);
    printf("Root: %d\n", elemt2.n_inf);
    printf("Root: %d\n", elemt3.n_inf);
    printf("Root: %d\n", elemt4.n_inf);
    

    return 0;
}