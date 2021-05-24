#include "Projeto_covid.h"

Pais* restringir_pop(Pais* head, int pop, int restringir)
{
    Pais aux;
    Pais* paux= &aux,*atual, *remover = NULL;
    paux->nextP = head;
    atual = paux;
    while(atual->nextP !=  NULL)
    {
        if(((atual->nextP->popu <= pop*1000 ) && (restringir == 1)) || ((atual->nextP->popu >= pop*1000) && (restringir == 2)))
        {
            remover = atual->nextP;
            atual->nextP = atual->nextP->nextP;
            Detalhes* remover2;
            while(remover->nextD != NULL)
            {
                remover2 = remover->nextD;
                remover->nextD = remover->nextD->nextD;
                free(remover2);
            }
            free(remover);

        }
        else
        {
            atual = atual->nextP;
        }
    }
    return paux->nextP;
}

Detalhes* restringir_week(Pais* head_pais, char* ano1, char* ano2, int restringir)
{
    Detalhes aux;
    Detalhes* atual,*paux = &aux, *remover = NULL;
    paux->nextD = head_pais->nextD;
    atual = paux;
    char ivrt[8];                   //variavel para inverter caso ano1 > ano2
    if((strcmp(ano1,ano2) > 0) && (restringir == 4))       // inversão caso ano1 > ano2
    {
        strcpy(ivrt,ano1);
        strcpy(ano1, ano2);
        strcpy(ano2, ivrt);
    }
    while(atual->nextD !=  NULL)
    {
        if((((strcmp(atual->nextD->year_week, ano1)) != 0) && (restringir == 3)) || (((strcmp(atual->nextD->year_week, ano1) < 0) || (strcmp(atual->nextD->year_week, ano2) > 0))  && (restringir == 4)))
        {
            remover = atual->nextD;
            atual->nextD = atual->nextD->nextD;
            free(remover);
        }
        else
        {
            atual = atual->nextD;
        }
    }
    return paux->nextD;
}

