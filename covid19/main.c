#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120

typedef struct linha {
    int n_dorc; // numero de deaths or cases
    int popu;
    int week_count;
    int year_week;
    float lastfteen;
    char cont[8];
    char pais[35];
    char cod_pais[4];
    char indic[7];
    //struct linha * next;
} linha;

/** \brief
 *
 * \param sep char
 * \param str char*
 * \return char*
 *
 */
char* separar(char sep, char* str, char troca){
int i;
char *psep = NULL;
for(i=0; str[i] != EOF ; i++){
if(str[i] == sep){
    str[i] = troca;
    psep = &str[i+1];
    break;
}
}
 return psep;
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void help(int helpvar){
    switch (helpvar) {
        case 1: printf("Erro! Problema nos argumentos de entrada");
                exit(-1);
                break;
        case 2: printf("Nao foi possivel ler o ficheiro de entrada.");
                exit(-1);
                break;
        case 3: printf("Nao foi possivel alocar memória.");
                exit(-1);
                break;
    }
}


/** \brief
 *
 * \param ler char*
 * \param a char*
 * \return char*
 *
 */
/*char* leit(char* ler, char* a){
char* pend;
pend = separar(',', ler,'\0');
    sscanf(ler, "%s", a);
    return pend;
}
*/


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
    char ordem[6] = {""}, leitura[35], selecao[9], ordenacao[5], l_fich[maxficheiro], e_fich[maxficheiro], l_ext[4], e_ext[4], ler[max_linha];
    opterr = 0;
    char *pend, *pend2;
    while((opt= getopt(argc, argv,"P:L:D:S:i:o:"))!= -1 ) // loop que recebe as informa��es do utilizador no incio do programa
    {
        switch (opt)
        {
        case 'P':
            sscanf(optarg," %s", ordem);
            if (strcmp("min", ordem) == 0 || strcmp("max", ordem) == 0){
            sscanf(optarg + 4," %d", &numero);}
            else if (strcmp("date", ordem) == 0){
            sscanf(optarg + 5," %d-%d", &ano1, &semana1);
            }
            else if (strcmp("dates", ordem) == 0){
            sscanf(optarg + 6," %d-%d", &ano1, &semana1);
            sscanf(optarg + 14," %d-%d", &ano2, &semana2);
            }
            else{
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
            if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0){
            sscanf(optarg + 4," %d-%d", &anod, &semanad);}
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
 if(strcmp(l_ext,"csv") == 0) {
    if ((lp = fopen(l_fich, "r"))==NULL){
        printf("Entrei aqui!!!");
        help(2);
    }}
else if(strcmp(l_ext,"dat") == 0){
    if ((lp = fopen(l_fich, "rb"))==NULL){
        help(2); }}

else{
        help(2);
}

if (fgets(ler, max_linha, lp)==NULL){
    help(4);
}

printf("%s \n", ler+3); //titulo
char a[35],b[35],c[35],e[35],g[35];
int d,f,i;
double h;
// Ler linhas
while(fgets(ler, max_linha, lp)!=NULL){
    //novo_node();
    pend = separar(',', ler,'\0');
    sscanf(ler, " %[^,]", a);  //Como pode ter espaços usei [^,] para ele ler tudo até ao terminador da string(já que as virgulas foram substituidas então não à problema)
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %s", b);
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", c);
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %d", &d);
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", e);
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %d", &f);
    pend = separar(',', ler,'\0');
    sscanf(pend2, " %s", g);
    pend2 = separar(',', ler,'\0');
    sscanf(pend, " %lf", &h);
    separar(',', ler,'\0');
    sscanf(pend2, " %d", &i);

    printf("%s / %s / %s / %d / %s / %d / %s / %f / %d\n\n",  a, b, c, d, e, f, g, h, i);}



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
///Criar node
/*linha * novo_node() {
    linha * new_param;
    if (new_param = (linha*) malloc(sizeof(linha)) == NULL){
            help(3);
    }

    new_param->next = NULL;

} */

