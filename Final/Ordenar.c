#include "Projeto_covid.h"


int valores(Pais* head_pais, int ordena, char*semana)
{
    Detalhes* atual;
    if(ordena == 3)
    {
        for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)
        {
            if((strcmp(atual->indic,"cases")==0) && (strcmp(atual->year_week, semana) ==0))
            {
                return atual->week_count;
            }
        }
    }

    else if(ordena == 4)
    {
        for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)
        {
            if((strcmp(atual->indic,"deaths")==0) && (strcmp(atual->year_week, semana) ==0))
            {
                return atual->week_count;
            }
        }
    }
    return 0;
}

Pais* ordenar(Pais* head, int ordena, char* semana)
{

    int flag = 0, x = 0, y = 0;
    Pais* esq, *drt, *paux, aux, *d, *e;
    paux = &aux;            //Cria auxiliar antes, pois vai mexer nos dois blocos da frente
    paux->nextP = head;
    while(flag == 0)
    {
        esq = paux;
        drt = paux -> nextP;
        flag = 1;

        while(drt-> nextP != NULL)
        {
            if(ordena == 3 || ordena == 4)
            {
                x = valores(drt, ordena, semana);
                y = valores(drt->nextP, ordena, semana);
            }
            if ((strcmp(drt->pais, drt->nextP->pais) > 0 && ordena == 1 )|| ((drt->popu) < (drt->nextP->popu) && ordena == 2) || (x < y) ||(x==y && strcmp(drt->pais, drt->nextP->pais) > 0 && (ordena == 3 || ordena == 4)))
            {
                flag = 0;
                d = esq->nextP;
                e = drt->nextP->nextP;
                esq->nextP = drt->nextP;
                drt->nextP->nextP = d;
                drt->nextP = e;
            }
            esq = drt;
            if (drt->nextP != NULL)
            {
                drt = drt->nextP;
            }
        }
    }
    head = paux->nextP;
    return head;
}
