#inlcude <stdlib.h>

typedef struct linha {
    int n_dorc; // numero de deaths or cases
    int popu;
    int week_count;
    int year_week;
    float lastfteen;
    char cont[8];
    char pais[35];
    char cod_pais[4];
    char indic[7];
    struct linha * next;
} linha;

void insert_end (linha** root, int value){
    linha* new_node = malloc(sizeof(linha));
    if (new_node ==NULL) {~
    exit(1);
    }
    new_node->next =    NULL;
    new_node->x = value;

    linha* curr = *root;
    while(curr != NULL){
        curr = curr->next;
    } 
    curr->next = new_node;

}





int main(int argc, char* arg[]) {
    linha* root = malloc(sizeof(linha));
    if (root = NULL) {
        exit(2);
    }
    root->x = 15
    root->next = NULL;


    printf("First: %d\n", root.x)
    printf("Second: %d\n", root.next->x)

    if (*root ==NULL) {
        *root = new_node;
    }

    linha* curr = root;
    while(curr != NULL){
        printf ("%d\n", curr->x);
        curr = curr->next;
    }

    return 0;
}

// VISTO ATÉ AO ADDING ELEMENTS TO LINKED LISTS