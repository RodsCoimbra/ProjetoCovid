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
    char pais[46];
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


/** \brief
 *
 * \param Pais*
 * \param int
 * \param char*
 * \return int
 *
 */
int valores(Pais*, int, char*);



/** \brief
 *
 * \param Pais*
 * \param int
 * \param char*
 * \return Pais*
 *
 */
Pais* ordenar(Pais*, int, char*);

/** \brief
 *
 * \param char*
 * \return int
 *
 */
int verificacao_week(char*);

/** \brief
 *
 * \param str char*
 * \return int
 *
 */
int verificacao_palavra(char*);

/** \brief
 *
 * \param Pais*
 * \param char*
 * \return void
 *
 */
void Escolher_sel(Pais*, char*);

/** \brief
 *
 * \param Pais*
 * \param char*
 * \return Pais*
 *
 */
Pais* Escolher_restri(Pais*,char*,long long int, char*, char*);

/** \brief
 *
 * \param Pais*
 * \param char*
 * \param char*
 * \return Pais*
 *
 */
Pais* Escolher_orde(Pais*, char*, char*);


#endif // projeto_covid
