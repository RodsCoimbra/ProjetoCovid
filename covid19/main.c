#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows

typedef struct linha {
    int n_inf;
    int n_mort;
    int popu;
    int week_count;
    int n_week;
    int lastfteen;
    char pais[35];
    char cod_pais[4];
    char indic[7];
    struct linha * next;
} linha;

/** \brief
 *
 * \param sep char
 * \param str char*
 * \return char*
 *
 */
char* separar(char sep, char* str){
int i;
char *psep;
for(i=0; str[i] != '\0' ; i++){
if(str[i] == sep){
    //str[i] = '\0';                    resolver mais tarde
    psep = &str[i+1] ;
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
help(int helpvar){
    switch (helpvar) {
        case 1: printf("Erro! Problema nos argumentos de entrada");
                exit(-1);
                break;
        case 2: printf("Nao foi possivel ler o ficheiro de entrada.");
                exit(-1);
                break;
        case 3: printf("");
                exit(-1);
                break;
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
    int opt, numero = 0, semana1, semana2, ano1, ano2, anod, semanad;
    char ordem[6] = {""}, leitura[35], selecao[9], ordenacao[5], l_fich[maxficheiro], e_fich[maxficheiro], l_ext[4], e_ext[4];
    opterr = 0;
    char *pend;
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
            pend = separar('.', l_fich);
            sscanf(pend,"%s", l_ext);
            break;

        case 'o':
            sscanf(optarg," %s", e_fich);
            pend = separar('.', e_fich);
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

char string[100];
fscanf(lp, " %s", string);
printf("%s", string);

fclose(lp);
//printf("ficheiro a ler - %s\n", lfich);

            /*printf("ficheiro a ler - %s.%s\n", lfich, exte);
            printf("ficheiro a escrever - %s.%s\n", efich, exts);
            printf("L - %s \n", leitura);
            printf("P - %s  %d\n", ordem, numero);
            printf("%d-%d\n", ano1, semana1);
            printf("%d-%d\n", ano2, semana2);           //so para teste, depois apagar*/
            return 0;
}

