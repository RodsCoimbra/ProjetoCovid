#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows

int main(int argc, char *argv[])       //   Rececao da informacao dada pelo jogador no inicio do programa me termos de dimensao do tabuleiro, modo de disparo, posicionamento e numero de pecas por tipo
{
    int opt, numero = 0, semana1, semana2, ano1, ano2, anod, semanad,a;
    char ordem[6] = {""}, leitura[25], selecao[9], ordenacao[5], lfich[maxficheiro], efich[maxficheiro];
    opterr = 0;
    while((opt= getopt(argc, argv,"P:L:D:S:i:o:"))!= -1 ) // loop que recebe as informações do utilizador no incio do programa
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
                printf("Erro! Parametro invalido");
                return(-1);
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
            sscanf(optarg," %s", lfich);
            break;

        case 'o':
            sscanf(optarg," %s", efich);
            break;

        default:    // Mostra a mensagem se for escrito um caracter sem sentido no programa
        {
            printf("*Carater %c nao identificado", optopt);
        }
}}

           /* printf("ficheiro a ler - %s\n", lfich);
            printf("ficheiro a escrever - %s\n", efich);
            printf("L - %s \n", leitura);
            printf("P - %s\n", ordem);
            printf("%d-%d\n", ano1, semana1);
            printf("%d-%d\n", ano2, semana2);           so para teste, depois apagar */

            return 0;
}
