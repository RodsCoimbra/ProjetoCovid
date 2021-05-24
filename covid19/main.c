#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct Detalhes   // lista que está dentro da lista "pais"
{
    char indic[7];
    int week_count;
    char year_week[8];
    double lastfteen;
    int n_dorc; // numero de deaths or cases
    struct Detalhes *nextD; // nextD é o pointer do detalhe seguinte
} Detalhes;

typedef struct Pais
{
    char pais[35];
    char cod_pais[4];
    char cont[8];
    int popu;
    Detalhes *nextD;
    struct Pais *nextP; // nextP é o pointer do pais seguinte
} Pais;

void help(int helpvar)
{
    switch (helpvar)
    {
    case 1:
        perror("Erro! Problema nos argumentos de entrada");
        break;
    case 2:
        perror("Nao foi possivel ler o ficheiro de entrada.");
        break;
    case 3:
        perror("Nao foi possivel alocar memória.");
        break;
    case 4:
        perror("O ficheiro de entrada não tem dados.");
        break;
    case 5:
        perror("Numero da populacao para a restricao invalido ou nao inserido.");
        break;
    case 6:
        perror("Nao consegui abrir o ficheiro de escrita (possivelmente esta aberto ou não escreveu)");
        break;
    }

    printf("\n\n### Menu Ajuda ###\n");
    printf("Metodo de introducao de argumentos\n");
    printf("./covid19 [argumento1] [argumento2] ... [argumentoN] -> Inicializa o programa com as carateristicas definidas nos argumentos\n");
    printf("Argumentos de Leitura:\n ");
    printf("\t-L all\t\t\t\tMostra todos os dados do ficheiro introduzido\n");
    printf("\t-L nome_do_continente\t\tMostra todos os dados referentes a um continente\n");
    printf("Argumentos de Ordenacao de Dados:\n ");
    printf("\t-S alfa\t\t\t\tOrdena os paises por ordem alfabetica\n");
    printf("\t-S  pop\t\t\t\tOrdena de forma decrescente a populacao dos paises\n");
    printf("\t-S inf yyyy-ww\t\t\tOrdena de forma decrescente o numero total de infetados por pais na data especificada\n");
    printf("\t-S dea yyyy-ww\t\t\tOrdena de forma decrescente o numero total de mortes por pais na data especificada\n");
    printf("Argumentos de Selecao de Dados:\n ");
    printf("\t-D inf\t\t\t\tSeleciona a semana com mais infetados de cada pais\n");
    printf("\t-D dea\t\t\t\tSeleciona a semana com mais mortes de cada pais\n");
    printf("\t-D racioinf\t\t\tSeleciona a semana com o maior racio de infetados por 100 mil habitantes\n");
    printf("\t-D raciodea\t\t\tSeleciona a semana com o maior racio de mortes por milhao de habitantes\n");
    printf("Argumentos de Rstricao de Dados:\n ");
    printf("\t-P min N\t\t\tMostra apenas os paises com papulacao superior a N\n");
    printf("\t-P max N\t\t\tMostra apenas os paises com papulacao inferior a N\n");
    printf("\t-P date yyy-ww\t\t\tMostra apenas os dados da semana introduzida\n");
    printf("\t-P dates yyyy-ww yyyy-ww\tMostra os dados referente ao intervalo de semanas introduzido\n");
    exit(-1);
}


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


