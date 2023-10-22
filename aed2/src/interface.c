#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "interface.h"

int obterUmaOpcao(int range) {
    int opcao = -1;
    
    scanf("%d", &opcao);
    fflush(stdin);

    while(opcao < 0 || opcao > range) {
        printf("[ERROR]: Opção inválida\n");
        scanf("%d", &opcao);
        fflush(stdin);
    }

    return opcao;
}

int obterUmInteiro(int minimo, int maximo) {
    int inteiro = minimo - 1;
    
    scanf("%d", &inteiro);
    fflush(stdin);

    while(inteiro < minimo || inteiro > maximo) {
        printf("[ERROR]: Opção inválida: O valor deve ser um inteiro entre %d e %d\n", minimo, maximo);
        scanf("%d", &inteiro);
        fflush(stdin);
    }

    return inteiro;
}

char * obterUmString(int minimo, int maximo) {
    int input_size = 0; 
    char * string = (char *) calloc(maximo + 1, sizeof(char));

    if (string == NULL) {
        printf("[FATAL] Alocação da string falhou\n");
        exit(1);
    }

    fgets(string, maximo, stdin);
    fflush(stdin);
    
    input_size = snprintf(NULL, 0, "%s", string);

    while(input_size < minimo && input_size > maximo) {
        printf("[ERROR]: Opção inválida: O valor deve ter um tamanho entre %d e %d\n", minimo, maximo);
        fgets(string, sizeof(maximo), stdin);
        fflush(stdin);
    }

    for (int i = 0; i < maximo; i++) {
        if(string[i] == '\n') {
            string[i] = '\0';
        }
    }

    return string;
}

void imprimirMenuPrincipal() {
    printf("Sistema de controle de Naves\n");
    printf("------------------------------\n");
    printf("1 - Autorizar passagem de Nave\n");
    printf("2 - Adcionar Nave a fila\n");
    printf("3 - Remover Nave da fila\n");
    printf("4 - Verificar prioridades\n");
    printf("5 - Mostrar fila\n");
    printf("0 - Sair\n");
}

void imprimirMenuDeNave() {
    printf("Criação de Naves\n");
    printf("Escolha uma opção abaixo:\n");
    printf("1 - Ver Prioridade\n");
    printf("2 - Ver Passageiros\n");
    printf("3 - Ver Recursos\n");
    printf("4 - Adcionar Prioridade\n");
    printf("5 - Adcionar Passageiro\n");
    printf("6 - Adcionar Recurso\n");
    printf("7 - Remover Passageiro\n");
    printf("8 - Remover Recurso\n");
    printf("9 - Confirmar \n");
    printf("0 - Cancelar\n");
}

void iniciarMenuCriacaoPassageiro(EspacoNave nave) {
    int id, idade;
    char *nome, *planeta;

    printf("Criação de Passageiros\n");
    
    printf("Digite o id: ");
    id = obterUmInteiro(0, INT_MAX);

    printf("Digite o nome: ");
    nome = obterUmString(3, 100);

    printf("Digite a idade: ");
    idade = obterUmInteiro(0, 120);

    printf("Digite o planeta de origem: ");
    planeta = obterUmString(3, 100);

    if(adcionarPassageiro(nave, id, idade, nome, planeta)) {
        Passageiro ultimo;
        if(obterPassageiroDaListaDePassageiros(nave->Passageiros, tamanhoDaListaDePassageiros(nave->Passageiros) - 1, &ultimo)) {
            printf("\n\t");
            imprimirPassageiro(ultimo);
        }
        else
            printf("[ERROR]: Um erro ocorreu ao tentar imprimir o último Passageiro\n");
    }
    else {
        printf("[ERROR]: Um erro ocorreu durante a inserção do Passageiro e a operação foi cancelada\n");
    }
}

