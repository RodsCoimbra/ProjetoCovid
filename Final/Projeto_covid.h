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
    char indic[7];
    int week_count;
    char year_week[8];
    double lastfteen; // racio
    int n_dorc; // numero de deaths or cases
    struct Detalhes *nextD; // nextD é o pointer do detalhe seguinte
} Detalhes;

typedef struct Pais
{
    char pais[47]; //Tamanho do maior nome de pais existente (Independent and Sovereign Republic of Kiribati). Não considerado The United Kingdom of Great Britain and Northern Ireland pois já havia united kingdom nos exemplos.
    char cod_pais[4];
    char cont[8];
    int popu;
    Detalhes *nextD;
    struct Pais *nextP; // nextP é o pointer do pais seguinte
} Pais;



/** \brief
 *
 * \param int
 * \return void
 *
 */
void help(int);


/** \brief
 *
 * \param Pais*
 * \param int
 * \param int
 * \return Pais*
 *
 */
Pais* restringir_pop(Pais*,long long int, int);

/** \brief
 *
 * \param Pais*
 * \param char*
 * \param char*
 * \param int
 * \return Detalhes*
 *
 */
Detalhes* restringir_week(Pais*, char*, char*, int);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
Detalhes* selecionar (Pais*, int);


/** \brief
 *
 * \param char*
 * \param Pais*
 * \return Pais*
 *
 */
Pais* encontra_pais(char*,Pais*);


/** \brief
 *
 * \param Detalhes*
 * \param char*
 * \param int
 * \param char*
 * \param double
 * \param int
 * \return void
 *
 */
void criarD(Detalhes*,char*, int, char*, double, int);


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
Pais* criarP (Pais*, char*, char*, char*,int, char*, int, char*, double, int);

/** \brief
 *
 * \param char
 * \param char*
 * \param char
 * \return char*
 *
 */
char* separar(char, char*, char);


/** \brief
 *
 * \param Pais*
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
