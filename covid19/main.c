#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct Detalhes { // lista que está dentro da lista "pais"
    int n_dorc; // numero de deaths or cases
    int week_count;
    char year_week[8];
    double lastfteen;
    char indic[7];
    struct Detalhes *nextD; // nextD é o pointer do detalhe seguinte
} Detalhes;

typedef struct Pais {
    char pais[35];
    char cod_pais[4];
    char cont[8];
    int popu;
    Detalhes *nextD;
    struct Pais *nextP; // nextP é o pointer do pais seguinte
} Pais;

/*void inserir_detalhes (pais **pais_list, detalhes *head, int n_dorc, int week_count, int year_week, float lastfteen, char indic[7]){
    pais *aux,*atual;
    aux=(pais*)malloc(sizeof(pais));
    aux->nextD = head;
    if((*pais_list)==NULL){
        (*pais_list) = aux;
    }
    else{
        atual=(*pais_list);
        while(atual->nextD!=NULL){
            atual=atual->nextD;
        }
        atual->nextD=aux;
    }
}

pais *inserir_paises (struct detalhes **head, int popu, char cont, char pais, char cod_pais){

}*/


void help(int helpvar)
{
    switch (helpvar)
    {
    case 1:
        printf("Erro! Problema nos argumentos de entrada");
        break;
    case 2:
        printf("Nao foi possivel ler o ficheiro de entrada.");
        break;
    case 3:
        printf("Nao foi possivel alocar memória.");
        break;
    }
    exit(-1);
}


Pais* verificacao(char* cod_pais,Pais* head){
    Pais* aux;
    if (head == NULL)
    {
        return NULL;
    }
    for(aux = head;aux != NULL;aux = aux->nextP){
        if(strcmp(cod_pais,aux->cod_pais) == 0){
        return aux;
        }
    }
    return NULL;
    }

