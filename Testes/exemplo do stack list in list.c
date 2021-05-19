#include <stdio.h>
#include <stdlib.h>

// for list of Intergers
struct node{
    int Data;
    struct node *next;
};

// this is for list of nodes i.e list of lists
struct list{
    struct node *start;
    struct list *listnext;
};


// insert integers in list 

void insertNode(struct node **head ,int data){
    struct node *temp,*current;
    temp=malloc(sizeof(struct node));
    temp->Data=data;
    temp->next=NULL;

    if((*head)==NULL){
        (*head)=temp;
    }
    else{
        current=(*head);
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=temp;
    }
}

//  insert lists of integers in a list

void insertList(struct list **Listhead,struct node *head){
    struct list *temp,*current;
    temp=malloc(sizeof(struct list));
    temp->start=head;
    temp->listnext=NULL;
    if((*Listhead)==NULL){
        (*Listhead)=temp;
    }
    else{
        current=(*Listhead);
        while(current->listnext!=NULL){
            current=current->listnext;
        }
        current->listnext=temp;
    }
}

// Show all the list with their data

void show(struct list *Listhead){
    int i=1;
    struct list *current;
    struct node *currentlist;
    current=Listhead;
    while(current!=NULL){
        currentlist=current->start;
        printf("List %d: ",i);
        while(currentlist!=NULL){
            printf("%d ",currentlist->Data);
            currentlist=currentlist->next;
        }
        i++;
        printf("\n");
        current=current->listnext;
    }
}

int main(){
    struct node *head1=NULL,*head2=NULL,*head3=NULL; // 3 lists of integers
    struct list *Listhead=NULL;  // Listhead will be the head of lists of list
    insertNode(&head1,20);  // inserting in first list
    insertNode(&head1,13);
    insertNode(&head1,22);
    insertNode(&head1,18);
    insertNode(&head2,42);  // inserting in second list
    insertNode(&head2,15);
    insertNode(&head3,12);  // inserting in third list
    insertNode(&head3,14);
    insertNode(&head3,28);
    insertList(&Listhead,head1); // inserting lists in list
    insertList(&Listhead,head2);
    insertList(&Listhead,head3);
    show(Listhead);
}