#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "leitorDeArquivo.h"

#define percentage(percent, total) ((percent * 100) / total)

FilaInfo obterInformacaoDeRegistro(FILE *fp) {
    char controle = 0;
    FilaInfo info = (FilaInfo) calloc(1, sizeof(FilaInfo));

    info->numeroDeBytes = 0;
    info->numeroDeLinhas = 1;

    rewind(fp);
    
    while(controle != EOF) {
        controle = fgetc(fp);
        
        info->numeroDeBytes++;
        
        if(controle == '\n') {
            info->numeroDeLinhas++;
        }
    }

    info->tamanhoDasLinhas = (long *) calloc(info->numeroDeLinhas, sizeof(long));

    rewind(fp);

    for(int i = 0; i < info->numeroDeLinhas; i++) {
        controle = 0;
        while(controle != '\n' && controle != EOF) {
            controle = fgetc(fp);
            info->tamanhoDasLinhas[i]++;
        }
    }

    rewind(fp);
    
    return info;
}

void obterPosicaoDoCaractereAtual(FILE *fp, long *copiarLinha, long *copiarColuna) {
    long posicaoAtual = ftell(fp);
    long linha = 0;
    long coluna = 0;
    long soma = 0;
    
    rewind(fp);
    
    char caractereAtual = 0;

    for(long i = 0; i < posicaoAtual; i++) {
        caractereAtual = fgetc(fp);
        soma += 1;

        if(caractereAtual == '\n') {
            linha++;
            coluna = 0;
        }
        else
            coluna++;
    }
    printf("SOMA: %d\n", soma);
    if(copiarLinha != NULL) *copiarLinha = linha;
    if(copiarColuna != NULL) *copiarColuna = coluna;
}

void irParaOComecoDaLinha(FILE *fp, FilaInfo info) {
    long caractereAtual = ftell(fp);
    long inicioDaLinha = 0;
    long  linhaAtual;

    obterPosicaoDoCaractereAtual(fp, &linhaAtual, NULL);

    for(long i = 1; i < linhaAtual; i++) {
        inicioDaLinha += info->tamanhoDasLinhas[i - 1]; 
    }

    fseek(fp, inicioDaLinha, SEEK_SET);
}

void irParaOFimDaLinha(FILE *fp, FilaInfo info) {
    long caractereAtual = ftell(fp);
    long fimDaLinha = 0;

    for(int i = 0; i < info->numeroDeLinhas; i++) {
        if(fimDaLinha >= caractereAtual) {
            break;
        }
        
        fimDaLinha += info->tamanhoDasLinhas[i];
    }
    
    fseek(fp, fimDaLinha, SEEK_SET);
}

char * obterLinhaAtual(FILE *fp, FilaInfo info) {
    long posicaoAtual = ftell(fp);
    char *conteudoDaLinha;
    long tamanhoDaLinha = 0;
    long linha;

    obterPosicaoDoCaractereAtual(fp, &linha, NULL);
    tamanhoDaLinha = info->tamanhoDasLinhas[linha] + 1;

    irParaOComecoDaLinha(fp, info);
    
    conteudoDaLinha = (char *) calloc(tamanhoDaLinha, sizeof(char));
    
    for(long i = 0; i < tamanhoDaLinha; i++) {
        char caractere = fgetc(fp);
        if(caractere == '\n') {
            conteudoDaLinha[i] = '\0';
            break;
        } else {
            conteudoDaLinha[i] = caractere;
        }
    }

    fseek(fp, posicaoAtual, SEEK_SET);

    return conteudoDaLinha;
}

void deletarInfo(FilaInfo info) {
    free(info->tamanhoDasLinhas);
    info->tamanhoDasLinhas = NULL;
    free(info);
    info = NULL;
}

int obterTamanhoDaString(FILE *fp, FilaInfo info) {
    int aspa = 0;
    int iniciou = 0;
    char controle = 0;
    long inicioDaString;
    int tamanhoDaString = 1;
    long posicaoAtual = ftell(fp);

    while(controle != EOF && controle != '\n') {
        controle = fgetc(fp);

        if(controle == '\"') {
            aspa = !aspa;
            if(!iniciou) {
                iniciou = 1;
                inicioDaString = ftell(fp);
            }
            continue;
        } 

        if(aspa) {
            tamanhoDaString++;
        }
    }

    if(iniciou) 
        fseek(fp, inicioDaString, SEEK_SET);
    else
        fseek(fp, posicaoAtual, SEEK_SET);
    
    return tamanhoDaString;
}

