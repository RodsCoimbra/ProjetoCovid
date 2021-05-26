#include "Projeto_covid.h"

int main(int argc, char *argv[])
{
    int opt, sel = 0, restri = 0;
    long long int numero = 0;
    char restricao[6] = {""}, leitura[8] = "all", selecao[9] = {""}, ordenacao[5] = "alfa", l_fich[maxficheiro] = {""}, e_fich[maxficheiro] = {""}, l_ext[4]= {""}, e_ext[4] = {""};
    char ano1[8] = {""}, ano2[8] = {""}, ano_ord[8] = {""}, *pend = NULL;
    opterr = 0;
    while((opt= getopt(argc, argv,"P:L:D:S:i:o:"))!= -1 ) // loop que recebe as informacoes do utilizador no incio do programa
    {
        switch (opt)
        {
        case 'P':
            restri = 1;
            sscanf(optarg," %s", restricao);
            if (strcmp("min", restricao) == 0 || strcmp("max", restricao) == 0)
            {
                if(sscanf(optarg + strlen(restricao) + 1," %lld", &numero) != 1)
                {
                    help(6);
                }
            }
            else if (strcmp("date", restricao) == 0)
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
                if(verificacao_week(ano1))
                {
                    help(6);
                }
            }
            else if (strcmp("dates", restricao) == 0)
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
                sscanf(optarg + strlen(restricao) +strlen(ano1) + 2," %s", ano2);
                if(verificacao_week(ano1) || verificacao_week(ano2))
                {
                    help(6);
                }
            }
            else
            {
                help(6);
            }
            break;
        case 'L':
            sscanf(optarg," %s", leitura);
            if(strcmp(leitura, "all") == 0 || strcmp(leitura, "Africa") == 0 || strcmp(leitura, "America") == 0 || strcmp(leitura, "Asia") == 0 || strcmp(leitura, "Europe") == 0 || strcmp(leitura, "Oceania") == 0)
            {
                break;
            }
            else
            {
                help(7);
            }
        case 'D':
            sscanf(optarg," %s", selecao);
            if(strcmp(selecao, "inf") == 0 || strcmp(selecao, "dea") == 0 || strcmp(selecao, "racioinf") == 0 || strcmp(selecao, "raciodea") == 0)
            {
                sel = 1;
                break;
            }
            else
            {
                help(8);
            }

        case 'S':
            sscanf(optarg," %s", ordenacao);
            if(strcmp(ordenacao,"alfa") == 0 || strcmp(ordenacao,"pop") == 0)
            {
                break;
            }
            else if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0)
            {
                sscanf(optarg + strlen(ordenacao) + 1," %s", ano_ord);
                if(verificacao_week(ano_ord))
                {
                    help(9);
                }
                break;
            }
            else
            {
                help(9);
            }

        case 'i':
            sscanf(optarg," %s", l_fich);
            pend = separar('.', l_fich,'.');
            if(pend == NULL)               //Caso o utilizador não meta extensão do ficheiro
            {
                help(2);
            }
            sscanf(pend,"%s", l_ext);       //l_ext = extensao do ficheiro de leitura
            break;

        case 'o':
            sscanf(optarg," %s", e_fich);
            pend = separar('.', e_fich,'.');
            if(pend == NULL)               //Caso o utilizador não meta extensão do ficheiro
            {
                help(5);
            }
            sscanf(pend,"%s", e_ext);      //e_ext = extensao do ficheiro de escrita
            break;

        default:    // Mostra a mensagem se for escrito um caracter sem sentido no programa
        {
            help(1);
        }
        }
    }

    if(strcmp(l_fich,e_fich) == 0)
    {
        help(11);
    }

    FILE *lp = NULL;    //lp = File pointer de leitura
    FILE *ep = NULL;    //ep = File pointer de escrita
    //Tipo de leitura
    if(strcmp(l_ext,"csv") == 0)
    {
        if ((lp = fopen(l_fich, "r"))== NULL)
        {
            help(2);
        }
    }
    else if((strcmp(l_ext,"dat")) == 0)
    {
        if ((lp = fopen(l_fich, "rb")) == NULL)
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
            fclose(lp);
            help(5);
        }
    }
    else if((strcmp(e_ext,"dat")) == 0)
    {
        if ((ep = fopen(e_fich, "wb"))==NULL)
        {
            fclose(lp);
            help(5);
        }
    }
    else
    {
        fclose(lp);
        help(5);
    }
    Pais* head = NULL;

    ///Leitura do ficheiro
    head = leit (head, lp, l_ext, ep, leitura, e_ext);

    ///Selecao
    if(sel)
    {
        Escolher_sel(head, selecao);
    }

    ///restricao
    if(restri)
    {
        head = Escolher_restri(head, restricao, numero, ano1, ano2);
    }

    ///ordenacao
    if(head != NULL && head->nextP != NULL)
    {
        head = Escolher_orde(head, ordenacao, ano_ord);
    }

    ///Escrita de dados
    escrita(ep, head, e_ext);

    apagar(head);
    fclose(lp);
    fclose(ep);
    printf("\nO seu ficheiro foi concluido! O conteudo foi escrito no ficheiro %s \n\n",e_fich);
    return 0;

}
