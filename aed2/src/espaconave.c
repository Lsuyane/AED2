#include <stdio.h>
#include <stdlib.h>
#include "espaconave.h"

EspacoNave novaEspacoNave(int prioridade) {
    EspacoNave nave = (EspacoNave) calloc(1, sizeof(struct EspacoNave));
    nave->Passageiros = novaListaDePassageiros();
    nave->Recursos = novaListaDeRecursos();
    nave->prioridade = prioridade;

  return nave;
}

int adcionarPassageiro(EspacoNave nave, int id, int idade, char* nome, char* planeta) {
    if(nave == NULL) return 0;
    
    Passageiro passageiro = novoPassageiro(id, idade, nome, planeta);
    return adicionarPassageiroAListaDePassageiros(nave->Passageiros, passageiro);
}

int adcionarRecurso(EspacoNave nave, char* nome, int quantidade) {
    if(nave == NULL) return 0;
    
    Recurso recurso = novoRecurso(nome, quantidade);
    return adicionarRecursoAListaDeRecursos(nave->Recursos, recurso);
}

int removerPassageiro(EspacoNave nave, int indice) {
    if(nave == NULL) return 0;

    return removerPassageiroAListaDePassageiros(nave->Passageiros, indice);
}

int removerRecurso(EspacoNave nave, int indice) {
    if(nave == NULL) return 0;

    return removerRecursoAListaDeRecursos(nave->Recursos, indice);
}

void esvaziarEspacoNave(EspacoNave nave) {
    limparListaDePassageiros(nave->Passageiros);
    limparListaDeRecursos(nave->Recursos);
}

void deletarEspacoNave(EspacoNave *nave) {
    deletarListaDePassageiros(&(*nave)->Passageiros);
    deletarListaDeRecursos(&(*nave)->Recursos);
    free(*nave);
    *nave = NULL;
}

void imprimirEspacoNave(EspacoNave nave) {
    int numeroDePassageiros = tamanhoDaListaDePassageiros(nave->Passageiros);
    int numeroDeRecursos = tamanhoDeListaDeRecursos(nave->Recursos);
    Recurso *copia = (Recurso *) malloc(sizeof(Recurso));
    int peso = 0;

    for(int i = 0; i < numeroDeRecursos; i++) {
        if(obterRecursoDaListaDeRecursos(nave->Recursos, i, copia))
            peso += (*copia)->quantidade;
    }

    printf("(espaçonave) prioridade: [%03d], lotação: %02d passageiro(s), recursos: %d kg\n", 
            nave->prioridade, numeroDePassageiros, peso);

    free(copia);
    copia = NULL;

}

void imprimirPassageirosDeEspacoNave(EspacoNave nave) {
    int numeroDePassageiros = tamanhoDaListaDePassageiros(nave->Passageiros);
    Passageiro *copia = (Passageiro *) malloc(sizeof(Passageiro));


    for(int i = 0; i < numeroDePassageiros; i++) {
        if(obterPassageiroDaListaDePassageiros(nave->Passageiros, i, copia)) {
            printf("\t%3d. ", i+1);
            imprimirPassageiro(*copia);
        }
        else {
            printf("\t[ERRO] (passageiro) falha ao obertar dados do %d° passageiro\n", i);
        }
    }

    free(copia);
    copia = NULL;
}

void imprimirRecursosEspacoNave(EspacoNave nave) {
    int numeroDeRecursos = tamanhoDeListaDeRecursos(nave->Recursos);
    Recurso *copia = (Recurso *) malloc(sizeof(Recurso));

    for(int i = 0; i < numeroDeRecursos; i++) {
        if(obterRecursoDaListaDeRecursos(nave->Recursos, i, copia)) {
            printf("\t%3d. ", i+1);
            imprimirRecurso(*copia);
        }
        else {
            printf("[ERRO] (recurso) falha ao obertar dados do %d° recurso\n", i);
        }
    }

    free(copia);
    copia = NULL;
}