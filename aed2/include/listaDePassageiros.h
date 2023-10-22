/**
 * @file listaDePassageiros.h
 * @brief Este arquivo define a estrutura de armazenamento de passageiros em através da implementação
 * de uma lista simplesmente encadeada, assim como suas operações de inserção, remocção, criação e
 * exclusão.
 */

#ifndef AED2_LISTA_DE_PASSAGEIROS_H
#define AED2_LISTA_DE_PASSAGEIROS_H

#include "dados.h"

typedef struct NoDePassageiros NoDePassageiros;
typedef NoDePassageiros ** ListaDePassageiros;

/**
 * @brief Aloca e retorna um ponteiro para uma lista encadeada.
 *
 * @return um ponteiro para uma lista encadeada.
*/
ListaDePassageiros novaListaDePassageiros();

/**
 * @brief Aloca e adiciona um Passageiro a primeira posição de uma lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int adicionarPassageiroAoInicioDaListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro);

/**
 * @brief Aloca e adiciona um Passageiro a última posição de uma lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int adicionarPassageiroAListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro);

/**
 * @brief Aloca e adiciona um Passageiro a uma posição da lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return 1 se a adição ocorrer com sucesso ou 0 se falhar
*/
int inserirPassageiroAListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro, int indice);

/**
 * @brief Remove um Passageiro pelo indice de uma posição na lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @param indice Representa o indice de um Passageiro  na lista encadeada a ser removido.
 * @return 1 se a remoção ocorrer com sucesso ou 0 se falhar
*/
int removerPassageiroAListaDePassageiros(ListaDePassageiros lista, int indice);

/**
 * @brief Copia os passageiro de um indice de uma posição na lista encadeada para um ponteiro copia.
 *
 * @param lista Representa o ponteiro para a lista encadeada a qual deseja-se copiar um Passageiro.
 * @param indice Representa o indice do Passageiro que se desejar copiar.
 * @param copia Representa o ponteiro para a cariavel que sera gravada.
 * @return 1 se possivel gravar ou 0 se falhar.
 */
int obterPassageiroDaListaDePassageiros(ListaDePassageiros lista, int indice, Passageiro *copia);

/**
 * @brief Retorna o tamanho da lista encadeada.
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser modificada.
 * @return um inteiro que representa o tamanho da lista.
 */
int tamanhoDaListaDePassageiros(ListaDePassageiros lista);

/**
 * @brief Verifica se há passageiro inseridos na lista encadeada
 *
 * @param lista Representa o ponteiro para a lista encadeada que se deseja verificar.
 * @return 1 se estiver vazia 0 se tiver passageiro.
 */
int estaVaziaListaDePassageiros(ListaDePassageiros lista);

/**
 * @brief Verifica se o ponteiro do tipo ListaDePassageiros aponta para NULL
 *
 * @param lista Representa o ponteiro para a lista encadeada que se deseja verificar.
 * @return 1 se aponta para NULL, 0 se caso contrário.
 */
int ehNulaListaDePassageiros(ListaDePassageiros lista);

/**
 * @brief Remove todos os valores de uma lista encadeada.
 *
 * @param lista Representa o ponteiro para a lista encadeada a ser esvaziada.
 */
void limparListaDePassageiros(ListaDePassageiros lista);

/**
 * @brief Libera da memoria uma lista encadeada
 *
 * @param ptrlista Representa uma passagem por referência para a lista encadeada a ser excluída.
 */
void deletarListaDePassageiros(ListaDePassageiros *ptrlista);


#endif // AED2_LISTA_DE_PASSAGEIROS_H