int arquivoExiste(const char *caminho) {
    FILE *file = fopen(caminho, "r");

    if (file) {
        fclose(file);
        return 1; // Arquivo existe
    } else {
        return 0; // Arquivo não existe
    }
}

FILE* abrirResgistro() {
    FILE *file;

    if(arquivoExiste("filainfo.txt")) {
        file = fopen("filainfo.txt", "r");
    } else if(arquivoExiste("public\\filainfo.txt")) {
        file = fopen("public\\filainfo.txt", "r");
    } else if(arquivoExiste("public/filainfo.txt")) {
        file = fopen("public/filainfo.txt", "r");
    } else {
        printf("[ERROR] Arquivo de registro não encontrado\n");
        return NULL;
    }

    return file;
}

int obterDadosDoRegistro(FILE *fp, FilaDePrioridade *fila) {

    if(fila == NULL) return 0;
    
    rewind(fp);

    char *nome;
    char *planeta;
    char controle = 0;
    int naveJaFoiCriada = 0;
    int prioridade, idade, id, quantidade, tamanho;
    long posicaoAtual = 0;
    EspacoNave nave;
    Recurso recurso;
    Passageiro passageiro;
    FilaInfo filainfo = obterInformacaoDeRegistro(fp);

    while(controle != EOF) {
        controle = fgetc(fp);
        posicaoAtual = ftell(fp);
        
        switch (controle) {

        case 'n':
            // Caso já exista uma nave, ele salva anterior antes de criar a proxima

            if(naveJaFoiCriada) {
                if(adicionarItemAFilaDePrioridade(fila, nave)) {
                    printf("Espaçonave adcionada a fila -> ");
                    imprimirEspacoNave(nave);
                    printf("%d\n", fila->tamanho);
                }
                else {
                    printf("[FALHA] Ao adicionar nave '%03d' a fila '%p'\n", nave->prioridade, fila->inicio);
                }
            }
            
            fscanf(fp, "%d", &prioridade);
            nave = novaEspacoNave(prioridade);
            printf("Espaçonave criada -> ");
            imprimirEspacoNave(nave);
            naveJaFoiCriada = 1;
            break;
        
        case 'p':
            if(!naveJaFoiCriada) return 0;

            printf("%d",fscanf(fp, "%d, %d, \"%s\", \"%s\"", &id, &idade, nome, planeta));
            
            passageiro = novoPassageiro(id, idade, nome, planeta);
            
            if(!adicionarPassageiroAListaDePassageiros(nave->Passageiros, passageiro)) {
                printf("[FALHA] Ao adcionar passageiro '%d' à nave '%03d'\n", passageiro->id, nave->prioridade);
                free(passageiro);
                passageiro = NULL;
            }

            else {
                printf("Passageiro adcionado -> ");
                imprimirPassageiro(passageiro);
            }

            break;
        
        case 'r':
            if(!naveJaFoiCriada) return 0;

            fscanf(fp, "%d,", &quantidade);

            tamanho = obterTamanhoDaString(fp, filainfo);
            nome = (char *) calloc(tamanho, sizeof(char));

            fgets(nome, tamanho, fp);
            fgetc(fp);

            recurso = novoRecurso(nome, quantidade);

            if(!adicionarRecursoAListaDeRecursos(nave->Recursos, recurso)) {
                printf("[FALHA] Ao adcionar recurso '%s' à nave '%03d'\n", recurso->nome, nave->prioridade);
                free(recurso);
                recurso = NULL;
            }

            else {
                printf("Recurso adcionado -> ");
                imprimirRecurso(recurso);
            }

            break;
        
        case '#':
            irParaOFimDaLinha(fp, filainfo);
            break;
        
        default:
            if(!isspace(controle) && controle != EOF) {
                printf("[FALHA] filainfo.txt caractere desconhecido: '%c'\n", controle);
                return 0;
            }

            break;
        }
    }
    
    rewind(fp);
    deletarInfo(filainfo);
    return 1;
}

void carregarDadosDoRegistro(FilaDePrioridade *fila) {
    FILE *filainfo = abrirResgistro();

    if(!obterDadosDoRegistro(filainfo, fila)) {
        printf("[ERROR]: Ao carregar arquivo de registro\n");
    }

    fclose(filainfo);
}
