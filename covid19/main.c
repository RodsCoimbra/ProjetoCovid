#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct linha
{
    int n_dorc; // number deaths or cases
    int popu;
    int week_count;
    char year_week[8];
    double lastfteen;
    char cont[8];
    char pais[35];
    char cod_pais[4];
    char indic[7];
    struct linha * next;
} linha;



/** \brief
*
* \param
* \param
* \return
*
*/
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

void criar(linha** ende, char* ler)  // ende=endereço
{
    char *pend, *pend2;
    linha* novo = (linha*) malloc (sizeof(linha));
    if (novo == NULL)
    {
        help(3);
    }

    pend = separar(',', ler,'\0');
    sscanf(ler, " %[^,]", novo->pais);  //Como pode ter espaços usei [^,] para ele ler tudo até ao terminador da string(já que as virgulas foram substituidas então não à problema)
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %s", novo->cod_pais);
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", novo->cont);
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %d", &(novo->popu));
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", novo->indic);
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %d", &(novo->week_count));
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", novo->year_week);
    pend2 = separar(',', ler,'\0');
    novo->lastfteen = 0;
    sscanf(pend, " %lf", &(novo->lastfteen));
    separar(',', ler,'\0');
    sscanf(pend2, " %d", &(novo->n_dorc));
    if (*ende == NULL)
    {
        *ende = novo;
        return;
    }
    linha* atual = *ende;
    while(atual->next != NULL)
    {
        atual = atual->next;
    }
    atual->next = novo;
}



void apagar(linha* ende){

linha* aux;

while(ende != NULL)
{
   aux = ende;
   ende = ende->next;
   free(aux);
}
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
    ///linha linha1;///isto e para apagar
    int opt, numero = 0, semana1, semana2, ano1, ano2, anod, semanad;
    char ordem[6] = {""}, leitura[35], selecao[9], ordenacao[5], l_fich[maxficheiro], e_fich[maxficheiro], l_ext[4], e_ext[4], ler[max_linha], *pend;
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
    if(strcmp(l_ext,"csv") == 0)
    {
        if ((lp = fopen(l_fich, "r"))==NULL)
        {
            printf("Entrei aqui!!!");
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

    if (fgets(ler, max_linha, lp)==NULL)
    {
        help(2);
    }
    printf("%s \n", ler+3); //titulo
    linha* head = NULL;

    // Ler linhas
    while(fgets(ler, max_linha, lp)!=NULL)
    {
        criar (&head, ler);
    }
    linha* atual;
    for (atual = head ; atual != NULL; atual = atual->next)
    {
        printf("%s / %s / %s / %d / %s / %d / %s / %.9f / %d\n\n", atual->pais, atual->cod_pais, atual->cont, atual->popu, atual->indic, atual->week_count, atual->year_week, atual->lastfteen, atual->n_dorc);
    }
    apagar(head);
    fclose(lp);

    /*printf("ficheiro a ler - %s \n", l_fich);
    printf("ficheiro a ler - %s.%s\n", l_fich, l_ext);
    printf("ficheiro a escrever - %s.%s\n", efich, e_ext);
    printf("L - %s \n", leitura);
    printf("P - %s  %d\n", ordem, numero);
    printf("%d-%d\n", ano1, semana1);
    printf("%d-%d\n", ano2, semana2);           //so para teste, depois apagar*/
    return 0;

}