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
    char indic[7];      // Informa se a linha indica numero de infetados ou mortes
    int week_count;     // Numero de mortos ou casos na semana
    char year_week[8];  // Semana do ano a que se referem os dados
    double lastfteen;   // racio
    int n_dorc;         // numero de deaths or cases
    struct Detalhes *nextD; // nextD é o pointer do detalhe seguinte
} Detalhes;

typedef struct Pais
{
    char pais[47];      //Tamanho do maior nome de pais existente (Independent and Sovereign Republic of Kiribati). Não considerado The United Kingdom of Great Britain and Northern Ireland pois já havia united kingdom nos exemplos.
    char cod_pais[4];   // código identificador do País
    char cont[8];       // continente em que o País analizado pertence
    int popu;           // população do País em anális
    Detalhes *nextD;    // pointer para o node da lista de detalhes
    struct Pais *nextP; // nextP é o pointer do pais seguinte
} Pais;



/** \brief Função que imprime avisos de erro e o menu de ajuda que contém todas as instruções referentes ao programa
 *
 * \param int: Recebe o helpvar, número escolhido para cada tipo de erro
 * \return void
 *
 */
void help(int);


/** \brief A função executa o comando dado tanto para restringir os dados por população minima e máxima
 *
 * \param Pais*: Recebe a "head", pointer que aponta para o primeiro elemento da lista de paises
 * \param long Long int: Recebe o "pop", variavel que contém o valor introduzido no comando da restrição e que simboliza a população
 * \param int: Recebe "restringir", flag que permite com a mesma função executar restrições diferentes
 * \return Pais*: Retorna a nova head da lista principal(lista Pais)
 *
 */
Pais* restringir_pop(Pais*,long long int, int);

/** \brief A função executa o comando dado tanto para restringir os dados a uma semana como para o intervalo entre duas semanas decidido no inicio do programa
 *
 * \param Pais*: Recebe "head_pais", endereço do nó de cada pais da lista Pais
 * \param char*: Recebe "ano1", pointer que aponta para a data introduzida na inicialização do programa
 * \param char*: Recebe "ano2", pointer que aponta para a data introduzida na inicialização do programa
 * \param int: Recebe "restringir", flag que permite com a mesma função executar restrições diferentes
 * \return Detalhes*: Retorna a nova head da lista secundária(lista Detalhes)
 *
 */
Detalhes* restringir_week(Pais*, char*, char*, int);


/** \brief A função permite fazer todos os tipos de seleção que podem ser selecionados no incio do programa
 *
 * \param Pais*: Recebe "head_pais", endereço do nó de cada pais da lista Pais
 * \param int: Recebe "select", flag que permite com a mesma função executar restrições diferentes
 * \return Detalhes*: Retorna a nova head da lista secundária(lista Detalhes)
 *
 */
Detalhes* selecionar (Pais*, int);


/** \brief A função percorre a lista de paises à procura do node de um pais especifico e indica se já existe ou não, esta função é essencial ao funcionamento da função criarP
 *
 * \param char*: Recebe a sigla do pais para comparar com as já existentes
 * \param Pais*: Recebe a "head", pointer que aponta para o primeiro elemento da lista de paises
 * \return Pais*: Se o pais da linha lida já tiver um node criado a função retorna o endereço desse node de País, se o país ainda não existir na lista de paises é retornado NULL
 *
 */
Pais* encontra_pais(char*,Pais*);


/** \brief  A função serve para criar nodes da lista de detalhes
 *
 * \param Detalhes*: Recebe "deta", endereço da head da lista secundária(lista Detalhes) de cada pais
 * \param char*: Recebe "indic", pointer que aponta para a variavel na struct que indica se a linha corresponde a cases or deaths
 * \param int: valor de infetado/mortes na semana
 * \param char*: ano e numero da semana a que os dados da linha pertencem
 * \param double: racio de infetados/mortes
 * \param int: valor de infetados/mortes totais
 * \return void
 *
 */
void criarD(Detalhes*,char*, int, char*, double, int);


/** \brief A função serve para criar nodes da lista de países
 *
 * \param Pais*:    Head da lista principal(lista Pais)
 * \param char*:    Nome do pais
 * \param char*:    Código do país a analisar
 * \param char*:    Continente em que o país se encontra situado
 * \param int:      População do país a analisar
 * \param char*:    Indicador se a linha se refere a infetados ou mortes
 * \param int:      Infetados/Mortes na semana em questão
 * \param char*:    Ano e numero da semana a que os dados da linha pertencem
 * \param double:   Racio
 * \param int:      valor de infetados/mortes totais
 * \return Pais*:   Head da lista principal(lista Pais)
 *
 */
Pais* criarP (Pais*, char*, char*, char*,int, char*, int, char*, double, int);

/** \brief A função procura o elemento dado em "sep" numa string, substitui por "troca" e retorna o endereço do carater a seguir ao trocado
 *
 * \param char:  Carater a encontrar na string
 * \param char*: String que se pretende separar
 * \param char:  Carater que se presente colocar em vez do carater que está no "sep"
 * \return char*:  Endereço do carater a seguir ao encontrado ou NULL caso não encontre "sep"
 *
 */
char* separar(char, char*, char);



/** \brief  A função é utilizada para dar free na memória alocada
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \return void
 *
 */
void apagar(Pais*);


/** \brief Função usada para a ordenação por infetados ou por mortes. Esta passa por todos os valores da lista secundária(lista dos Detalhes)
 *         e retorna o valor de week_count quando, tanto a razão(cases ou deaths) como a semana são iguais às especificadas pelo utilizador
 *
 * \param Pais*: Endereço do nó de cada pais da lista Pais
 * \param int: número que indica que modo de -S foi selecionado(3 é -S inf; 4 é -S dea)
 * \param char*: semana escolhida pelo utilizador para ordenar
 * \return int: valor do week_count para ser usado na ordenação ou -1 (flag para a funçao ordena, é negativo pois week_count nunca pode ser esse valor) caso essa semana não exista no ficheiro de leitura depois das tratamentos anteriores
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

/** \brief Função que confirma se a string passada só contêm letras e espaços
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
 * \param int long long: população caso o utilizador use o -P min ou -P max e 0 caso contrário
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

/** \brief Escrita dos dados já tratados no ficheiro de escrita
 *
 * \param FILE*: Ficheiro em que se vai escrever
 * \param Pais*: Head da lista principal(lista Pais)
 * \param char*: Extensão do ficheiro de escrita(.csv ou .dat)
 * \return void
 *
 */
void escrita(FILE*, Pais*, char*);

/** \brief Leitura dos argumentos e caso o ficheiro de leitura seja .dat ele também escreve
 *
 * \param Pais*: Head da lista principal(lista Pais)
 * \param FILE*: Ficheiro em que se vai ler
 * \param char*: Extensão do ficheiro de leitura(.csv ou .dat)
 * \param FILE*: Ficheiro em que se vai escrever
 * \param char*: Argumento passado pelo utilizador no -L ou "all" caso o utilizador não introduza nada
 * \param char*: Extensão do ficheiro de escrita(.csv ou .dat)
 * \return Pais*: Head da lista principal(lista Pais)
 *
 */
Pais* leit(Pais*, FILE*, char*, FILE*, char*, char*);

#endif // projeto_covid
