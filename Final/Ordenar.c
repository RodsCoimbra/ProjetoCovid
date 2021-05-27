#include "Projeto_covid.h"
/** Comentários mais completos de cada função no .h
*/


/** \brief Função usada para a ordenação por infetados ou por mortes. Esta passa por todos os valores da lista secundária(lista dos Detalhes)
 *         e retorna o valor de week_count quando, tanto a razão(cases ou deaths) como a semana são iguais às especificadas pelo utilizador
 */
int valores(Pais* head_pais, int ordena, char*semana)
{
    Detalhes* atual;
    if(ordena == 3) // Executa se a ordenação for por número de infetados
    {
        for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)  // Executa até chegar ao final da lista de detalhes daquele pais
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
    return -1;  // Retorna o valor de -1 (pois week_count nunca pode ser negativo) para servir de flag na função ordenar
}

/** \brief Função que ordena todos os tipos de -S, com base no algoritmo de bubble sort
 */
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
                x = valores(drt, ordena, semana);        // x vai conter o valor do week_count do primeiro elemento a comparar
                y = valores(drt->nextP, ordena, semana); // y vai conter o valor do week_count do segundo elemento a comparar
            }
            if ((strcmp(drt->pais, drt->nextP->pais) > 0 && ordena == 1 )|| ((drt->popu) < (drt->nextP->popu) && ordena == 2) || ((drt->popu) == (drt->nextP->popu) && strcmp(drt->pais, drt->nextP->pais) > 0 && ordena == 2) || (x < y) ||((x==y && strcmp(drt->pais, drt->nextP->pais) > 0 && (ordena == 3 || ordena == 4) && x != -1)))
            {
                // faz a comparação dos valores e faz a troca de posições, variaveis "d" e "e" de auxilio
                flag = 0;
                d = esq->nextP;             //guarda o esq->nextP em "d" para depois passar para o drt->nextP->nextP
                e = drt->nextP->nextP;      //guarda o esq->nextP em "e" para depois passar para o drt->nextP
                esq->nextP = drt->nextP;
                drt->nextP->nextP = d;
                drt->nextP = e;
                //Caso cada bloco representasse um número, sendo esq = 1 e drt = 2, então se a ordem fosse 1->2->3->4, ele basicamente faz 1->3->2->4
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

/** \brief Função que escolhe qual o modo de ordenação pretendido pelo utilizador
 */
Pais* Escolher_orde(Pais* head, char* ordenacao, char* ano_ord)
{
    if(strcmp(ordenacao,"alfa") == 0)       //Compara as ordenações que existem com o argumento do -S do utilizador
    {
        head = ordenar(head, 1, NULL);      //Cada número(2º argumento passado na função) representa um tipo de ordenação, sendo 1 é -S alfa; 2 é -S pop; 3 é -S inf; 4 é -S dea
    }
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
