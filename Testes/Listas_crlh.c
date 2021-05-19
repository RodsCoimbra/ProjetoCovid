#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct detalhes { // lista que está dentro da lista "pais"
    int n_dorc; // numero de deaths or cases
    int popu;
    int week_count;
    int year_week;
    float lastfteen;
    char cont[8];
    char pais[35];
    char cod_pais[4];
    char indic[7];
    struct detalhes *next;
} detalhes;

typedef struct pais {   // pais é a nova "linha"
    struct detalhes *start;
    struct pais *pais_next;
} pais;

void inserir_detalhes (struct detalhes **head, int n_dorc, int popu, int week_count, int year_week, float lastfteen, char cont, char pais, char cod_pais, char indic){
    struct detalhes, *temp, *curr;
    temp = malloc(sizeof(struct detalhes));
    temp->n_dorc = n_dorc;
    //inserir o resto do dados//
    temp->next = NULL;

    if (*head == NULL) {
        *head = temp;
    }
    else{
        current =(*head);
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=temp;
    }
}

//  insert lists of integers in a list

void inserir_paises (struct pais **pais_list,struct detalhes *head){
    struct list *temp,*current;
    temp=malloc(sizeof(struct list));
    temp->start=head;
    temp->listnext=NULL;
    if((*pais_list)==NULL){
        (*pais_list)=temp;
    }
    else{
        current=(*pais_list);
        while(current->listnext!=NULL){
            current=current->listnext;
        }
        current->listnext=temp;
    }
}

// Show all the list with their data

void show(struct list *pais_list){
    int i=1;
    struct pais *current;
    struct detalhes *currentlist;
    current=pais_list;
    while(current!=NULL){
        currentlist=current->start;
        printf("List %d: ",i);
        while(currentlist!=NULL){
            printf("%d ",currentlist->_);
            currentlist=currentlist->next;
        }
        i++;
        printf("\n");
        current=current->listnext;
    }
}

int main(){
    struct node *head1=NULL,*head2=NULL,*head3=NULL; // 3 lists of integers
    struct list *pais_list=NULL;  // pais_list will be the head of lists of list
    insertNode(&head1,20);  // inserting in first list
    insertNode(&head1,13);
    insertNode(&head1,22);
    insertNode(&head1,18);
    insertNode(&head2,42);  // inserting in second list
    insertNode(&head2,15);
    insertNode(&head3,12);  // inserting in third list
    insertNode(&head3,14);
    insertNode(&head3,28);
    insertList(&pais_list,head1); // inserting lists in list
    insertList(&pais_list,head2);
    insertList(&pais_list,head3);
    show(pais_list);
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