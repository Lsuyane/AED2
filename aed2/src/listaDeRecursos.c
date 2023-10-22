#include <stdio.h>
#include <stdlib.h>

#include "listaDeRecursos.h"

struct NoDeRecursos {
    struct NoDeRecursos *proximo;
    Recurso recurso;
};

ListaDeRecursos novaListaDeRecursos() {
    ListaDeRecursos lista = (ListaDeRecursos) calloc(1, sizeof(ListaDeRecursos));
    return lista;
}

/*
 * Inserção de Recursos
 *
 * Para inserir recurso, precisaremos alocar e copiar os recurso para memória e em seguida
 * adcioná-los/inseri-los em alguma posição da lista. Assim podemos ter até três formas
 * de inserção de recurso sendo as principais:
 * 
 *  1: A lista está vazia e o dado inserido será o de primeiro indice
 *  2: A lista não está vazia e o dado inserido estará entre dos recurso já inseridos
 *  3: A lista não está vazia e o dado será inserido na última poscição
*/

// Caso 1:

int adicionarRecursoAoInicioDaListaDeRecursos(ListaDeRecursos lista, Recurso recurso) {
    if(ehNulaListaDeRecursos(lista)) return 0;

    // Alocação do dado
    NoDeRecursos *novoNo = (NoDeRecursos *) calloc(1, sizeof(NoDeRecursos));

    // Caso a alocação falhe retorna 0
    if(novoNo == NULL)
        return 0;

    // Copia os recurso no espaço de memória alocado anteriormente
    novoNo->proximo = *lista;
    novoNo->recurso = recurso;
    *lista = novoNo;

    return 1;
}

// Caso 2:

int adicionarRecursoAListaDeRecursos(ListaDeRecursos lista, Recurso recurso) {
    // Caso seja uma lista inválida
    if(ehNulaListaDeRecursos(lista)) return 0;

    // Caso a lista esteja vazia é necessário adcionar o dado ao inicio
    if(estaVaziaListaDeRecursos(lista)) return adicionarRecursoAoInicioDaListaDeRecursos(lista, recurso);

    NoDeRecursos *novoNo = (NoDeRecursos *) calloc(1, sizeof(NoDeRecursos));

    // Caso a alocação falhe retorna 0
    if(novoNo == NULL)
        return 0;

    novoNo->proximo = NULL;
    novoNo->recurso = recurso;


    NoDeRecursos* auxiliar = *lista;

    while(auxiliar->proximo != NULL)
        auxiliar = auxiliar->proximo;

    auxiliar->proximo = novoNo;

    return 1;
}

// Caso 3:

int inserirRecursoAListaDeRecursos(ListaDeRecursos lista, Recurso recurso, int indice) {
    // Caso não seja uma lista inválida
    if(ehNulaListaDeRecursos(lista)) return 0;

    // Caso o indice seja igual a zero temos novamente o Caso 1
    else if(indice == 0)
        return adicionarRecursoAoInicioDaListaDeRecursos(lista, recurso);

    // Caso o indice seja o último indice da lista temos o Caso 2
    else if(indice == tamanhoDeListaDeRecursos(lista))
        return adicionarRecursoAListaDeRecursos(lista, recurso);

    // Caso o indice ultrapasse o tamanho da lista
    else if(indice > tamanhoDeListaDeRecursos(lista) || indice < 0)
        return 0;

    // Caso contrário temos o Caso 3
    else {
        int i = 0;
        NoDeRecursos *noAtual = *lista, *noAnterior = NULL;
        NoDeRecursos *novoNo = (NoDeRecursos *) calloc(1, sizeof(NoDeRecursos));

        if(novoNo == NULL)
            return 0;

        novoNo->recurso = recurso;

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
 * Remoção de Recursos
 *
 * Para remover um dado basta liberar os recurso alocados e reajustar os ponteiros.
 * Assim como na inserção há algumas possibilidades de remoção:
 * 
 *  1: A lista está vazia não há nada a fazer
 *  2: A lista não está vazia e o dado a ser removido não tem antecessores
 *  3: A lista não está vazia e o dado a ser removido tem antecessores e/ou sucessores
*/

int removerRecursoAListaDeRecursos(ListaDeRecursos lista, int indice) {
    // Caso 1:
    if(estaVaziaListaDeRecursos(lista) || indice < 0)
        return 0;
    else {
        int i = 0;
        NoDeRecursos *noAnterior = NULL, *noAtual = *lista;

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
 * Recuperação de Recursos
 *
 * Para recuperar os recurso na lista basta procurar o dado e copia seus valores para um ponteiro
 * Lembrando que como a estrutura dado apresenta um ponteiro generico, ao copiar os recurso o ponteiro
 * do dado copiado tembém apontará para o mesmo endereço do original ou seja a alteração do valor de
 * um alterará o outro e vice-versa.
*/

int obterRecursoDaListaDeRecursos(ListaDeRecursos lista, int indice, Recurso *copia) {
    // Caso a lista esteja vazia retorna 0
    if(estaVaziaListaDeRecursos(lista) || indice < 0) return 0;
    // Caso o indice ultrapasse o tamanho da lista
    else if(indice > tamanhoDeListaDeRecursos(lista)) return 0;

    int i = 0;
    NoDeRecursos *auxiliar = *lista;

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

    *copia = auxiliar->recurso;

    return 1;
}

/*
 * Para obter o tamanho da lista basta contarmos o número de nós utilizando um ponteiro auxiliar
*/

int tamanhoDeListaDeRecursos(ListaDeRecursos lista) {
    // Verifica se está vazia
    if(estaVaziaListaDeRecursos(lista)) return 0;

    int tamanho = 1;

    NoDeRecursos * auxiliar = *lista;

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

int ehNulaListaDeRecursos(ListaDeRecursos lista) {
    return lista == NULL;
}

/* 
 * Para verificar se uma lista está vazia basta verificar se o primeiro elemento é NULL ou se não é uma lista válida
*/

int estaVaziaListaDeRecursos(ListaDeRecursos lista) {
    if(ehNulaListaDeRecursos(lista) || *lista == NULL) return 1;
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

void limparListaDeRecursos(ListaDeRecursos lista) {

    // Se há lista está vazia não fazemos nada
    if(!ehNulaListaDeRecursos(lista) && !estaVaziaListaDeRecursos(lista)) {
        NoDeRecursos *noAtual = *lista, *noAnterior = NULL;

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

void deletarListaDeRecursos(ListaDeRecursos *ptrlista) {
    // Verificamos se a lista é válida e a limpamos
    if(!ehNulaListaDeRecursos(*ptrlista)) {
        limparListaDeRecursos(*ptrlista);
    }

    // Liberamos da memória a raiz
    free(*ptrlista);
    *ptrlista = NULL;
}
