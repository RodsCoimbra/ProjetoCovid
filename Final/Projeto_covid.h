#ifndef projeto_covid
#define projeto_covid
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#define maxficheiro 259 //numero max de carateres de ficheiros no windows
#define max_linha 120



typedef struct Detalhes   // lista que está dentro da lista "pais"
{
    char indic[7];  // Inoforma se a linha indica numero de infetados ou mortes
    int week_count;  // Numero de mortos ou casos na semana
    char year_week[8];  // Semana do ano a que se referem os dados
    double lastfteen; // racio
    int n_dorc; // numero de deaths or cases
    struct Detalhes *nextD; // nextD é o pointer do detalhe seguinte
} Detalhes;

typedef struct Pais
{
    char pais[47]; // tamanho do maior nome de pais existente (Independent and Sovereign Republic of Kiribati). Não considerado The United Kingdom of Great Britain and Northern Ireland pois já havia united kingdom nos exemplos.
    char cod_pais[4];   // código identificador do País 
    char cont[8];   // continente em que o Páis analizado pertence
    int popu;   // população do País em análise
    Detalhes *nextD;    // pointer para o próximo node da lista de detalhes
    struct Pais *nextP; // nextP é o pointer do pais seguinte
} Pais;



/** \brief Função que imprime avisos de erro e o menu de ajuda que contém todas as instruções referentes ao programa
 *
 * \param int Recebe o helpvar, número escolhido para cada tipo de erro
 * \return void
 *
 */
void help(int);


/** \brief
 *
 * \param Pais* Recebe a "head", pointer que aponta para o primeiro elemento da lista de paises
 * \param long Long int recebe o "pop", variavel que contém o valor introduzido no comando da restrição
 * \param int Recebe "restringir", flag que permite com a mesma função executar restrições diferentes
 * \return Pais*  --------------
 *
 */
Pais* restringir_pop(Pais*,long long int, int);

/** \brief  A função executa o comando dado tanto para restringir os dados a uma semana como para o intervalo entre duas semanas decidido no inicio do programa
 *
 * \param Pais* Recebe "head_pais", pointer que aponta para o pais ????primeiro????
 * \param char* Recebe "ano1", pointer que aponta para a data introduzida na inicialização do programa
 * \param char* Recebe "ano2", pointer que aponta para a data introduzida na inicialização do programa
 * \param int recebe "restringir", flag que permite com a mesma função executar restrições diferentes
 * \return Detalhes* -----------
 *
 */
Detalhes* restringir_week(Pais*, char*, char*, int);

/** \brief  A função permite fazer a todos os tipos de seleção que podem ser selecionados no incio do programa, contendo uma flag para a separação de funções
 *
 * \param Pais* Recebe "head_pais", pointer que aponta para o pais ????primeiro????
 * \param int Recebe "select", flag que permite com a mesma função executar restrições diferentes
 * \return Detalhes* ????
 *
 */
Detalhes* selecionar (Pais*, int);


/** \brief  A função percorre a lista de paises á procura de o node de um pais especifico e indica se já existe ou não, esta função é essencial ao funcionamento da função criarP
 *
 * \param char* Recebe a "head", pointer que aponta para o primeiro elemento da lista de paises
 * \param Pais* Struct da lista de paises que cotem os dados fixos
 * \return Pais* Se o pais da linha lida já tiver um node criado a função retorna o endereço desse node de País, se o país ainda não existir na lista de paises é retornado NULL
 *
 */
Pais* encontra_pais(char*,Pais*);


/** \brief  A função tem o trabalho de criar nodes da lista de detalhes
 *
 * \param Detalhes* ???deta???
 * \param char* Recebe "indic", pointer que aponta para variavel na struc que indica se a linha corresponde a cases or deaths
 * \param int valor de infetado/mortes na semana
 * \param char* ano e numero da semana a que os dados da linha pertencem
 * \param double racio de infetados/mortes
 * \param int valor de infetados/mortes totais ????? é ?????
 * \return void
 *
 */
void criarD(Detalhes*,char*, int, char*, double, int);


/** \brief  A função tem o trabalho de criar nodes da lista de países
 *
 * \param Pais* Head da lista principal(lista Pais)
 * \param char* Nome do pais
 * \param char* Código do país a analizar
 * \param char* Continente em que o país se encontra situado
 * \param int   População do país a analizar
 * \param char* Indicador se a linha se refere a infetados ou mortes
 * \param int   Infetados/Mortes na semana em questão
 * \param char* Ano e numero da semana a que os dados da linha pertencem
 * \param double Racio
 * \param int   valor de infetados/mortes totais ????? é ?????
 * \return Pais* Head da lista principal(lista Pais)
 *
 */
