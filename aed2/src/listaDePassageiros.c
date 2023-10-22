#include <stdio.h>
#include <stdlib.h>

#include "listaDePassageiros.h"

struct NoDePassageiros {
    struct NoDePassageiros *proximo;
    Passageiro passageiro;
};

ListaDePassageiros novaListaDePassageiros() {
    ListaDePassageiros lista = (ListaDePassageiros) calloc(1, sizeof(ListaDePassageiros));
    return lista;
}

/*
 * Inserção de Passageiros
 *
 * Para inserir passageiro, precisaremos alocar e copiar os passageiro para memória e em seguida
 * adcioná-los/inseri-los em alguma posição da lista. Assim podemos ter até três formas
 * de inserção de passageiro sendo as principais:
 * 
 *  1: A lista está vazia e o dado inserido será o de primeiro indice
 *  2: A lista não está vazia e o dado inserido estará entre dos passageiro já inseridos
 *  3: A lista não está vazia e o dado será inserido na última poscição
*/

// Caso 1:

int adicionarPassageiroAoInicioDaListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro) {
    if(ehNulaListaDePassageiros(lista)) return 0;

    // Alocação do dado
    NoDePassageiros *novoNo = (NoDePassageiros *) calloc(1, sizeof(NoDePassageiros));

    // Caso a alocação falhe retorna 0
    if(novoNo == NULL)
        return 0;

    // Copia os passageiro no espaço de memória alocado anteriormente
    novoNo->proximo = *lista;
    novoNo->passageiro = passageiro;
    *lista = novoNo;

    return 1;
}

// Caso 2:

int adicionarPassageiroAListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro) {
    // Caso seja uma lista inválida
    if(ehNulaListaDePassageiros(lista)) return 0;

    // Caso a lista esteja vazia é necessário adcionar o dado ao inicio
    if(estaVaziaListaDePassageiros(lista)) return adicionarPassageiroAoInicioDaListaDePassageiros(lista, passageiro);

    NoDePassageiros *novoNo = (NoDePassageiros *) calloc(1, sizeof(NoDePassageiros));

    // Caso a alocação falhe retorna 0
    if(novoNo == NULL)
        return 0;

    novoNo->proximo = NULL;
    novoNo->passageiro = passageiro;


    NoDePassageiros* auxiliar = *lista;

    while(auxiliar->proximo != NULL)
        auxiliar = auxiliar->proximo;

    auxiliar->proximo = novoNo;

    return 1;
}

// Caso 3:

int inserirPassageiroAListaDePassageiros(ListaDePassageiros lista, Passageiro passageiro, int indice) {
    // Caso não seja uma lista inválida
    if(ehNulaListaDePassageiros(lista)) return 0;

    // Caso o indice seja igual a zero temos novamente o Caso 1
    else if(indice == 0)
        return adicionarPassageiroAoInicioDaListaDePassageiros(lista, passageiro);

    // Caso o indice seja o último indice da lista temos o Caso 2
    else if(indice == tamanhoDaListaDePassageiros(lista))
        return adicionarPassageiroAListaDePassageiros(lista, passageiro);

    // Caso o indice ultrapasse o tamanho da lista
    else if(indice > tamanhoDaListaDePassageiros(lista) || indice < 0)
        return 0;

    // Caso contrário temos o Caso 3
    else {
        int i = 0;
        NoDePassageiros *noAtual = *lista, *noAnterior = NULL;
        NoDePassageiros *novoNo = (NoDePassageiros *) calloc(1, sizeof(NoDePassageiros));

        if(novoNo == NULL)
            return 0;

        novoNo->passageiro = passageiro;

        // Procurar a posição correta para inserir o dado
        while(i < indice && noAtual != NULL) {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            i++;
        }

        // Inserção do novo nó
        noAnterior->proximo = novoNo;
        novoNo->proximo = noAtual;

        return 1;
    }
}

/*
 * Remoção de Passageiros
 *
 * Para remover um dado basta liberar os passageiro alocados e reajustar os ponteiros.
 * Assim como na inserção há algumas possibilidades de remoção:
 * 
 *  1: A lista está vazia não há nada a fazer
 *  2: A lista não está vazia e o dado a ser removido não tem antecessores
 *  3: A lista não está vazia e o dado a ser removido tem antecessores e/ou sucessores
*/

