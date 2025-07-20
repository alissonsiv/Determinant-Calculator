#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprimir_cabecalho() {
    printf("\n----------------------------------\n");
    printf("---- CALCULADORA DE DETERMINANTES ----\n");
    printf("----------------------------------\n");
}

void imprimir_resultado(double det, double tempo, int n) {
    printf("------------------------------------\n");
    printf("------------- RESULTADO ------------\n");
    printf("------------------------------------\n");

    printf("Matriz: %dx%d\n", n, n);
    printf("Determinante: %.5lf\n", det);
    printf("Tempo de execucao: %.5lf segundos\n", tempo);

    printf("----------------------------------\n");
}

void exibir_opcoes() {
    printf("Escolha o tamanho da matriz: \n");
    printf("1 - Matriz 3x3\n");
    printf("2 - Matriz 5x5\n");
    printf("3 - Matriz 8x8\n");
    printf("4 - Matriz 20x20\n");
    printf("5 - Matriz 100x100\n");
}

int** obter_matriz(int* n) {
    int opcao;
    FILE* arquivo = NULL;
    int **matriz = NULL;

    exibir_opcoes();
    scanf("%d", &opcao);

    switch(opcao) {
        case 1: arquivo = fopen("matrices/matrix_3x3.txt", "r"); *n = 3; break;
        case 2: arquivo = fopen("matrices/matrix_5x5.txt", "r"); *n = 5; break;
        case 3: arquivo = fopen("matrices/matrix_8x8.txt", "r"); *n = 8; break;
        case 4: arquivo = fopen("matrices/matrix_20x20.txt", "r"); *n = 20; break;
        case 5: arquivo = fopen("matrices/matrix_100x100.txt", "r"); *n = 100; break;
        default:
            printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
            return NULL;
    }

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    matriz = (int **) malloc(*n * sizeof(int*));
    if (matriz == NULL) {
        printf("Erro de alocacao de memória.\n");
        fclose(arquivo);
        return NULL;
    }
    for (int i = 0; i < *n; i++) {
        matriz[i] = (int *) malloc(*n * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro de alocacao de memória.\n");

            for (int k = 0; k < i; k++) free(matriz[k]);
            free(matriz);
            fclose(arquivo);
            return NULL;
        }
    }

    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(arquivo, "%d", &matriz[i][j]) != 1) {
                printf("Erro na leitura do arquivo.\n");

                for (int k = 0; k < *n; k++) free(matriz[k]);
                free(matriz);
                fclose(arquivo);
                return NULL;
            }
        }
    }

    fclose(arquivo);
    return matriz;
}

double determinante_laplace(int** matriz, int n) {
    if (n == 1) {
        return matriz[0][0];
    }
    if (n == 2) {
        return matriz[0][0] * matriz[1][1] - matriz[0][1] * matriz[1][0];
    }

    double det = 0.0;

    for (int j = 0; j < n; j++) {
        int** submatriz = (int**) malloc((n-1) * sizeof(int*));
        for (int i = 0; i < (n-1); i++) {
            submatriz[i] = (int*) malloc((n-1) * sizeof(int));
        }

        for (int k = 1; k < n; k++) {
            int col_index = 0;
            for (int l = 0; l < n; l++) {
                if (l != j) {
                    submatriz[k-1][col_index] = matriz[k][l];
                    col_index++;
                }
            }
        }

        double subdet = determinante_laplace(submatriz, n - 1);
        det += matriz[0][j] * subdet * ((j % 2 == 0) ? 1 : -1);

        for (int i = 0; i < (n-1); i++) {
            free(submatriz[i]);
        }
        free(submatriz);
    }

    return det;
}

double eliminacao_gauss(int** matriz, int n) {
    double temp;
    int sinal = 1;
    double det = 1.0;

    double **mat = (double **)malloc(n * sizeof(double *));
    if (!mat) {
        printf("Erro de alocacao de memória.\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)malloc(n * sizeof(double));
        if (!mat[i]) {
            printf("Erro de alocacao de memória.\n");
            for (int k = 0; k < i; k++) free(mat[k]);
            free(mat);
            return 0;
        }
        for (int j = 0; j < n; j++) {
            mat[i][j] = matriz[i][j]; 
        }
    }

    for (int i = 0; i < n; i++) {
        if (mat[i][i] == 0) {
            int troca = -1;
            for (int j = i + 1; j < n; j++) {
                if (mat[j][i] != 0) {
                    troca = j;
                    break;
                }
            }

            if (troca == -1) {
                det = 0;
                break;
            } else {
                for (int k = 0; k < n; k++) {
                    temp = mat[i][k];
                    mat[i][k] = mat[troca][k];
                    mat[troca][k] = temp;
                }
                sinal *= -1;
            }
        }

        if (mat[i][i] == 0) {
            det = 0; 
            break;
        }

        for (int j = i + 1; j < n; j++) {
            double fator = mat[j][i] / mat[i][i];
            for (int k = i; k < n; k++) {
                mat[j][k] -= fator * mat[i][k];
            }
        }
    }

    if (det != 0) {
        for (int i = 0; i < n; i++) {
            det *= mat[i][i];
        }
        det *= sinal;
    }

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);

    return det;
}

int main() {
    int opcao = 0, n = 0;
    int **matriz = NULL;
    int continuar = 0;

    while(opcao != 3) {
        imprimir_cabecalho();
        printf("Escolha uma opcao: \n");
        printf("1 - Calcular com expansao de Laplace\n");
        printf("2 - Calcular com eliminacao de Gauss\n");
        printf("3 - Sair\n");
        printf("\nDigite sua opcao: ");
        
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            printf("\nVoce escolheu: Calcular com expansao de Laplace.\n");

            matriz = obter_matriz(&n);

            if (matriz != NULL) {
                printf("Calculando Determinante...\n\n");
                
                clock_t inicio = clock();
                double resultado = determinante_laplace(matriz, n);
                clock_t fim = clock();
                
                double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                imprimir_resultado(resultado, tempo, n);
                
                for (int i = 0; i < n; i++) {
                    free(matriz[i]);
                }
                free(matriz);
            }
        } else if (opcao == 2) {
            printf("\nVoce escolheu: Calcular com eliminacao de Gauss.\n");

            matriz = obter_matriz(&n);
            
            if (matriz != NULL) {
                printf("Calculando Determinante...\n\n");
                
                clock_t inicio = clock();
                double resultado = eliminacao_gauss(matriz, n);
                clock_t fim = clock();
                
                double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                imprimir_resultado(resultado, tempo, n);
                
                for (int i = 0; i < n; i++) {
                    free(matriz[i]);
                }
                free(matriz);
            }
        } else if (opcao == 3){
            break;
        } else {
            printf("\nOpcao invalida. Por favor, escolha uma opcao valida.\n");
            return 1;
        }
        
        printf("Deseja continuar?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        
        scanf("%d", &continuar);
        
        if (continuar == 2){
            break;
        } else if (continuar != 1){
            printf("Erro: Opcao Invalida\n");
            return 1;
        }
    }

    return 0;
}
