#ifndef AED2_LISTA_DE_PRIORIDADES_H
#define AED2_LISTA_DE_PRIORIDADES_H

#include "espaconave.h"

typedef struct NoDePrioridades NoDePrioridades;
typedef struct Cabecalho {
    struct NoDePrioridades *inicio;
    struct NoDePrioridades *fim;
    int tamanho;
} FilaDePrioridade;

/**
 * @brief Aloca e retorna um ponteiro para uma lista de prioridades.
 *
 * @return um ponteiro para uma lista encadeada.
*/
FilaDePrioridade *novaFilaDePrioridade();

/**
 * @brief Aloca e adciona uma nave a lista de prioridades
 *
 * @param fila Representa o ponteiro para a lista
 * @param nave Representa o nave a ser inserida a lista
 * @return 1 se a adcição ocorrer com sucesso ou 0 se falhar
*/
int adicionarItemAFilaDePrioridade(FilaDePrioridade *fila, EspacoNave nave);

/**
 * @brief Remove o primeiro item da lista sem liberar da memoria
 *
 * @param fila Representa o ponteiro para a lista
 * @return 1 se a adcição ocorrer com sucesso ou 0 se falhar
*/
int removerItemDaFilaDePrioridade(FilaDePrioridade *fila);

/**
 * @brief Remove um item da lista sem liberar da memoria e copia o item removido para um ponteiro
 *
 * @param fila Representa o ponteiro para a lista
 * @param prioridade Representa a prioridade do elemento a ser excluido da lista
 * @param cpy Representa um ponteiro onde serão movidos os dados removidos
 * @return 1 se a adcição ocorrer com sucesso ou 0 se falhar
*/
int excluirItemDaFilaDePrioridade(FilaDePrioridade *fila, int prioridade, EspacoNave *cpy);

/**
 * @brief Copia o primeiro item da lista
 *
 * @param fila Representa o ponteiro para a lista
 * @param copia Representa um ponteiro onde serão movidos os dados removidos
 * @return 1 se a adcição ocorrer com sucesso ou 0 se falhar
*/
int obterItemDaFilaDePrioridade(FilaDePrioridade *fila, EspacoNave *copia);

/**
 * @brief Copia o item na posição x da lista
 *
 * @param fila Representa o ponteiro para a lista
 * @param indice Representa a posição que deseja copiar
 * @param copia Representa um ponteiro onde serão movidos os dados removidos
 * @return 1 se a adcição ocorrer com sucesso ou 0 se falhar
*/
int obterIndexDaFilaDePriodade(FilaDePrioridade *fila, int indice, EspacoNave *copia);

/**
 * @brief Retorna o tamanho da lista
 * 
 * @param fila Representa o ponteiro para a lista
 * @return int Representa o tamnho da lista
 */
int tamanhoDaFilaDePrioridade(FilaDePrioridade *fila);

/**
 * @brief Verifica se a lista estaá vazia
 * 
 * @param fila Representa o ponteiro para a lista
 * @return int 1 se estiver vazia  caso contrário
 */
int estaVaziaFilaDePrioridade(FilaDePrioridade *fila);

/**
 * @brief Libera da memoria a lista
 * 
 * @param fila Representa o ponteiro para a lista
 */
void deletarFilaDePrioridade(FilaDePrioridade *fila);

/**
 * @brief Imprime a lista
 * 
 * @param fila Representa o ponteiro para a lista
 */
void imprimirFilaDePrioridade(FilaDePrioridade *fila);


#endif // AED2_LISTA_DE_PRIORIDADES_H