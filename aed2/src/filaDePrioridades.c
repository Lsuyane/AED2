#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "filaDePrioridades.h"

struct NoDePrioridades {
    EspacoNave nave;
    struct NoDePrioridades *proximo;
    struct NoDePrioridades *anterior;
};

FilaDePrioridade *novaFilaDePrioridade() {
    FilaDePrioridade *fila = (FilaDePrioridade *) calloc(1, sizeof(FilaDePrioridade));
    
    fila->fim = NULL;
    fila->tamanho = 0;
    fila->inicio = NULL;
    
    return fila;
}

void filhoDosNo(FilaDePrioridade *fila, NoDePrioridades *pai, NoDePrioridades **esq, NoDePrioridades **dir) {
    NoDePrioridades *auxiliar = fila->inicio;
    int posicaoDoPai = 0;
    int posicaoDoFilhoEsq = 0;
    int posicaoDoFilhoDir = 0;

    // Encontre a posição do nó pai
    while (auxiliar != NULL && auxiliar != pai) {
        auxiliar = auxiliar->proximo;
        posicaoDoPai++;
    }

    // Verifique se o pai não foi encontrado
    if (auxiliar != pai) {
        *esq = NULL;
        *dir = NULL;
        return;
    }

    posicaoDoFilhoEsq = 2 * posicaoDoPai + 1;
    posicaoDoFilhoDir = 2 * posicaoDoPai + 2;

    auxiliar = fila->inicio;  // Reinicie auxiliar para o início da fila

    // Encontre o filho esquerdo
    for (int i = 0; i < posicaoDoFilhoEsq; i++) {
        auxiliar = auxiliar->proximo;
    }

    *esq = auxiliar;

    // Encontre o filho direito
    for (int i = 0; i < posicaoDoFilhoDir; i++) {
        auxiliar = auxiliar->proximo;
    }

    *dir = auxiliar;
}

/**
 * @brief Retorna o Nó da fila de prioridades que e ancestral de um dado Nó
 * 
 * @param fila Representa a fila onde será feita a busca
 * @param filho Representa o Nó que desejamos encontrar seus ancestral
 * @return NoDePrioridades* O ancestral de um no filho
 */
NoDePrioridades *paiDoNo(FilaDePrioridade *fila, NoDePrioridades *filho) {
    if(filho == fila->inicio) {
        return NULL; // Se o filho é o nó raiz, não há pai.
    }

    int posicaoDoFilho = 0;
    NoDePrioridades *ancestral = fila->inicio;

    // Encontre a posição do nó filho na fila
    while(ancestral != filho) {
        ancestral = ancestral->proximo;
        posicaoDoFilho++;
    }

    ancestral = fila->inicio;
    int indiceDoAncestral = (int)floor(posicaoDoFilho / 2) - 1;

    // Percorra a fila para encontrar o nó ancestral
    for(int i = 0; i < indiceDoAncestral; i++) {
        ancestral = ancestral->proximo;
    }

    return ancestral;
}

/**
 * @brief Restaura as propriedades da fila de Prioridades
 * 
 * @param fila Representa a fila de Prioridades
 * @return int 1 se tudo ocorreu bem 0 caso contrário
 */
int adicionarAux(FilaDePrioridade *fila) {

    EspacoNave naveAux;
    NoDePrioridades * auxiliar = fila->fim;

    // Verifique se auxiliar não é o nó raiz antes de continuar
    if (auxiliar == fila->inicio) {
        return 1;
    }

    NoDePrioridades * ancestral = paiDoNo(fila, auxiliar);

    // Sobe a árvore corrigindo as prioradades dos elementos
    while (ancestral != NULL && auxiliar->nave->prioridade > ancestral->nave->prioridade) {
        naveAux = auxiliar->nave;
        auxiliar->nave = ancestral->nave;
        ancestral->nave = naveAux;
        
        auxiliar = ancestral;
        ancestral = paiDoNo(fila, ancestral);
    }

    return 1;
}

int adicionar_clandestino(int *prioridade) {
    int numeroAleatorio = rand();
    
    if(numeroAleatorio % 10 == 0) {
        // Escolha uma prioridade aleatoria menor que zero
        *prioridade = 0 > numeroAleatorio ? numeroAleatorio : -numeroAleatorio;
        return 1;
    }

    return 0;
}

int adicionarItemAFilaDePrioridade(FilaDePrioridade *fila, EspacoNave nave) {
    /* Note que como implementamos a fila com uma lista duplamente encadeada
     * precisamos asegurar que a adição de novos elementos não remover as propriedades da fila
     * Para isso basta a inserir o elemento ao final da lista e em seguida o trocado de lugar com
     * seu pai até que sua posição seja a ideal
     */
    NoDePrioridades *novoNo = (NoDePrioridades *) calloc(1, sizeof(NoDePrioridades));
    novoNo->nave = nave;
    
    // Tem a chance de 10% de mudar a prioridade
    adicionar_clandestino(&novoNo->nave->prioridade);

    // Caso a alocação falhe retorna 0
    if(novoNo == NULL)
        return 0;

    // Caso não hajam elementos não e preciso verificar a quebra da propriedade
    if(estaVaziaFilaDePrioridade(fila)) {
        fila->inicio = novoNo;
        fila->fim = novoNo;
        fila->tamanho++;
        return 1;
    }

    else {
        // Adciona o elemento ao final
        fila->fim->proximo = novoNo;
        novoNo->anterior = fila->fim;
        fila->fim = novoNo;
        fila->tamanho++;
        
        // Chama a função de reordenação da fila se falhar o no e liberado da memoria e retorna 0;
        if(!adicionarAux(fila)) {
            fila->fim = fila->fim->anterior;
            free(novoNo);
            novoNo = NULL;
            fila->tamanho--;
            return 0;
        }

        return 1;
    }
}