void criarD(Detalhes* deta,char* indic, int week_count, char* year_week, double lastfteen, int n_dorc){
    Detalhes* aux = deta;
    Detalhes* deta2 = (Detalhes*) malloc(sizeof(Detalhes));
    while(aux->nextD != NULL){
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
    if (P_atual != NULL){
        criarD(P_atual->nextD, indic, week_count, year_week, lastfteen, n_dorc);
        return head;
    }

    Pais* novo = (Pais*) malloc (sizeof(Pais));
    Detalhes* deta = (Detalhes*) malloc(sizeof(Detalhes)); //deta=*detalhes

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
    if (head == NULL){
        novo->nextP = NULL;
        novo->nextD = deta;
        return novo;
    }
    Pais* aux = head;
    while(aux->nextP != NULL){
         aux = aux->nextP;
    }
    aux->nextP = novo;
    aux->nextD = deta;
    criarD(deta, indic, week_count, year_week, lastfteen, n_dorc);
    return head;
}





/** \brief
*
* \param sep char
* \param str char*
* \return char*
*
*/
char* separar(char sep, char* str, char troca)
{
    int i;
    char *psep = NULL;
    for(i=0; str[i] != EOF ; i++)
    {
        if(str[i] == sep)
        {
            str[i] = troca;
            psep = &str[i+1];
            break;
        }
    }
    return psep;
}


/*void apagar(linha* ende)
{

    linha* aux;

    while(ende != NULL)
    {
        aux = ende;
        ende = ende->next;
        free(aux);
    }
}*/




/** \brief
 *
 * \param argc int
 * \param argv[] char*
 * \return int
 *
 */
int main(int argc, char *argv[])
{
    int opt, numero = 0, semana1, semana2, ano1, ano2, anod, semanad;
    char ordem[6] = {""}, leitura[35], selecao[9], ordenacao[5], l_fich[maxficheiro], e_fich[maxficheiro], l_ext[4], e_ext[4], ler[max_linha], *pend, *pend2;
    opterr = 0;
    while((opt= getopt(argc, argv,"P:L:D:S:i:o:"))!= -1 ) // loop que recebe as informacoes do utilizador no incio do programa
    {
        switch (opt)
        {
        case 'P':
            sscanf(optarg," %s", ordem);
            if (strcmp("min", ordem) == 0 || strcmp("max", ordem) == 0)
            {
                sscanf(optarg + 4," %d", &numero);
            }
            else if (strcmp("date", ordem) == 0)
            {
                sscanf(optarg + 5," %d-%d", &ano1, &semana1);
            }
            else if (strcmp("dates", ordem) == 0)
            {
                sscanf(optarg + 6," %d-%d", &ano1, &semana1);
                sscanf(optarg + 14," %d-%d", &ano2, &semana2);
            }
            else
            {
                help(1);
            }
            break;
        case 'L':
            sscanf(optarg," %s", leitura);
            break;
        case 'D':
            sscanf(optarg," %s", selecao);
            break;
        case 'S':
            sscanf(optarg," %s", ordenacao);
            if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0)
            {
                sscanf(optarg + 4," %d-%d", &anod, &semanad);
            }
            break;

        case 'i':
            sscanf(optarg," %s", l_fich);
            pend = separar('.', l_fich,'.');
            sscanf(pend,"%s", l_ext);
            break;

        case 'o':
            sscanf(optarg," %s", e_fich);
            pend = separar('.', e_fich,'.');
            sscanf(pend,"%s", e_ext);
            break;

        default:    // Mostra a mensagem se for escrito um caracter sem sentido no programa
        {
            help(1);
        }
        }
    }

    FILE *lp;
    FILE *ep;
    //Tipo de leitura
    if(strcmp(l_ext,"csv") == 0)
    {
        if ((lp = fopen(l_fich, "r"))==NULL)
        {
            help(2);
        }
    }
    else if((strcmp(l_ext,"dat")) == 0)
    {
        if ((lp = fopen(l_fich, "rb")) ==NULL)
        {
            help(2);
        }
    }
    else
    {
        help(2);
    }

    //Tipo de escrita
    if(strcmp(e_ext,"csv") == 0)
    {
        if ((ep = fopen(e_fich, "w"))==NULL)
        {
            help(2);
        }
    }
    else if((strcmp(e_ext,"dat")) == 0)
    {
        if ((ep = fopen(e_fich, "wb"))==NULL)
        {
            help(2);
        }
    }
    else
    {
        help(2);
    }
    Pais* head = NULL;
    //Leitura do ficheiro
    if (fgets(ler, max_linha, lp)==NULL)
    {
        help(2);
    }
    if(strcmp(e_ext,"csv") == 0)
    {
        fprintf(ep, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n"); //titulo
    }
    // Ler linhas
    Pais aux;
    Detalhes aux2;
    while(fgets(ler, max_linha, lp)!= NULL){
        pend = separar(',', ler,'\0');
        sscanf(ler, " %[^,]", aux.pais);  //Como pode ter espaços usei [^,] para ele ler tudo até ao terminador da string(já que as virgulas foram substituidas então não à problema)
        pend2 = separar(',', ler,'\0');
        sscanf(pend, " %s", aux.cod_pais);
        pend = separar(',', ler,'\0');
        sscanf(pend2, " %s", aux.cont);
        pend2 = separar(',', ler,'\0');
        sscanf(pend, " %d", &(aux.popu));
        pend = separar(',', ler,'\0');
        sscanf(pend2, " %s", aux2.indic);
        pend2 = separar(',', ler,'\0');
        sscanf(pend, " %d", &(aux2.week_count));
        pend = separar(',', ler,'\0');
        sscanf(pend2, " %s", aux2.year_week);
        pend2 = separar(',', ler,'\0');
        aux2.lastfteen = 0;         //como este número pode não ter dados, assume-se como 0
        sscanf(pend, " %lf", &(aux2.lastfteen));
        separar(',', ler,'\0');
        sscanf(pend2, " %d", &(aux2.n_dorc));
        head = criarP (head, aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
    }
    Pais* atual;
    Detalhes* atual2;
    for (atual = head ; atual != NULL; atual = atual->nextP){
    for (atual2 = atual->nextD; atual2 != NULL; atual2 = atual2->nextD)
    {
        //printf("%s / %s / %s / %d / %s / %d / %s / %.9f / %d\n\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual->indic, atual->week_count, atual->year_week, atual->lastfteen, atual->n_dorc);
        //depois apagar o printf
        printf("%s,%s,%s,%d,%s,%d,%s,%.9f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
        fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%.9f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
    }
    }
    //apagar(head);
    fclose(lp);
    fclose(ep);
    printf("O seu ficheiro foi concluido!\n");
    return 0;

}