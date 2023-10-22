#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dados.h"

Passageiro novoPassageiro(int id, int idade, char *nome, char *planeta) {
    Passageiro passageiro = (Passageiro) calloc(1, sizeof(struct Passageiro));

    passageiro->id = id;
    passageiro->idade = idade;
    passageiro->nome = nome;
    passageiro->planetaDeOrigem = planeta;

    return passageiro;
}

Recurso novoRecurso(char *nome, int quantidade) {
    Recurso recurso = (Recurso) calloc(1, sizeof(struct Recurso));

    recurso->nome = nome;
    recurso->quantidade = quantidade;

    return recurso;
}

int editarNomePassageiro(Passageiro passageiro, char *nome) {
    int tamanhoDoNome = strlen(nome) + 1;
    
    if(tamanhoDoNome > 255) tamanhoDoNome = 255;
    
    passageiro->nome = (char *) realloc(passageiro->nome, sizeof(char) * tamanhoDoNome);
    snprintf(passageiro->nome, tamanhoDoNome, "%s", nome);
}

int editarNomeRecurso(Recurso recurso, char *nome) {
    int tamanhoDoNome = strlen(nome) + 1;
    
    if(tamanhoDoNome > 255) tamanhoDoNome = 255;
    
    recurso->nome = (char *) realloc(recurso->nome, sizeof(char) * tamanhoDoNome);
    snprintf(recurso->nome, tamanhoDoNome, "%s", nome);
}

void excluirPassageiro(Passageiro passageiro) {
    free(passageiro->nome);
    passageiro->nome = NULL;
    free(passageiro);
    passageiro = NULL;
}

void excluirRecurso(Recurso recurso) {
    free(recurso->nome);
    recurso->nome = NULL;
    free(recurso);
    recurso = NULL;
}

void imprimirRecurso(Recurso recurso) {
    printf("(recurso) %s %d\n", recurso->nome, recurso->quantidade);
}

void imprimirPassageiro(Passageiro passageiro) {
    printf("(passageiro) %d %s %d %s\n", passageiro->id, passageiro->nome, passageiro->idade, passageiro->planetaDeOrigem);
}