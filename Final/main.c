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
            restri = 1;                              // Flag para saber que foi usada uma restrição
            sscanf(optarg," %s", restricao);        // Lê a opção de Restrição do utilizador
            if (strcmp("min", restricao) == 0 || strcmp("max", restricao) == 0)     // Executa caso a opção escolhida for "min" ou "max"
            {
                if(sscanf(optarg + strlen(restricao) + 1," %lld", &numero) != 1)        //Leitura do argumento a seguir à palavra min e max
                    //Soma-se a optarg(onde começa a primeira palavra deste argumento) a strlen de max ou min (neste caso 3) + 1 para também passar o terminador de string e assim obtem-se o endereço onde começa a segunda palavra
                {
                    help(6);
                }
            }
            else if (strcmp("date", restricao) == 0)        // Executa caso a opção escolhida for "date"
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
                if(verificacao_week(ano1))      // Verifica se o ano e semana estam escrita de forma correta
                {
                    help(6);
                }
            }
            else if (strcmp("dates", restricao) == 0)       // Executa caso a opção escolhida for "dates"
            {
                sscanf(optarg + strlen(restricao) + 1," %s", ano1);
                sscanf(optarg + strlen(restricao) +strlen(ano1) + 2," %s", ano2);    //Como desta vez são duas palavras antes do argumento pretendido soma-se as strlens de cada uma das strings + 2 ao optarg
                if(verificacao_week(ano1) || verificacao_week(ano2))        // Verifica se as datas estam escritas de forma correta se alguma delas não estiver apresenta o menu de ajuda
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
            sscanf(optarg," %s", leitura);      // Lê a opção de Leitura do utilizador
            if(strcmp(leitura, "all") == 0 || strcmp(leitura, "Africa") == 0 || strcmp(leitura, "America") == 0 || strcmp(leitura, "Asia") == 0 || strcmp(leitura, "Europe") == 0 || strcmp(leitura, "Oceania") == 0)
            {
                break;
            }
            else
            {
                help(7);
            }
        case 'D':
            sscanf(optarg," %s", selecao);      // Lê a opção de Seleção do utilizador
            if(strcmp(selecao, "inf") == 0 || strcmp(selecao, "dea") == 0 || strcmp(selecao, "racioinf") == 0 || strcmp(selecao, "raciodea") == 0)
            {
                sel = 1;        //Flag para saber que foi usada uma seleção
                break;
            }
            else
            {
                help(8);
            }

        case 'S':
            sscanf(optarg," %s", ordenacao);        // Lê a opção de Ordenação do utilizador
            if(strcmp(ordenacao,"alfa") == 0 || strcmp(ordenacao,"pop") == 0)       // Executa se a opção escolhida for "alfa" nem "pop"
            {
                break;
            }
            else if (strcmp("inf", ordenacao) == 0 || strcmp("dea", ordenacao) == 0)        // Executa se a opção de ordenação escolhida foi "inf" ou "dea"
            {
                sscanf(optarg + strlen(ordenacao) + 1," %s", ano_ord);
                if(verificacao_week(ano_ord))       // Verifica se a semana está escrita de forma correta
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
            if(pend == NULL)                 //Caso o utilizador não meta extensão do ficheiro
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
    if(strcmp(l_ext,"csv") == 0)        // Se for um ficheiro com extensão .csv
    {
        if ((lp = fopen(l_fich, "r"))== NULL)       // Se der erro ao abrir o ficheiro de leitura, ele mostra o menu de ajuda
        {
            help(2);
        }
    }
    else if((strcmp(l_ext,"dat")) == 0)     // Se for um ficheiro com extensão .dat
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
        if ((ep = fopen(e_fich, "w")) == NULL)      // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha e mostra o menu de ajuda
        {
            fclose(lp);
            help(5);
        }
    }
    else if((strcmp(e_ext,"dat")) == 0)
    {
        if ((ep = fopen(e_fich, "wb"))==NULL)       // Se der erro ao abrir o ficheiro de saida, então o ficheiro de leitura fecha e mostra o menu de ajuda
        {
            fclose(lp);
            help(5);
        }
    }
    else
    {
        fclose(lp);     // Fecha o ficheiro de leitura
        help(5);
    }
    Pais* head = NULL;

    ///Leitura do ficheiro
    head = leit (head, lp, l_ext, ep, leitura, e_ext);      // Chama a função de leitura

    ///Selecao
    if(sel)     //Entra caso o utilizador tenha escolhido um tipo de seleção(-D)
    {
        Escolher_sel(head, selecao);        // Chama a função irá executar o tratamento de dados de acordo com a seleção pedida no incio do programa pelo utilizador
    }

    ///restricao
    if(restri)    //Entra caso o utilizador tenha escolhido um tipo de restrição(-P)
    {
        head = Escolher_restri(head, restricao, numero, ano1, ano2);        // Chama a função irá executar o tratamento de dados de acordo com a restrição pedida no incio do programa pelo utilizador
    }

    ///ordenacao
    if(head != NULL && head->nextP != NULL)     //Caso não tenha nada na lista ou só tenha um elemento não é necessário ordenar nada
    {
        head = Escolher_orde(head, ordenacao, ano_ord);     //Chama a função irá executar a ordenação dos dados de acordo com o pedido do utilizador ou alfabeticamente em caso de omissão desse parametro
    }

    ///Escrita de dados
    escrita(ep, head, e_ext);       // Escreve no ficheiro escolhido na inicialização do programa

    apagar(head);       // Chamada da função apagar para dar free de todos os dados da lista
    fclose(lp);         // Fecha o ficheiro de leitura
    fclose(ep);         // Fecha o ficheiro de escrita
    printf("\nO seu ficheiro foi concluido! O conteudo foi escrito no ficheiro %s \n\n",e_fich);
    return 0;

}
