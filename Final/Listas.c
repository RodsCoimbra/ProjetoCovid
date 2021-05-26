#include "Projeto_covid.h"

Pais* encontra_pais(char* cod_pais,Pais* head)
{
    Pais* aux;
    if (head == NULL) // Se a lista não tiver nenhum node
    {
        return NULL;
    }
    for(aux = head; aux != NULL; aux = aux->nextP)  // Executa até percorrer a lista toda
    {
        if(strcmp(cod_pais,aux->cod_pais) == 0)     //comparacao com o codigo dos paises, se o pais já tiver um node_pais criado dá return do endereço desse node
        {
            return aux;
        }
    }
    return NULL;    //caso não encontre retorna NULL
}

void criarD(Detalhes* deta,char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Detalhes* aux = deta;
    Detalhes* deta2 = (Detalhes*) calloc(1,sizeof(Detalhes));
    while(aux->nextD != NULL)   // Anda com o aux até ao final da lista de detalhes daquele pais para depois colocar o novo_detalhes
    {
        aux = aux->nextD;
    }
    aux->nextD = deta2;

    deta2->n_dorc = n_dorc;
    deta2->lastfteen = lastfteen;    // O node_detalhes recebe os dados do ficheiro lido
    deta2->week_count = week_count;
    strcpy(deta2->year_week, year_week);
    strcpy(deta2->indic, indic);
}

Pais* criarP (Pais* head, char* pais, char* cod_pais, char* cont,int popu, char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Pais* P_atual;
    P_atual = encontra_pais(cod_pais, head);
    if (P_atual != NULL)    // Caso em que o node daquele pais já existe e portanto só adiciona um node aos detalhes desse pais
    {
        criarD(P_atual->nextD, indic, week_count, year_week, lastfteen, n_dorc);
        return head;
    }
    //Caso seja nulo, ou seja, não exista qualquer registo daquele pais então cria mais um node de pais e um node de detalhes associado a este
    Pais* novo = (Pais*) calloc (1,sizeof(Pais));
    Detalhes* deta = (Detalhes*) calloc(1,sizeof(Detalhes)); //deta significa detalhes

    if (novo == NULL)       //caso em que não consegue alocar novo
    {
        help(3);
    }
    if (deta == NULL)       //caso em que não consegue alocar deta
    {
        help(3);
    }
    novo->popu = popu;
    strcpy(novo->cont, cont);
    strcpy(novo->pais, pais);
    strcpy(novo->cod_pais, cod_pais);
    if (head == NULL)       // se não houver nenhum elemento na lista, define os detalhes para os campos respetivos e retorna o endereco de "novo" para este servir de cabeça da lista
    {
        novo->nextP = NULL;
        novo->nextD = deta;
        deta->n_dorc = n_dorc;
        deta->lastfteen = lastfteen;
        deta->week_count = week_count;
        strcpy(deta->year_week, year_week);
        strcpy(deta->indic, indic);
        return novo;
    }
    Pais* aux = head;
    while(aux->nextP != NULL)   // Avança até ao final da lista de paises
    {
        aux = aux->nextP;
    }
    aux->nextP = novo;
    novo->nextD = deta;
    deta->n_dorc = n_dorc;
    deta->lastfteen = lastfteen;
    deta->week_count = week_count;
    strcpy(deta->year_week, year_week);
    strcpy(deta->indic, indic);
    return head;
}

void apagar(Pais* head)
{

    Pais* aux;
    Detalhes* aux2;

    while(head != NULL)     // Executa até encontrar o final da lista
    {
        while(head->nextD != NULL)  // Até chegar ao final da lista remove todos os nodes
        {
            aux2 = head->nextD;
            head->nextD = head->nextD->nextD;
            free(aux2);
        }
        aux = head;
        head = head->nextP;
        free(aux);
    }
}
