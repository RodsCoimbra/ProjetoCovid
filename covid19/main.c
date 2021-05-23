#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct Detalhes { // lista que está dentro da lista "pais"
    char indic[7];
    int week_count;
    char year_week[8];
    double lastfteen;
    int n_dorc; // numero de deaths or cases
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
    case 4:
        printf("O ficheiro de entrada não tem dados.");
        break;
    }
printf("\n### Menu Ajuda ###\n");
printf("\n### Menu Ajuda ###\n");
printf("Metodo de introducao de argumentos\n");
printf("./covid19 [argumento1] [argumento2] ... [argumentoN] -> Inicializa o programa com as carateristicas definidas nos argumentos\n");
printf("Argumentos de Leitura:\n ");
printf("    -L all          Mostra todos os dados do ficheiro introduzido\n    -L nome_do_continente        Mostra todos os dados referentes a um continente ");
printf("Argumentos de Ordenacao de Dados:\n ");
printf("    -S alfa         Ordena os paises por ordem alfabetica\n     -S  pop         Ordena de forma decrescente a populacao dos paises\n    -S inf yyyy-ww          Ordena de forma decrescente o numero total de infetados por pais na data especificada\n     -S dea yyyy-ww          Ordena de forma decrescente o numero total de mortes por pais na data especificada\n");
printf("Argumentos de Selecao de Dados:\n ");
printf("    -D inf          Seleciona a semana com mais infetados de cada pais\n    -D dea          Seleciona a semana com mais mortes de cada pais\n   -D racioinf         Seleciona a semana com o maior racio de infetados por 100000 habitantes\n   -D raciodea         Seleciona a semana com o maior racio de mortes por 100000 habitantes");
printf("Argumentos de Rstricao de Dados:\n ");
printf("    -P min n        \n ");
    exit(-1);
}


Pais* verificacao(char* cod_pais,Pais* head){
    Pais* aux;
    if (head == NULL)
    {
        return NULL;
    }
    for(aux = head;aux != NULL;aux = aux->nextP){
        if(strcmp(cod_pais,aux->cod_pais) == 0){   //comparacao com o codigo dos paises
        return aux;
        }
    }
    return NULL;
    }

void criarD(Detalhes* deta,char* indic, int week_count, char* year_week, double lastfteen, int n_dorc){
    Detalhes* aux = deta;
    Detalhes* deta2 = (Detalhes*) calloc(1,sizeof(Detalhes));
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
    if (head == NULL){
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
    while(aux->nextP != NULL){
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
        while(head->nextD != NULL){
            aux2 = head->nextD;
            head->nextD = head->nextD->nextD;
            free(aux2);
        }
        aux = head;
        head = head->nextP;
        free(aux);
    }
}

int valores(Pais* head_pais, int ordena, char*semana){
Detalhes* atual;
if(ordena == 3){
for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD){
    if((strcmp(atual->indic,"cases")==0) && (strcmp(atual->year_week, semana) ==0)){
        return atual->week_count;}}
}

else if(ordena == 4){
for (atual = head_pais->nextD; atual != NULL; atual = atual->nextD){
    if((strcmp(atual->indic,"deaths")==0) && (strcmp(atual->year_week, semana) ==0)){
        return atual->week_count;}}
}
return 0;
}

//1 - alfa; 2-pop; 3-inf; 4-dea;
Pais* ordenar(Pais* head, int ordena, char* semana){

    int flag = 0, x = 0, y = 0;
    Pais* esq, *drt, *paux, aux, *d, *e;
    paux = &aux;            //Cria auxiliar antes, pois vai mexer nos dois blocos da frente
    paux->nextP = head;
    while(flag == 0){
            esq = paux;
            drt = paux -> nextP;
            flag = 1;

            while(drt-> nextP != NULL)
            {
                if(ordena == 3 || ordena == 4){
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
                if (drt->nextP != NULL){
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
    int opt, numero = 0;
    char restricao[6], leitura[8] = "all", selecao[9], ordenacao[5] = "alfa", l_fich[maxficheiro], e_fich[maxficheiro], l_ext[4], e_ext[4], ler[max_linha], *pend, *pend2;
    char ano1[8], ano2[8], ano_ord[8];
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
            break;
        case 'S':
            sscanf(optarg," %s", ordenacao);
            if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0)
            {
                sscanf(optarg + strlen(ordenacao) + 1," %s", ano_ord);
            }
            else {
                help(1);
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
    if(strcmp(l_ext,"csv") == 0){
    if (fgets(ler, max_linha, lp)==NULL)
    {
        help(4);
    }}
    if(strcmp(e_ext,"csv") == 0)
    {
        fprintf(ep, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n"); //titulo
    }
    // Ler linhas
    Pais aux;
    Detalhes aux2;

if ((strcmp(l_ext,"dat")) == 0){
        while(1){
        fread(aux.pais, sizeof(aux.pais), 1, lp);
        fread(aux.cod_pais, sizeof(aux.cod_pais), 1, lp);
        fread(aux.cont, sizeof(aux.cont), 1, lp);
        fread(&aux.popu, sizeof(aux.popu), 1, lp);
        fread(aux2.indic, sizeof(aux2.indic), 1, lp);
        fread(&aux2.week_count, sizeof(aux2.week_count), 1, lp);
        fread(aux2.year_week, sizeof(aux2.year_week), 1, lp);
        fread(&aux2.lastfteen, sizeof(aux2.lastfteen), 1, lp);
        fread(&aux2.n_dorc, sizeof(aux2.n_dorc), 1, lp);
        if(feof(lp) != 0){
                break;}
        fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%f,%d\n", aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
}}

else{
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
        separar(',', ler,',');
        sscanf(pend2, " %d", &(aux2.n_dorc));
        if(strcmp(leitura, "all") != 0 && strcmp(leitura, aux.cont) != 0){
            continue;
        }
        head = criarP (head, aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
    }}
    if(head != NULL && head->nextP != NULL){
        if(strcmp(ordenacao,"alfa") == 0){
        head = ordenar(head, 1," ");
        }
        else if(strcmp(ordenacao,"pop") == 0){
        head = ordenar(head, 2," ");
        }
        else if(strcmp(ordenacao,"inf") == 0){
        head = ordenar(head, 3, ano_ord);
        }
        else if(strcmp(ordenacao,"dea") == 0){
        head = ordenar(head, 4, ano_ord);
        }
        else{
        apagar(head);
        help(1);
        }}
    Pais* atual;
    Detalhes* atual2;

    for (atual = head ; atual != NULL; atual = atual->nextP){
    for (atual2 = atual->nextD; atual2 != NULL; atual2 = atual2->nextD){

        if(strcmp(e_ext,"dat") == 0){
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

       else{
        //printf("%s,%s,%s,%d,%s,%d,%s,%.9f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
        //depois apagar o printf

        fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%f,%d\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual2->indic, atual2->week_count, atual2->year_week, atual2->lastfteen, atual2->n_dorc);
    }
    }}

    apagar(head);
    fclose(lp);
    fclose(ep);
    printf("\nO seu ficheiro foi concluido! O conteudo foi escrito no ficheiro %s \n\n",e_fich);
    return 0;

}
      /// -i covid19_w_t01.csv -o escrita.csv -L all
      /// -i covid19_w_t01.csv -o escrita.dat -L all
     ///  -i escrita.dat -o escrita.csv -L all -P min 5000*/ /// Ainda nao funciona
