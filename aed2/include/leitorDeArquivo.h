#ifndef AED2_LEITOR_DE_ARQUICO_H
#define AED2_LEITOR_DE_ARQUICO_H

#include <stdio.h>
#include "filaDePrioridades.h"
/// @brief Estrutura para armazenar numero de linhas do arquivo
struct FilaInfo {
    int numeroDeBytes;
    int numeroDeLinhas;
    long *tamanhoDasLinhas;
};

typedef struct FilaInfo *FilaInfo;

/**
 * @brief Verifica se o arquivo de configuração existe
 * 
 * @param caminho Representa o caminho do arquivo
 * @return int 1 se existir 0 caso contrario
 */
int arquivoExiste(const char *caminho);

/**
 * @brief Abreo arquivo de configuração
 * 
 * @return FILE* o arquivo aberto no modo read
 */
FILE* abrirResgistro();

/**
 * @brief Tenta extrair os dados do registo
 * 
 * @param fila Representa onde os dados serão adcionados
 */
void carregarDadosDoRegistro(FilaDePrioridade *fila);

#endif // AED2_LEITOR_DE_ARQUICO_H