void iniciarMenuCriacaoRecurso(EspacoNave nave) {
    char *nome;
    int quantidade;

    printf("Criação de Recursos\n");
    
    printf("Digite o nome: ");
    nome = obterUmString(3, 100);
    
    printf("Digite a quantidade: ");
    quantidade = obterUmInteiro(0, INT_MAX);

    if(adcionarRecurso(nave, nome, quantidade)) {
        Recurso ultimo;
        if(obterRecursoDaListaDeRecursos(nave->Recursos, tamanhoDeListaDeRecursos(nave->Recursos) - 1, &ultimo)) {
            printf("\n\t");
            imprimirRecurso(ultimo);
        }
        else
            printf("[ERROR]: Um erro ocorreu ao tentar imprimir o último Recurso\n");
    }
    else {
        printf("[ERROR]: Um erro ocorreu durante a inserção do Recurso e a operação foi cancelada\n");
    }
}

void iniciarMenuAdicaoDePrioridade(EspacoNave nave) {
    int prioridade;
    printf("Mudança de Prioridade\n");
    
    printf("Digite a nova prioridade: ");
    prioridade = obterUmInteiro(INT_MIN, INT_MAX);
    printf("\n");

    nave->prioridade = prioridade;

    printf("A prioridade da nave foi alterada\n");
}

void iniciarMenuRemocaoPassageiro(EspacoNave nave) {
    int indice;
    printf("Remoção de Passageiros\n");
    
    printf("Digite o indice: ");
    indice = obterUmInteiro(0, INT_MAX);
    printf("\n");

    if(removerPassageiro(nave, indice)) {
        printf("Um Passageiro foi removido nave:\n");
        imprimirEspacoNave(nave);
    }
    else {
        printf("[ERROR]: Um erro ocorreu durante a remoção do Passageiro e a operação foi cancelada\n");
    }
}

void iniciarMenuRemocaoRecurso(EspacoNave nave) {
    int indice;
    printf("Remocao de Recurso\n");
    
    printf("Digite o indice: ");
    indice = obterUmInteiro(0, INT_MAX);
    printf("\n");

    if(removerRecurso(nave, indice)) {
        printf("Um Recurso foi removido nave:\n");
        imprimirEspacoNave(nave);
    }
    else {
        printf("[ERROR]: Um erro ocorreu durante a remoção do Recurso e a operação foi cancelada\n");
    }
}

void iniciarMenuAdicaoNave(FilaDePrioridade *fila, EspacoNave nave) {
    if(adicionarItemAFilaDePrioridade(fila, nave)) {
        imprimirMenuDeNave(nave);

        printf("Uma nave entrou na lista de prioridades:\n");
        imprimirEspacoNave(nave);

        printf("Passageiros\n");
        if(estaVaziaListaDePassageiros(nave->Passageiros)) printf("Nenhum\n");
        else imprimirPassageirosDeEspacoNave(nave);

        printf("Recursos\n");
        if(estaVaziaListaDeRecursos(nave->Recursos)) printf("Nenhum\n");
        else imprimirRecursosEspacoNave(nave);
       
    } else {
        printf("[ERROR]: Ao adcionar nave a fila e a operação foi cancelada\n");
        deletarEspacoNave(&nave);
    }
}

void iniciarMenuRemocaoNave(FilaDePrioridade *fila) {
    if(estaVaziaFilaDePrioridade(fila)) {
         printf("Não a naves na fila\n");
    }
    else {
        int prioridade;
        EspacoNave nave;

        printf("Remocao de Nave\n");
        
        printf("Digite o prioridade: ");
        prioridade = obterUmInteiro(0, INT_MAX);
        printf("\n");

        if(excluirItemDaFilaDePrioridade(fila, prioridade, &nave)) {
            printf("Uma nave foi removida com sucesso da fila de prioridades");
            printf("Detalhes da nave: ");
            imprimirEspacoNave(nave);
            deletarEspacoNave(&nave);
        }
        else {
            printf("[ERROR]: Um erro ocorreu durante a remoção da Nave\n");
        }
    }
}

