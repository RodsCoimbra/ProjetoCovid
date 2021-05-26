#include "Projeto_covid.h"


int valores(Pais* head_pais, int ordena, char*semana)
{
    Detalhes* atual;
    if(ordena == 3) // Executa se a ordenação for por número de infetados
    {
        for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)  // Executa até chegar ao final da lista de detalhes
        {
            if((strcmp(atual->indic,"cases")==0) && (strcmp(atual->year_week, semana) ==0)) // Retorna o valor de "atual->week_count"" se a semana e o indic(infetados) coresponderem
            {
                return atual->week_count;
            }
        }
    }

    else if(ordena == 4)
    {
        for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)
        {
            if((strcmp(atual->indic,"deaths")==0) && (strcmp(atual->year_week, semana) ==0))    // Retorna o valor de "atual->week_count"" se a semana e o indic(mortos) coresponderem
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
    paux->nextP = head;     // Cria um outro pointer para o endereço do primeiro node_pais
    /// Bubble sort
    while(flag == 0)    //Fazer enquanto a flag for 0, ou seja, enquanto não estiver tudo ordenado
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
                // faz a comparação dos valores e faz a troca de posições, variaveis "d" e "e" de auxilio
                flag = 0;
                d = esq->nextP;
                e = drt->nextP->nextP;
                esq->nextP = drt->nextP;
                drt->nextP->nextP = d;
                drt->nextP = e;
            }
            esq = drt;
            if (drt->nextP != NULL)  // Se a lista não tiver no final avança para o próximo pais
            {
                drt = drt->nextP;
            }
        }
    }
    head = paux->nextP;
    return head;
}


Pais* Escolher_orde(Pais* head, char* ordenacao, char* ano_ord)
{
    head = ordenar(head, 1, NULL);              //organiza sempre por ordem alfabetica para depois caso haja empate já vir organizado por ordem alfabetica
    if(strcmp(ordenacao,"alfa") == 0)           //apenas para se for esta opção passar os outros
    {}
    else if(strcmp(ordenacao,"pop") == 0)
    {
        head = ordenar(head, 2,NULL);
    }
    else if(strcmp(ordenacao,"inf") == 0)
    {
        head = ordenar(head, 3, ano_ord);
    }
    else if(strcmp(ordenacao,"dea") == 0)
    {
        head = ordenar(head, 4, ano_ord);
    }
    return head;
}
