#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct detalhes { // lista que está dentro da lista "pais"
    int n_dorc; // numero de deaths or cases
    int week_count;
    int year_week;
    float lastfteen;
    char indic[7];
    struct detalhes *nextD; // nextD é o pointer do detalhe seguinte
} detalhes;

typedef struct pais {
    char pais[35];
    char cod_pais[4];
    char cont[8];
    int popu;
    detalhes *nextD;
    struct pais *nextP; // nextP é o pointer do pais seguinte
} pais;

pais *inserir_paises (struct detalhes **head, int popu, char cont, char pais, char cod_pais){
    struct detalhes, *temp, *curr;
    
}

//  insert lists of integers in a list

detalhes *inserir_detalhes (pais **pais_list, detalhes *head){
    pais *aux,*atual;
    aux=(pais*)malloc(sizeof(pais));
    aux->nextD = head;
    aux->nextD->nextD = NULL;
    if((*pais_list)==NULL){
        (*pais_list) = aux;
    }
    else{
        atual=(*pais_list);
        while(atual->nextD!=NULL){
            atual=atual->nextD;
        }
        atual->nextD=aux;
    
    }
}
/*
int main(int argc, char arg[]) {
    pais* root = malloc(sizeof(pais));
    if (root = NULL) {
        exit(2);
    }
    root->x = 15
    root->next = NULL;


    printf("First: %d\n", root.x)
    printf("Second: %d\n", root.next->x)

    if (*root ==NULL) {
        root = novo_det;
    }

    pais curr = root;
    while(curr != NULL){
        printf ("%d\n", curr->x);
        curr = curr->next;
    }

    return 0;
}*/