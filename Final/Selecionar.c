#include "Projeto_covid.h"


Detalhes* selecionar (Pais* head_pais, int select)
{
    Detalhes* aux = NULL, *atual, *remover = NULL;
    int num_week = -1; //como o numero de infetados/mortos não pode ser negativo então ele guarda sempre o primeiro valor dos detalhes no aux
    double num_racio = -1;
    for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)     // Executa até percorrer a lista toda
    {
        if(((strcmp(atual->indic,"cases")== 0) && (atual->week_count > num_week) && (select== 1)) || ((strcmp(atual->indic,"deaths")== 0) && (atual->week_count > num_week) && (select == 2)) || ((strcmp(atual->indic,"cases") == 0) && (atual->lastfteen > num_racio) && (select== 3)) || ((strcmp(atual->indic,"deaths")== 0) && (atual->lastfteen > num_racio) && (select == 4)))
            // Este if serve para os 4 tipos de seleção
        {
            free(aux);
            aux = atual;
            num_week = atual->week_count;
            num_racio = atual->lastfteen;
        }
        else
        {
            free (remover);
            remover = atual;
        }
    }
    free (remover);
    return  aux;
}


void Escolher_sel(Pais* head, char* selecao)
{
    Pais* atual;
    if(strcmp(selecao, "inf") == 0)                              // Compara as seleções que existem com o argumento do -D do utilizador
    {
        for (atual = head ; atual != NULL; atual = atual->nextP) // Vai passando todos os paises e fazendo e chamando a função selecionar para cada um deles
        {
            atual->nextD = selecionar(atual, 1);                 // o primeiro elemento da lista dos detalhes é substituido pelo elemento que o selecionar retornar
            atual->nextD->nextD = NULL;                          // Como o -D só seleciona um elemento da lista de detalhes por pais, então o a seguir a esse terá de ser nulo
        }
    }
    else if(strcmp(selecao, "dea") == 0)                        //todos os outros tem o mesmo raciocio que o primeiro
    {
        for (atual = head ; atual != NULL; atual = atual->nextP)
        {
            atual->nextD = selecionar(atual, 2);
            atual->nextD->nextD = NULL;
        }
    }
    else if(strcmp(selecao, "racioinf") == 0)
    {
        for (atual = head ; atual != NULL; atual = atual->nextP)
        {
            atual->nextD = selecionar(atual, 3);
            atual->nextD->nextD = NULL;
        }
    }
    else if(strcmp(selecao, "raciodea") == 0)
    {
        for (atual = head ; atual != NULL; atual = atual->nextP)
        {
            atual->nextD = selecionar(atual, 4);
            atual->nextD->nextD = NULL;
        }
    }
}