/**
 * @brief Copia o elemento de maior prioridade da fila
 * 
 * @param fila Representa o ponteiro para a fila
 * @param copia Representa o ponteiro onde a copia sera feita
 * @return int Retorna 1 se funcionar 0 caso contrario
 */
int obterItemDaFilaDePrioridade(FilaDePrioridade *fila, EspacoNave *copia) {
    if(estaVaziaFilaDePrioridade(fila)) return 0;

    // Caso o pontoreiro de copia aponte para NULL
    if(copia == NULL)
        return 0;

    *copia = fila->inicio->nave;
    return 1;
}

/**
 * @brief Copia um respectivo no da fila
 * 
 * @param fila Representa o ponteiro para a fila
 * @param indice Representa o Indice que se deseja copiar
 * @param copia Representa o ponteiro onde a copia sera feira
 * @return int Retorna 1 se funcionar 0 caso contrario
 */
int obterIndexDaFilaDePriodade(FilaDePrioridade *fila, int indice, EspacoNave *copia) {
    if(estaVaziaFilaDePrioridade(fila)) return 0;

    int i = 1;
    NoDePrioridades *aux = fila->inicio;

    while(aux != NULL && i < indice) {
        aux = aux->proximo;
        i++;
    }

    if(aux == NULL)
        return 0;

    if(copia == NULL)
        return 0;

    *copia = aux->nave;
    return 1;
}


/**
 * @brief Exclui um respectivo no da fila
 * 
 * @param fila Representa o ponteiro para a fila
 * @param prioridade Representa o a prioridade do item que se deseja excluir
 * @param cpy Representa uma ponteiro para onde os dados serão movidos
 * @return int retorna 1 se funcionar 0 caso contrario
 */
int excluirItemDaFilaDePrioridade(FilaDePrioridade *fila, int prioridade, EspacoNave *cpy) {
    
    /* Note que normalmente queremos obter o item de maior prioridade 
     * Contudo para manutenções na arvore essa função é bem util
     */

    if(estaVaziaFilaDePrioridade(fila)) return 0;

    NoDePrioridades *aux = fila->inicio;

    while(aux != NULL && aux->nave->prioridade != prioridade) {
        aux = aux->proximo; 
    }

    // Não encontrou a nave com prioridade x
    if(aux == NULL) return 0;

    if(fila->fim == fila->inicio) {
        // Só há uma nave na fila é ela e a que queremos remover
        if(prioridade == fila->inicio->nave->prioridade) {
            fila->fim = NULL;
            free(fila->inicio);
            fila->inicio = NULL;
            fila->tamanho--;
            return 1;
        }
        else {
            return 0;
        }
    }

    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;
    *cpy = aux->nave;

    if(aux == fila->inicio) fila->inicio = aux->proximo;
    if(aux == fila->fim) fila->fim = aux->anterior;

    free(aux);
    aux = NULL;
    fila->tamanho--;

    return 1;
}


/**
 * @brief Remove o elemento de maior prioridade da Fila
 * 
 * @param fila Representa a fila que faremos a operação
 * @return int 1 se funcionar 0 caso contrario
 */
int removerItemDaFilaDePrioridade(FilaDePrioridade *fila) {
    if(estaVaziaFilaDePrioridade(fila)) return 0;
    
    if(fila->fim == fila->inicio) {
        fila->fim = NULL;
        free(fila->inicio);
        fila->inicio = NULL;
        fila->tamanho--;
    }

    else {
        if(fila->inicio->proximo->nave->prioridade > fila->inicio->proximo->proximo->nave->prioridade) {
            fila->inicio = fila->inicio->proximo;
        }
        
        free(fila->inicio->anterior);
        fila->inicio->anterior = NULL;
        fila->tamanho--;
    }

    return 1;
}

int tamanhoDaFilaDePrioridade(FilaDePrioridade *fila) {
    return fila->tamanho;
}

int estaVaziaFilaDePrioridade(FilaDePrioridade *fila) {
    if(fila->inicio == NULL) return 1;
    return 0;
}

void deletarFilaDePrioridade(FilaDePrioridade *fila) {
    // Se há fila está vazia não fazemos nada
    if(!estaVaziaFilaDePrioridade(fila)) {

        // Caso contrário utilizamos dois ponteiros auxiliares para percorrer a fila removendo seus itens 
        while(fila->inicio->proximo != NULL) {
            fila->inicio = fila->inicio->proximo;        
            // Liberação do a nave e o item da memória
            deletarEspacoNave(&fila->inicio->anterior->nave);
            free(fila->inicio->anterior);
            fila->inicio->anterior = NULL;
        }

        // Aqui desreferenciamos o primeiro elemento
        fila->fim = NULL;
        fila->tamanho = 0;
        fila->inicio = NULL;
    }
}

void imprimirFilaDePrioridade(FilaDePrioridade *fila) {
    printf("Fila de Prioridades - %d Nave(s)\n", tamanhoDaFilaDePrioridade(fila));
    
    if(!estaVaziaFilaDePrioridade(fila)) {
        int i = 1;
        NoDePrioridades *auxiliar = fila->inicio;

        while(auxiliar != NULL) {
            printf("%5d. ", i);
            imprimirEspacoNave(auxiliar->nave);
            auxiliar = auxiliar->proximo;
            i++;
        }
    }
    else {
        printf("Nenhum item na fila\n");
    }
}
