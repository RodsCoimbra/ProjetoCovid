#include "Projeto_covid.h"

Pais* verificacao(char* cod_pais,Pais* head)
{
    Pais* aux;
    if (head == NULL)
    {
        return NULL;
    }
    for(aux = head; aux != NULL; aux = aux->nextP)
    {
        if(strcmp(cod_pais,aux->cod_pais) == 0)    //comparacao com o codigo dos paises
        {
            return aux;
        }
    }
    return NULL;
}

void criarD(Detalhes* deta,char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Detalhes* aux = deta;
    Detalhes* deta2 = (Detalhes*) calloc(1,sizeof(Detalhes));
    while(aux->nextD != NULL)
    {
        aux = aux->nextD;
    }
    aux->nextD = deta2;

    deta2->n_dorc = n_dorc;
    deta2->lastfteen = lastfteen;
    deta2->week_count = week_count;
    strcpy(deta2->year_week, year_week);
    strcpy(deta2->indic, indic);
}

Pais* criarP (Pais* head, char* pais, char* cod_pais, char* cont,int popu, char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Pais* P_atual;
    P_atual = verificacao(cod_pais, head);
    if (P_atual != NULL)
    {
        criarD(P_atual->nextD, indic, week_count, year_week, lastfteen, n_dorc);
        return head;
    }

    Pais* novo = (Pais*) calloc (1,sizeof(Pais));
    Detalhes* deta = (Detalhes*) calloc(1,sizeof(Detalhes)); //deta=*detalhes

    if (novo == NULL)
    {
        help(3);
    }
    if (deta == NULL)
    {
        help(3);
    }
    novo->popu = popu;
    strcpy(novo->cont, cont);
    strcpy(novo->pais, pais);
    strcpy(novo->cod_pais, cod_pais);
    if (head == NULL)
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
    while(aux->nextP != NULL)
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

    while(head != NULL)
    {
        while(head->nextD != NULL)
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
