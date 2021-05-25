#include "Projeto_covid.h"

Pais* restringir_pop(Pais* head, long long int pop, int restringir)
{
    Pais aux;   // variavel para auxilio da funcao
    Pais* paux= &aux,*atual, *remover = NULL;
    paux->nextP = head; // coloca o endereço do primeiro Pais (head)
    atual = paux;
    while(atual->nextP !=  NULL)     // executa até ao final da lista (ultimo_elemento_da_lista->nextP = NULL)
    {
        if(((atual->nextP->popu <= pop*1000 ) && (restringir == 1)) || ((atual->nextP->popu >= pop*1000) && (restringir == 2))) // este IF aplica-se tanto para verificar quando a população do pais é inferior que o valor escolhido como quando é superior
        {
            remover = atual->nextP;
            atual->nextP = atual->nextP->nextP;
            Detalhes* remover2;
            while(remover->nextD != NULL)   // Executa enquanto não chegar ao ultimo elememento da lista de detalhes, e dá free dos nodes_detalhes que não cumprem a condição
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
    char ivrt[8];    //variavel para inverter caso ano1 > ano2
    if((strcmp(ano1,ano2) > 0) && (restringir == 4))       // inversão caso ano1 > ano2
    {
        strcpy(ivrt,ano1);
        strcpy(ano1, ano2);
        strcpy(ano2, ivrt);
    }
    while(atual->nextD !=  NULL)    // Executa enquanto não chegar ao ultimo elememento da lista de detalhes, e dá free dos nodes_detalhes que não cumprem a condição
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

