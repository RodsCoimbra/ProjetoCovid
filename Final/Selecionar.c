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
