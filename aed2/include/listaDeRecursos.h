/**
 * @file listaDeRecursos.h
 * @brief Este arquivo define a estrutura de armazenamento de recursos em através da implementação
 * de uma lista simplesmente encadeada, assim como suas operações de inserção, remoção, criação e
 * exclusão.
 */

#ifndef AED2_LISTA_DE_RECURSOS_H
#define AED2_LISTA_DE_RECURSOS_H

#include "dados.h"

typedef struct NoDeRecursos NoDeRecursos;
typedef NoDeRecursos ** ListaDeRecursos;

/**
 * @brief Aloca e retorna um ponteiro para uma lista encadeada.
 *
 * @return um ponteiro para uma lista encadeada.
*/
ListaDeRecursos novaListaDeRecursos();

/**
 * @brief Aloca e adiciona um dado a primeira posição de uma lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int adicionarRecursoAoInicioDaListaDeRecursos(ListaDeRecursos lista, Recurso recurso);

/**
 * @brief Aloca e adiciona um dado a última posição de uma lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int adicionarRecursoAListaDeRecursos(ListaDeRecursos lista, Recurso recurso);

/**
 * @brief Aloca e adiciona um dado a uma posição da lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int inserirRecursoAListaDeRecursos(ListaDeRecursos lista, Recurso recurso, int indice);

/**
 * @brief Remove um dado pelo indice de uma posição na lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @param indice Representa o indice de um dado  na lista encadeada a ser removido.
 * @return 1 se a remoção ocorrer com sucesso ou 0 se falhar
*/
int removerRecursoAListaDeRecursos(ListaDeRecursos lista, int indice);

/**
 * @brief Copia os recurso de um indice de uma posição na lista encadeada para um ponteiro copia.
 *
 * @param lista Representa o ponteiro para a lista encadeada a qual deseja-se copiar um dado.
 * @param indice Representa o indice do dado que se desejar copiar.
 * @param copia Representa o ponteiro para a cariavel que sera gravada.
 * @return 1 se possivel gravar ou 0 se falhar.
 */
int obterRecursoDaListaDeRecursos(ListaDeRecursos lista, int indice, Recurso *copia);

/**
 * @brief Retorna o tamanho da lista encadeada.
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return um inteiro que representa o tamanho da lista.
 */
int tamanhoDeListaDeRecursos(ListaDeRecursos lista);

/**
 * @brief Verifica se há recurso inseridos na lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada que se deseja verificar.
 * @return 1 se estiver vazia 0 se tiver recurso.
 */
int estaVaziaListaDeRecursos(ListaDeRecursos lista);

/**
 * @brief Verifica se o ponteiro do tipo ListaDeRecursos aponta para NULL
 *
 * @param lista Representa o ponteiro para a lista encadeada que se deseja verificar.
 * @return 1 se aponta para NULL, 0 se caso contrário.
 */
int ehNulaListaDeRecursos(ListaDeRecursos lista);

/**
 * @brief Remove todos os valores de uma lista encadeada.
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser esvaziada.
 */
void limparListaDeRecursos(ListaDeRecursos lista);

/**
 * @brief Libera da memoria uma lista encadeada
 *
 * @param ptrlista Representa uma passagem por referência para a lista encadeada a ser excluída.
 */
void deletarListaDeRecursos(ListaDeRecursos *ptrlista);


#endif // AED2_LISTA_DE_RECURSOS_H
