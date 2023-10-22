#ifndef AED2_ESPACONAVE_H
#define AED2_ESPACONAVE_H

#include "dados.h"
#include "listaDePassageiros.h"
#include "listaDeRecursos.h"

/// @brief Define o tipo abstrato EspacoNave
struct EspacoNave {
    int prioridade;
    ListaDeRecursos Recursos;
    ListaDePassageiros Passageiros;
};

typedef struct EspacoNave* EspacoNave;

/**
 * @brief Retorna uma tipo struct EspacoNave aloca na memoria Heap
 * 
 * @param prioridade A prioridade da nave na lista de prioridades
 * @return EspacoNave 
 */
EspacoNave novaEspacoNave(int prioridade);

/**
 * @brief Adciona um novo Passageiro a uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser inserida o Passageiro
 * @param id Representa o id do Passageiro a ser criado e adcionado
 * @param idade Representa a idade do Passageiro a ser criado e adcionado
 * @param nome Representa o nome do Passageiro a ser criado e adcionado
 * @param planeta Representa o planeta de Origem do Passageiro a ser criado e adcionado
 * @return int Return 1 se a operação for bem sucedida ou 0 caso contrário
 */
int adcionarPassageiro(EspacoNave nave, int id, int idade, char* nome, char* planeta);

/**
 * @brief Adciona um novo Recurso a uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser inserida o Passageiro
 * @param nome Representa o nome do Recurso a ser criado e adcionado
 * @param quantidade Representa a quantidade do Recurso a ser criado e adcionado
 * @return int Return 1 se a operação for bem sucedida ou 0 caso contrário
 */
int adcionarRecurso(EspacoNave nave, char * nome, int quantidade);

/**
 * @brief Remove um Passageiro de uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser removido um Passageiro
 * @param indice Representa o indice na lista de Passageiros a qual será removido
 * @return int Return 1 se a operação for bem sucedida ou 0 caso contrário
 */
int removerPassageiro(EspacoNave nave, int indice);

/**
 * @brief Remove um Recurso de uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser removido um Recurso
 * @param indice Representa o indice na lista de Recursos a qual será removido
 * @return int Return 1 se a operação for bem sucedida ou 0 caso contrário
 */
int removerRecurso(EspacoNave nave, int indice);

/**
 * @brief Remove todos os Recursos e PAssageiros de uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser esvaziada
 */
void esvaziarEspacoNave(EspacoNave nave);

/**
 * @brief Libera da memória uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser liberada
 */
void deletarEspacoNave(EspacoNave *nave);

/**
 * @brief Imprime na tela uma EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser impressa
 */
void imprimirEspacoNave(EspacoNave nave);

/**
 * @brief Imprime na tela os Passageiros EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser consultada
 */
void imprimirPassageirosDeEspacoNave(EspacoNave nave);

/**
 * @brief Imprime na tela os Recursos EspacoNave
 * 
 * @param nave Representa a EspacoNave a ser consultada
 */
void imprimirRecursosEspacoNave(EspacoNave nave);

#endif // AED2_ESPACONAVE_H