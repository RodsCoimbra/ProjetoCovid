#include "Projeto_covid.h"

void help(int helpvar)
{
    switch (helpvar)
    {
    case 1:
        perror("Argumentos de entrada desconhecido.");
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
        perror("Ficheiro de escrita inválido (possivelmente esta aberto ou não foi passado o argumento)");
        break;
    case 6:
        perror("O argumento -P está errado.");
        break;
    case 7:
        perror("O argumento -L está errado.");
        break;
    case 8:
        perror("O argumento -D está errado.");
        break;
    case 9:
        perror("O argumento -S está errado.");
        break;
    case 10:
        perror("O ficheiro contêm um erro na linha escrita em cima.");
        break;
    case 11:
        perror("O ficheiros de entrada e de saida são os mesmos.");
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
    printf("\t-S pop\t\t\t\tOrdena de forma decrescente a populacao dos paises\n");
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

char* separar(char sep, char* str, char troca)
{
    int i;
    char* psep = NULL;
    for(i=0; str[i] != '\0' ; i++)   // Executa enquanto não chegar ao final da string
    {
        if(str[i] == sep)       // Quando encontrar o carater passado na variavel "sep" muda esse carater para o que for passado pela variavel "troca" e retorna o endereço do carater a seguir ao trocado
        {
            str[i] = troca;
            psep = &str[i+1];
            break;
        }
    }
    return psep;
}


int verificacao_week(char* str)
{
    int a;
    for(a=0; a != 7; a++)
    {                                        //formato que a string tem de ter é yyyy-ww
        if(isdigit(str[a]) == 0 && a != 4)  //a função isdigit retorna 0 caso não seja um número, logo se qualquer um dos carateres não for um número sem ser o 5º digito(o valor que contém '-') entra no if
        {
            return (1);
        }
        else if(a == 4 && str[4] != '-')    //verifica se o 5º digito é '-', se não for retorna 1
        {
            return(1);
        }
    }
    return (0);                             //retorna 0 caso não tenha erro para não entrar no if do erro
}


int verificacao_palavra(char* str)
{
    int a;
    for(a=0; a < strlen(str); a++)
    {
        if(isdigit(str[a]) != 0)    //a função isdigit retorna 0 caso não seja um número, logo se qualquer um dos carateres for um número entra no if
        {
            return (1);
        }
    }
    return (0); //retorna 0 caso não tenha erro para não entrar no if do erro
}

