#include "Projeto_covid.h"

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
                help(6);
            }
            break;
        case 'L':
            sscanf(optarg," %s", leitura);
            if(strcmp(leitura, "all") == 0 || strcmp(leitura, "Africa") == 0 || strcmp(leitura, "America") == 0 || strcmp(leitura, "Asia") == 0 || strcmp(leitura, "Europe") == 0 || strcmp(leitura, "Oceania") == 0){
            break;}
            else{
                help(7);
            }
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
            if(pend == pend2){              //Caso o utilizador não meta extensão do ficheiro
                help(2);
            }
            sscanf(pend,"%s", l_ext);
            break;

        case 'o':
            sscanf(optarg," %s", e_fich);
            pend2 = separar('.', e_fich,'.');
            if(pend == pend2){              //Caso o utilizador não meta extensão do ficheiro
                help(5);
            }
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
            help(5);
        }
    }
    else if((strcmp(e_ext,"dat")) == 0)
    {
        if ((ep = fopen(e_fich, "wb"))==NULL)
        {
            help(5);
        }
    }
    else
    {
        help(5);
    }
    Pais* head = NULL;

    ///Leitura do ficheiro
    if(strcmp(l_ext,"csv") == 0)
    {
        fgets(ler, max_linha, lp); //para descartar a primeira linha com os titulos
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
            apagar(head);
            help(8);
        }
    }


    ///restricao
    if(strcmp(restricao, "min") == 0)
    {
        head = restringir_pop(head, numero,1);
    }

    else if(strcmp(restricao, "max") == 0)
    {
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
            help(9);
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