void iniciarMenuDePassagem(FilaDePrioridade *fila) {
    if(estaVaziaFilaDePrioridade(fila)) {
        printf("Não a naves na fila\n");
    }
    else {

        EspacoNave *cpy;

        if(obterItemDaFilaDePrioridade(fila, cpy) && removerItemDaFilaDePrioridade(fila)) {
            printf("Nave concluiu a passagem: ");
            imprimirEspacoNave(*cpy);
            free(cpy);
            cpy = NULL;
        }
        else printf("[ERROR]: Nave não conseguiu concluir a passagem corretamente\n");
    }
}

void iniciarVerificarLista(FilaDePrioridade *fila) {
    printf("Verificando prioridades\n");
    EspacoNave aux;
    int tamanho = tamanhoDaFilaDePrioridade(fila);
    int errados = 0;
    int indices[tamanho]; 

    for(int i = 0; i < tamanho; i++) {
        obterIndexDaFilaDePriodade(fila, i, &aux);
        
        if(0 > aux->prioridade) {
            indices[errados] = aux->prioridade;
            errados++;
        }
    }

    if(errados > 0) {
        printf("Foram encontrados dados %d errados\n", errados);

        for(int i = 0; i < errados; i++) {
            printf("removido: %s\n", excluirItemDaFilaDePrioridade(fila, indices[i], &aux) ? "true" : "false");
            printf("Digite uma nova prioridade: ");
            aux->prioridade = obterUmInteiro(0, INT_MAX);
            adicionarItemAFilaDePrioridade(fila, aux);
        }
    }

    else {
       printf("Nada foi encontrado\n");
    }
}

void syspause() {
    printf("Presione a tecla Enter para continuar ");
    getchar();
    printf("\n");
}

void iniciarMenuDeNave(FilaDePrioridade *fila) {
    int opcao;
    int continuar = 1;
    EspacoNave nave = novaEspacoNave(0);

    while(continuar) {
        imprimirMenuDeNave();
        opcao = obterUmaOpcao(9);

        switch (opcao) {

        case 1:
            imprimirEspacoNave(nave);
            break;
        
        case 2:
            if(estaVaziaListaDePassageiros(nave->Passageiros)) printf("A nave não apresenta Passageiros\n");
            else imprimirPassageirosDeEspacoNave(nave);
            break;

        case 3:
            if(estaVaziaListaDeRecursos(nave->Recursos)) printf("A nave não apresenta Recursos\n");
            else imprimirRecursosEspacoNave(nave);
            break;
        
        case 4:
            iniciarMenuAdicaoDePrioridade(nave);
            break;
                
        case 5:
            iniciarMenuCriacaoPassageiro(nave);
            break;
        
        case 6:
            iniciarMenuCriacaoRecurso(nave);
            break;

        case 7:
            iniciarMenuRemocaoPassageiro(nave);
            break;
                
        case 8:
            iniciarMenuRemocaoRecurso(nave);
            break;
        
        case 9:
            continuar = 0;
            iniciarMenuAdicaoNave(fila, nave);
            break;
        
        case 0:
            continuar = 0;
            deletarEspacoNave(&nave);
            printf("Criação Cancelada\n");
            break;

        default:
            opcao = -1;
            printf("[ERROR]: Opção inválida\n");
            break;
        }

        printf("\n");

        if(continuar)
            syspause();
    }
}

void iniciarMenuPrincipal(FilaDePrioridade *fila) {
    int opcao;
    int continuar = 1;

    while(continuar) {
        imprimirMenuPrincipal();
        opcao = obterUmaOpcao(5);

        switch (opcao) {

        case 0:
            continuar = 0;
            break;

        case 1:
            iniciarMenuDePassagem(fila);
            break;
        
        case 2:
            iniciarMenuDeNave(fila);
            break;

        case 3:
            iniciarMenuRemocaoNave(fila);
            break;
        
        case 4:
            iniciarVerificarLista(fila);
            break;
        
        case 5:
            imprimirFilaDePrioridade(fila);
            break;

        default:
            opcao = -1;
            printf("[ERROR]: Opção inválida\n");
            break;
        }

        if(continuar)
            syspause();
    }
}
