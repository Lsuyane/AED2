#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#include "interface.h"
#include "leitorDeArquivo.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    setlocale(LC_ALL, "portuguese");

    FilaDePrioridade *filaDeNaves = novaFilaDePrioridade();
    
    // carregarDadosDoRegistro(filaDeNaves);
    
    iniciarMenuPrincipal(filaDeNaves);

    deletarFilaDePrioridade(filaDeNaves);
    printf("Desligando do sitema\n");

    return 0;
}