Pais* criarP (Pais*, char*, char*, char*,int, char*, int, char*, double, int);

/** \brief  A função separa elementos numa string separados por um carater escolhido e guardado em "sep"
 *
 * \param char  Carater a mudar na string ?duvida se é msm isto?
 * \param char* String que se pretende separar
 * \param char  Carater que se presente colocar em vez do carater que está no "sep" ?é isto?
 * \return char*    String separada ??
 *
 */
char* separar(char, char*, char);


/** \brief A função é utilizada para dar free na memória alocada e por sua vez apagar os dados em questão
 *
 * \param Pais* Head da lista principal(lista Pais)
 * \return void
 *
 */
void apagar(Pais*);


/** \brief Função usada para a ordenação por infetados ou por mortes. Esta passa por todos os valores da lista secundária(lista dos Detalhes)
 *         e retorna o valor de week_count quando tanto a razão(cases ou deaths) como a semana são iguais às especificadas pelo utilizador
 *
 * \param Pais*: Endereço do nó de cada pais da lista Pais
 * \param int: número que indica que modo de -S foi selecionado(3 é -S inf; 4 é -S dea)
 * \param char*: semana escolhida pelo utilizador para ordenar
 * \return int: valor do week_count para ser usado na ordenação ou -1 (flag para a funçao ordena, é negativo pois week_count nunca pode ser esse valor) caso essa semana não exista no programa
 *
 */
int valores(Pais*, int, char*);



/** \brief Função que ordena todos os tipos de -S, com base no algoritmo de bubble sort
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param int: número que indica que modo de -S foi selecionado(1 é -S alfa; 2 é -S pop; 3 é -S inf; 4 é -S dea)
 * \param char*: semana para as ordenações de -S inf e -S dea
 * \return Pais*: Head da lista principal(lista Pais)
 *
 */
Pais* ordenar(Pais*, int, char*);

/** \brief Função que confirma se os argumentos sobre datas passados pelo utilizador estão bem escritos (formato yyyy-ww)
 *
 * \param char*: data passada pelo utilizador
 * \return int: Retorna 0 caso esteja no formato correto e 1 caso contrário
 *
 */
int verificacao_week(char*);

/** \brief Função que confirma se a string passada não contêm algarismos
 *
 * \param char*: dado do ficheiro que se quer analisar
 * \return int: Retorna 0 caso esteja no formato correto e 1 caso contrário
 *
 */
int verificacao_palavra(char*);

/** \brief Função que escolhe qual o modo de seleção pretendido pelo utilizador e aplica o a todos os países existentes na lista
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param char*: Argumento passado pelo utilizador no -D
 * \return void
 *
 */
void Escolher_sel(Pais*, char*);

/** \brief Função que escolhe qual o modo de restrição pretendido pelo utilizador
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param char*: Argumento passado pelo utilizador no -P
 * \param int long long: população caso seja -P min ou -P max e 0 caso contrário
 * \param char*: Data passada pelo utilizador no -P date ou -P dates
 * \param char*: 2ª data passada pelo utilizador para o -P dates
 * \return Pais*: Head da lista principal(lista Pais)
 *
 */
Pais* Escolher_restri(Pais*,char*,long long int, char*, char*);

/** \brief Função que escolhe qual o modo de ordenação pretendido pelo utilizador
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param char*: Argumento passado pelo utilizador no -S ou "alfa" caso o utilizador não introduza nada
 * \param char*: data passada pelo utilizador no caso -S inf ou -S dea
 * \return Pais*: Head da lista principal(lista Pais)
 *
 */
Pais* Escolher_orde(Pais*, char*, char*);

/** \brief
 *
 * \param FILE*: Ficheiro em que se vai escrever
 * \param Pais*: Head da lista principal(lista Pais)
 * \param char*: extensão do ficheiro de escrita(.csv ou .dat)
 * \return void
 *
 */
void escrita(FILE*, Pais*, char*);

/** \brief
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param FILE*: Ficheiro em que se vai ler
 * \param char*: extensão do ficheiro de leitura(.csv ou .dat)
 * \param FILE*: Ficheiro em que se vai escrever
 * \param char*: Argumento passado pelo utilizador no -L ou "all" caso o utilizador não introduza nada
 * \param char*: extensão do ficheiro de escrita(.csv ou .dat)
 * \return Pais*: Head da lista principal(lista Pais)
 *
 */
Pais* leit(Pais*, FILE*, char*, FILE*, char*, char*);

#endif // projeto_covid
