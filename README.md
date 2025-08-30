# Determinant Calculator

Este projeto implementa dois métodos numéricos para o cálculo do determinante de matrizes quadradas reais:

- **Expansão de Laplace**: método recursivo baseado na cofactoração da matriz.
- **Eliminação de Gauss**: método eficiente baseado na triangularização da matriz.

## Funcionamento do Programa

O programa realiza o cálculo de determinantes a partir de matrizes armazenadas em arquivos `.txt` localizados na pasta `matrices/`. Ele oferece os seguintes recursos:

- Escolha do tamanho da matriz: 3x3, 5x5, 8x8, 20x20 e 100x100.
- Seleção do método de cálculo (Laplace ou Gauss).
- Impressão do determinante com 5 casas decimais.
- Cálculo e exibição do tempo de execução.
- Detecção de erros como arquivos ausentes ou alocação de memória.

## Como Utilizar

1. Prepare arquivos `.txt` com os dados das matrizes e coloque-os na pasta `matrices/`.
2. Compile o programa:
   ```bash
   gcc -Wall main.c -o determinant
   ```
3. Execute o programa:
   ```bash
   ./determinant
   ```
4. Siga as instruções no terminal para selecionar o método e a matriz desejada.
5. O programa exibirá o resultado e perguntará se deseja continuar.

## Instalação e Execução

### Pré-requisitos

- Compilador C (ex: GCC)
- Ambiente configurado para compilação via terminal

### Passo a passo

1. Clone ou baixe este repositório.
2. Navegue até a pasta do projeto pelo terminal.
3. Compile com:
   ```bash
   gcc -Wall main.c -o determinant
   ```
4. Execute:
   ```bash
   ./determinant
   ```

## Autor

Alisson Silva
