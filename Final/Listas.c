#include "Projeto_covid.h"

Pais* encontra_pais(char* cod_pais,Pais* head)
{
    Pais* aux;
    if (head == NULL) // Se a lista não tiver nenhum node
    {
        return NULL;
    }
    for(aux = head; aux != NULL; aux = aux->nextP)  // Executa até percorrer a lista toda
    {
        if(strcmp(cod_pais,aux->cod_pais) == 0)     //comparacao com o codigo dos paises, se o pais já tiver um node_pais criado dá return do endereço desse node
        {
            return aux;
        }
    }
    return NULL;    //caso não encontre retorna NULL
}

void criarD(Detalhes* deta,char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Detalhes* aux = deta;
    Detalhes* deta2 = (Detalhes*) calloc(1,sizeof(Detalhes));
    if (deta2 == NULL)       //caso em que não consegue alocar deta2
    {
        help(3);
    }
    while(aux->nextD != NULL)   // Anda com o aux até ao final da lista de detalhes daquele pais para depois colocar o novo_detalhes
    {
        aux = aux->nextD;
    }
    aux->nextD = deta2;

    deta2->n_dorc = n_dorc;
    deta2->lastfteen = lastfteen;    // O node_detalhes recebe os dados do ficheiro lido
    deta2->week_count = week_count;
    strcpy(deta2->year_week, year_week);
    strcpy(deta2->indic, indic);
}