int removerPassageiroAListaDePassageiros(ListaDePassageiros lista, int indice) {
    // Caso 1:
    if(estaVaziaListaDePassageiros(lista) || indice < 0)
        return 0;
    else {
        int i = 0;
        NoDePassageiros *noAnterior = NULL, *noAtual = *lista;

        // Segmetation fault
        while(i < indice && noAtual->proximo != NULL) {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            i++;
        }

        // Caso 3: irá remover um elemento entre dois elementos 
        if(noAnterior != NULL) {
            // o elemento anterior irá apontar para o elemento sucessor ao elemento atual
            noAnterior->proximo = noAtual->proximo;
        } 
        
        // Caso 2: irá remover o primeiro elemento
        else {
            // Não há antecessores logo devemos atualizar o ponteiro para o começo da lista
            *lista = noAtual->proximo;
        }

        free(noAtual);
        noAtual = NULL;
        return 1;
    }
}

/*
 * Recuperação de Passageiros
 *
 * Para recuperar os passageiro na lista basta procurar o dado e copia seus valores para um ponteiro
 * Lembrando que como a estrutura dado apresenta um ponteiro generico, ao copiar os passageiro o ponteiro
 * do dado copiado tembém apontará para o mesmo endereço do original ou seja a alteração do valor de
 * um alterará o outro e vice-versa.
*/

int obterPassageiroDaListaDePassageiros(ListaDePassageiros lista, int indice, Passageiro *copia) {
    // Caso a lista esteja vazia retorna 0
    if(estaVaziaListaDePassageiros(lista) || indice < 0) return 0;
    // Caso o indice ultrapasse o tamanho da lista
    else if(indice > tamanhoDaListaDePassageiros(lista)) return 0;

    int i = 0;
    NoDePassageiros *auxiliar = *lista;

    // Busca o dado pelo indice
    while(i < indice && auxiliar != NULL) {
        auxiliar = auxiliar->proximo;
        i++;
    }

    // Caso não encontre
    if(auxiliar == NULL)
        return 0;

    // Caso o pontoreiro de copia aponte para NULL
    if(copia == NULL)
        return 0;

    *copia = auxiliar->passageiro;

    return 1;
}

/*
 * Para obter o tamanho da lista basta contarmos o número de nós utilizando um ponteiro auxiliar
*/

int tamanhoDaListaDePassageiros(ListaDePassageiros lista) {
    // Verifica se está vazia
    if(estaVaziaListaDePassageiros(lista)) return 0;

    int tamanho = 1;

    NoDePassageiros * auxiliar = *lista;

    // Conta o número de nós da lista
    while(auxiliar->proximo != NULL) {
        tamanho++;
        auxiliar = auxiliar->proximo;
    }

    return tamanho;
}


/*
 * Para verificar se uma lista é válida basta verificar se a raiz não aponta para NULL
*/

int ehNulaListaDePassageiros(ListaDePassageiros lista) {
    return lista == NULL;
}

/* 
 * Para verificar se uma lista está vazia basta verificar se o primeiro elemento é NULL ou se não é uma lista válida
*/

int estaVaziaListaDePassageiros(ListaDePassageiros lista) {
    if(ehNulaListaDePassageiros(lista) || *lista == NULL) return 1;
    return 0;
}

/*
 * Exclusão da lista
 * 
 * Para excluir a lista, devemos remover todas as alocações feitas durante suas operações, pois 
 * se apenas for liberado da memória a raiz haverá lixo de memória por toda parte, portanto é preciso:
 * 1: Liberar da memória todos seus membros ou seja limpar a lista
 * 2: Liberar a raiz da memória
 */

// Caso 1

void limparListaDePassageiros(ListaDePassageiros lista) {

    // Se há lista está vazia não fazemos nada
    if(!ehNulaListaDePassageiros(lista) && !estaVaziaListaDePassageiros(lista)) {
        NoDePassageiros *noAtual = *lista, *noAnterior = NULL;

        // Caso contrário utilizamos dois ponteiros auxiliares para percorrer a lista removendo seus itens 
        while(noAtual != NULL) {
            noAnterior = noAtual;
            noAtual = noAtual->proximo;
            
            // Liberação do item da memória
            free(noAnterior);
            noAnterior = NULL;
        }

        // Aqui desreferenciamos o primeiro elemento
        *lista = NULL;
    }
}

// Caso 2

void deletarListaDePassageiros(ListaDePassageiros *ptrlista) {
    // Verificamos se a lista é válida e a limpamos
    if(!ehNulaListaDePassageiros(*ptrlista)) {
        limparListaDePassageiros(*ptrlista);
    }

    // Liberamos da memória a raiz
    free(*ptrlista);
    *ptrlista = NULL;
}
