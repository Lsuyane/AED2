/**
 * @file dados.h
 * @brief Este arquivo define uma abstração dos dados utilizados no projeto, assim como suas operações
 * de inserção, remocção, criação e exclusão.
 */

#ifndef AED2_DADOS_H
#define AED2_DADOS_H

/// @brief Define a estrutura de dado abstrato Passageiro
struct Passageiro {
    int id;
    int idade;
    char *nome;
    char *planetaDeOrigem;
};

/// @brief Define a estrutura de dado abstrato Recurso
struct Recurso {
    char *nome;
    int quantidade;
};

typedef struct Recurso * Recurso;
typedef struct Passageiro * Passageiro;

/**
 * @brief Retorna um ponteiro para uma struct Passageiro alocados na Heap
 * 
 * @param id Representa o id do Passageiro
 * @param idade Representa o idade do Passageiro
 * @param nome Representa o nome do Passageiro
 * @param planeta Representa o nome do planeta de origem do Passageiro
 * @return Passageiro 
 */
Passageiro novoPassageiro(int id, int idade, char *nome, char *planeta);

/**
 * @brief Retorna um ponteiro para uma struct Recurso alocados na Heap
 * 
 * @param nome Representa o nome do recurso
 * @param quantidade Representa a quantidade disponivel daquele recurso existe
 * @return Recurso 
 */
Recurso novoRecurso(char *nome, int quantidade);

/**
 * @brief Libera da memoria Heap um Passageiro preveamente alocado
 * 
 * @param recurso Pointeiro para o Passageiro a ser removido
 */
void excluirPassageiro(Passageiro passageiro);

/**
 * @brief Libera da memoria Heap um recurso preveamente alocado
 * 
 * @param recurso Pointeiro para o recurso a ser removido
 */
void excluirRecurso(Recurso recurso);

/**
 * @brief Imprime na tela os dados de struct Recurso
 * 
 * @param recurso O ponteiro para recurso a ser impresso
 */
void imprimirRecurso(Recurso recurso);

/**
 * @brief Imprime na tela os dados de struct Passageiro
 * 
 * @param recurso O ponteiro para passageiro a ser impresso
 */
void imprimirPassageiro(Passageiro passageiro);

#endif // AED2_DADOS_H