Pais* criarP (Pais* head, char* pais, char* cod_pais, char* cont,int popu, char* indic, int week_count, char* year_week, double lastfteen, int n_dorc)
{
    Pais* P_atual;
    P_atual = encontra_pais(cod_pais, head);
    if (P_atual != NULL)    // Caso em que o node daquele pais já existe e portanto só adiciona um node aos detalhes desse pais
    {
        criarD(P_atual->nextD, indic, week_count, year_week, lastfteen, n_dorc);
        return head;
    }
    //Caso seja nulo, ou seja, não exista qualquer registo daquele pais então cria mais um node de pais e um node de detalhes associado a este
    Pais* novo = (Pais*) calloc (1,sizeof(Pais));
    Detalhes* deta = (Detalhes*) calloc(1,sizeof(Detalhes)); //deta significa detalhes

    if (novo == NULL)       //caso em que não consegue alocar novo
    {
        help(3);
    }
    if (deta == NULL)       //caso em que não consegue alocar deta
    {
        help(3);
    }
    novo->popu = popu;
    strcpy(novo->cont, cont);
    strcpy(novo->pais, pais);
    strcpy(novo->cod_pais, cod_pais);
    if (head == NULL)       // se não houver nenhum elemento na lista, define os detalhes para os campos respetivos e retorna o endereco de "novo" para este servir de cabeça da lista
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
    while(aux->nextP != NULL)   // Avança até ao final da lista de paises
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

void apagar(Pais* head)
{

    Pais* aux;
    Detalhes* aux2;

    while(head != NULL)     // Executa até encontrar o final da lista
    {
        while(head->nextD != NULL)  // Até chegar ao final da lista remove todos os nodes
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


void escrita(FILE* ep, Pais* head,char* e_ext)
{
    Pais* atual;
    if(strcmp(e_ext,"csv") == 0)
    {
        fprintf(ep, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n"); //Primeira linha de todos os ficheiros .csv
    }
    Detalhes* atual2;
    for (atual = head ; atual != NULL; atual = atual->nextP)                    //Passar todos os elementos da lista Pais
    {
        for (atual2 = atual->nextD; atual2 != NULL; atual2 = atual2->nextD)     //Passar todos os elementos da lista Detalhes
        {

            if(strcmp(e_ext,"dat") == 0)
            {
                fwrite(atual->pais, sizeof(atual->pais), 1, ep);            //Escrita dos parametros em binário
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
                //Escrita dos parametros nas linhas do ficheiro caso seja .csv
            }
        }
    }
}


Pais* leit(Pais* head, FILE* lp, char* l_ext, FILE* ep, char* leitura, char* e_ext)
{
    int linha = 1,erro = 0;
    char ler[max_linha] = {""}, *pend = NULL, *pend2 = NULL;
    if(strcmp(l_ext,"csv") == 0)
    {
        fgets(ler, max_linha, lp); //para descartar a primeira linha com o titulo que há em .csv
    }
    Pais aux;
    Detalhes aux2;
    ///Leitura do ficheiro caso este seja .dat
    if ((strcmp(l_ext,"dat")) == 0)
    {
        if(strcmp(e_ext,"csv") == 0)
        {
            fprintf(ep, "country,country_code,continent,population,indicator,weekly_count,year_week,rate_14_day,cumulative_count\n");   //Primeira linha de todos os ficheiros .csv
        }
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
            if(feof(lp) != 0)       //Quando acabar de ler o ficheiro binário break
            {
                break;
            }
            if(strcmp(e_ext,"dat") == 0){       //caso queira escrever de binário para binário
            fwrite(aux.pais, sizeof(aux.pais), 1, ep);
            fwrite(aux.cod_pais, sizeof(aux.cod_pais), 1, ep);
            fwrite(aux.cont, sizeof(aux.cont), 1, ep);
            fwrite(&aux.popu, sizeof(aux.popu), 1, ep);
            fwrite(aux2.indic, sizeof(aux2.indic), 1, ep);
            fwrite(&aux2.week_count, sizeof(aux2.week_count), 1, ep);
            fwrite(aux2.year_week, sizeof(aux2.year_week), 1, ep);
            fwrite(&aux2.lastfteen, sizeof(aux2.lastfteen), 1, ep);
            fwrite(&aux2.n_dorc, sizeof(aux2.n_dorc), 1, ep);
            }
            else{
            //escrita de .dat para .csv
            fprintf(ep, "%s,%s,%s,%d,%s,%d,%s,%f,%d\n", aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
            }
        }
        printf("\nO seu ficheiro foi concluido!\n\n");
        fclose(lp);
        fclose(ep);
        exit(0);
    }
    else
    {
        while(fgets(ler, max_linha, lp)!= NULL)
        {
            linha++;                                    //Para saber a linha em que há erro (caso haja erro no ficheiro)
            pend = separar(',', ler,'\0');              //substituir as virgulas por terminadores de string
            if(sscanf(ler, " %[^,]", aux.pais) != 1)   //Como pode ter espaços usei [^,] para ele ler tudo até ao terminador da string(já que a virgulas foi substituida por uma terminador de string)
            {
                erro=1;                                //caso haja algum erro em qualquer argumento ele mete a variável erro a 1
            }
            pend2 = separar(',', pend,'\0');            //repetição para todos os argumentos
            if(sscanf(pend, " %s", aux.cod_pais) != 1)
            {
                erro=1;
            }
            pend = separar(',', pend2,'\0');
            if(sscanf(pend2, " %s", aux.cont) != 1)
            {
                erro=1;
            }

            pend2 = separar(',', pend,'\0');
            if(sscanf(pend, " %d", &(aux.popu)) != 1)
            {
                erro=1;
            }
            pend = separar(',', pend2,'\0');
            if(sscanf(pend2, " %s", aux2.indic)!= 1)
            {
                erro=1;
            }
            pend2 = separar(',', pend,'\0');
            if(sscanf(pend, " %d", &(aux2.week_count)) != 1)
            {
                erro=1;
            }
            pend = separar(',', pend2,'\0');
            if(sscanf(pend2, " %s", aux2.year_week) != 1)
            {
                erro=1;
            }
            pend2 = separar(',', pend,'\0');
            if(sscanf(pend, " %lf", &(aux2.lastfteen)) != 1)
            {
                aux2.lastfteen = 0;         //caso este número não tenha dados, assume-se como 0
            }
            if(sscanf(pend2, " %d", &(aux2.n_dorc)) != 1)
            {
                erro=1;
            }
            if(verificacao_week(aux2.year_week) || verificacao_palavra(aux.pais) || verificacao_palavra(aux.cod_pais) || (strcmp(aux2.indic,"cases") != 0 && strcmp(aux2.indic,"deaths") != 0) || verificacao_palavra(aux.cont) || aux.popu <= 0 || aux2.week_count < 0 || aux2.lastfteen < 0 || aux2.n_dorc < 0)
            {
                erro=1;
            }
            if(strcmp(leitura, "all") != 0 && strcmp(leitura, aux.cont) != 0)   //Entra dentro do if caso o continente passado em -L seja diferente do continente especificado. Caso seja "all" nunca entra
            {
                erro = 0;           //Ignora o erro já que a linha é descartada
                continue;           //Volta ao inicio do while
            }
            if(erro)                //Caso tenha um erro imprime a linha em que tem o erro, fecha todos os ficheiros, dá free da memória e vai para o help
            {
                printf("Linha --> %d\n", linha);
                apagar(head);
                fclose(lp);
                fclose(ep);
                help(10);
            }
            head = criarP (head, aux.pais, aux.cod_pais, aux.cont, aux.popu, aux2.indic, aux2.week_count, aux2.year_week, aux2.lastfteen, aux2.n_dorc);
            //Chamar a função criarP para adicionar mais um elemento há lista
        }
    }
    return head;
}
