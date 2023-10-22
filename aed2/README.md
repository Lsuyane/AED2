# Projeto AED2

## Como compilar

### Requisitos para compilação

Certifique-se de ter instalado o gcc ou outro compilador com suporte da linguagem c em sua versão c11, e do make na versão 4.3, juntamente do cmake em sua versão 3.20.

- gcc
- make
- cmake

### Compilação Manual

Para a compilação manual basta chamar o cmake usando o comando `cmake` para gerar o makefile de compilação com a flag `-S <diretorio do projeto>` que indica qual o diretorio de trabalho e seguido da flag `-B <diretorio de build>` indicando o diretorio de saida de compilação. Em seguida basta compilar usando o `make` juntamente da flag `-C <diretorio do makefile>` que indica o diretorio do makefile. Por fim basta invocar o executavel do programa.

```sh
cmake -S . -B build
make -C build
build/program
```

### Compilação com IDE

Basta importa o projeto na ide e compilar normalmente.