Detalhes* selecionar (Pais* head_pais, int select)
{
    Detalhes* aux = NULL, *atual, *remover = NULL;
    int num_week = -1; //como o numero de infetados/mortos não pode ser negativo então ele guarda sempre o primeiro valor dos detalhes no aux
    double num_racio = -1;
    for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD)
    {
        if(((strcmp(atual->indic,"cases")== 0) && (atual->week_count > num_week) && (select== 1)) || ((strcmp(atual->indic,"deaths")== 0) && (atual->week_count > num_week) && (select == 2)) || ((strcmp(atual->indic,"cases") == 0) && (atual->lastfteen > num_racio) && (select== 3)) || ((strcmp(atual->indic,"deaths")== 0) && (atual->lastfteen > num_racio) && (select == 4)))
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


char* separar(char sep, char* str, char troca)
{
    int i;
    char* psep = NULL;
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

//1 - alfa; 2-pop; 3-inf; 4-dea;
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
/** \brief
 *
 * \param argc int
 * \param argv[] char*
 * \return int
 *
 */
int main(int argc, char *argv[])
{
    int opt, numero = 0, sel = 0;
    char restricao[6] = {""}, leitura[8] = "all", selecao[9] = {""}, ordenacao[5] = "alfa", l_fich[maxficheiro] = {""}, e_fich[maxficheiro] = {""}, l_ext[4]= {""}, e_ext[4] = {""};
    char ano1[8] = {""}, ano2[8] = {""}, ano_ord[8] = {""}, ler[max_linha] = {""}, *pend = NULL, *pend2 = NULL;
    opterr = 0;
    while((opt= getopt(argc, argv,"P:L:D:S:i:o:"))!= -1 ) // loop que recebe as informacoes do utilizador no incio do programa
    {
        switch (opt)
        {
        case 'P':
            sscanf(optarg," %s", restricao);
            if (strcmp("min", restricao) == 0 || strcmp("max", restricao) == 0)
            {
                sscanf(optarg + strlen(restricao) + 1," %d", &numero);
            }
            else if (strcmp("date", restricao) == 0)
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
            }
            else if (strcmp("dates", restricao) == 0)
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
                sscanf(optarg + strlen(restricao) +strlen(ano1) + 2," %s", ano2);
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
            sel = 1;
            break;
        case 'S':
            sscanf(optarg," %s", ordenacao);
            if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0)
            {
                sscanf(optarg + strlen(ordenacao) + 1," %s", ano_ord);
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
        if ((ep = fopen(e_fich, "w")) == NULL)
        {
            help(6);
        }
    }
    else if((strcmp(e_ext,"dat")) == 0)
    {
        if ((ep = fopen(e_fich, "wb"))==NULL)
        {
            help(6);
        }
    }
    else
    {
        help(6);
    }
    Pais* head = NULL;
    //Leitura do ficheiro
    if(strcmp(l_ext,"csv") == 0)
    {
        if (fgets(ler, max_linha, lp) == NULL)
        {
            help(4);
        }
    }
    if(strcmp(e_ext,"csv") == 0)
    {
        fprintf(ep, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n"); //titulo
    }
    // Ler linhas
    Pais aux;
    Detalhes aux2;
    if ((strcmp(l_ext,"dat")) == 0)
    {
        while(1)
        {
            fread(aux.pais, sizeof(aux.pais), 1, lp);
            fread(aux.cod_pais, sizeof(aux.cod_pais), 1, lp);
            fread(aux.cont, sizeof(aux.cont), 1, lp);
            fread(&aux.popu, sizeof(aux.popu), 1, lp);
            fread(aux2.indic, sizeof(aux2.indic), 1, lp);
            fread(&aux2.week_count, sizeof(aux2.week_count), 1, lp);
            fread(aux2.year_week, sizeof(aux2.year_week), 1, lp);
            fread(&aux2.lastfteen, sizeof(aux2.lastfteen), 1, lp);
            fread(&aux2.n_dorc, sizeof(aux2.n_dorc), 1, lp);
            if(feof(lp) != 0)
            {
                break;
            }
            fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%f,%d\n", aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
        }
    }
    else
    {
        while(fgets(ler, max_linha, lp)!= NULL)
        {
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
            sscanf(pend2, " %d", &(aux2.n_dorc));
            if(strcmp(leitura, "all") != 0 && strcmp(leitura, aux.cont) != 0)
            {
                continue;
            }
            head = criarP (head, aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
        }
    }


    Pais* atual;

    ///Selecao
    if(sel)
    {
        if(strcmp(selecao, "inf") == 0)
        {
            for (atual = head ; atual != NULL; atual = atual->nextP)
            {
                atual->nextD = selecionar(atual, 1);
                atual->nextD->nextD = NULL;
            }
        }
        else if(strcmp(selecao, "dea") == 0)
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
        else
        {
            help(1);
        }
    }


    ///restricao
    if(strcmp(restricao, "min") == 0)
    {
        if(numero <= 0)
        {
            help(5);
        }
        head = restringir_pop(head, numero,1);
    }

    else if(strcmp(restricao, "max") == 0)
    {
        if(numero <= 0)
        {
            help(5);
        }
        head = restringir_pop(head, numero,2);
    }

    else if(strcmp(restricao, "date") == 0)
    {
        for (atual = head ; atual != NULL; atual = atual->nextP)
        {
            atual->nextD = restringir_week(atual, ano1, ano2, 3);
        }
    }
    else if(strcmp(restricao, "dates") == 0)
    {
        for (atual = head ; atual != NULL; atual = atual->nextP)
        {
            atual->nextD = restringir_week(atual, ano1, ano2, 4);
        }
    }



    ///ordenacao
    if(head != NULL && head->nextP != NULL)
    {
        if(strcmp(ordenacao,"alfa") == 0)
        {
            head = ordenar(head, 1," ");
        }
        else if(strcmp(ordenacao,"pop") == 0)
        {
            head = ordenar(head, 2," ");
        }
        else if(strcmp(ordenacao,"inf") == 0)
        {
            head = ordenar(head, 3, ano_ord);
        }
        else if(strcmp(ordenacao,"dea") == 0)
        {
            head = ordenar(head, 4, ano_ord);
        }
        else
        {
            apagar(head);
            help(1);
        }
    }

    Detalhes* atual2;
    for (atual = head ; atual != NULL; atual = atual->nextP)
    {
        for (atual2 = atual->nextD; atual2 != NULL; atual2 = atual2->nextD)
        {

            if(strcmp(e_ext,"dat") == 0)
            {
                fwrite(atual->pais, sizeof(atual->pais), 1, ep);
                fwrite(atual->cod_pais, sizeof(atual->cod_pais), 1, ep);
                fwrite(atual->cont, sizeof(atual->cont), 1, ep);
                fwrite(&atual->popu, sizeof(atual->popu), 1, ep);
                fwrite(atual2->indic, sizeof(atual2->indic), 1, ep);
                fwrite(&atual2->week_count, sizeof(atual2->week_count), 1, ep);
                fwrite(atual2->year_week, sizeof(atual2->year_week), 1, ep);
                fwrite(&atual2->lastfteen, sizeof(atual2->lastfteen), 1, ep);
                fwrite(&atual2->n_dorc, sizeof(atual2->n_dorc), 1, ep);
            }

            else
            {
                //printf("%s,%s,%s,%d,%s,%d,%s,%.9f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
                //depois apagar o printf

                fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
            }
        }
    }

    apagar(head);
    fclose(lp);
    fclose(ep);
    printf("\nO seu ficheiro foi concluido! O conteudo foi escrito no ficheiro %s \n\n",e_fich);
    return 0;

}
