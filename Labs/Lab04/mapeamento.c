#include <stdio.h>
#include <stdlib.h>

// Função para alocar uma matriz de inteiros com tamanho dado
int **cria_matriz(int tamanho);

// Função para preencher a matriz com entradas fornecidas pelo usuário
void entradas_matriz(int **matriz, int tamanho);

// Função para modificar a matriz antes de analisar o quadrante que necessita de mais atenção
void modifica_matriz(int **matriz, int inicio[], int modifica[]);

// Função para analisar a matriz e determinar qual quadrante necessita de mais atenção
void analisa_matriz(int **matriz, int tamanho, int situacao, int inicio[]);

// Função para imprimir uma parte da matriz, dependendo da situação
void imprime_matriz(int **matriz, int tamanho, int situacao, int inicio[]);

// Função para liberar a memória alocada para a matriz
void libera_matriz(int **matriz, int tamanho);


int main(void)
{   
    // "tamanho" recebe o tamanho (ordem) da matriz
    // "verifica" analisa se haverá modificação na matriz ou não
    // "modifica" é um vetor que recebe a linha e coluna a ser alterada e o novo valor
    // "inicio" é um vetor para a posição do primeiro elemento do quadrante analisado
    int tamanho, **matriz, verifica, modifica[3], inicio[2] = {0, 0};

    scanf("%d", &tamanho);
    matriz = cria_matriz(tamanho);
    entradas_matriz(matriz, tamanho);

    printf("Quadras:\n");
    imprime_matriz(matriz, tamanho, 0, inicio);

    for (int i = 1; i < tamanho; i++) {
        // o "i" servirá para saber em qual ordem a matriz será reduzida

        if (i != 1) {
            scanf("%d", &verifica);

            if (verifica == 0) {   // o programa termina
                libera_matriz(matriz, tamanho);
                return 0;
            }
            else {   // elemento da submatriz será alterado
                for (int j = 0; j < 3; j++)
                    scanf("%d", &modifica[j]);
                modifica_matriz(matriz, inicio, modifica);
            }
        }

        analisa_matriz(matriz, tamanho, i, inicio);
        printf("Conjuntos que precisam de atenção:\n");
        imprime_matriz(matriz, tamanho, i, inicio);     
    }

    libera_matriz(matriz, tamanho);
    
    return 0;
}

int **cria_matriz(int tamanho)
{
    int **matriz;

    matriz = malloc(tamanho * sizeof(int *));
    for (int i = 0; i < tamanho; i++)
        matriz[i] = malloc(tamanho * sizeof(int));
    
    return matriz;
}

void entradas_matriz(int **matriz, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        for (int j = 0; j < tamanho; j++)
            scanf("%d", &matriz[i][j]);
}

void modifica_matriz(int **matriz, int inicio[], int modifica[])
{
    matriz[modifica[0] + inicio[0]][modifica[1] + inicio[1]] = modifica[2]; 
}

void analisa_matriz(int **matriz, int tamanho, int situacao, int inicio[])
{
    int soma = 0, linha, coluna, maior = 0, a, b;

    /* com este loop for percorreremos os 4 quadrantes da matriz, com as variáveis
    linha e coluna recebendo os valore (0,0), (0,1), (1,0) ou (1,1).
    As variáveis a e b receberão o valor final que irá acrescer à posição do primeiro
    elemento da submatriz*/
    for (int m = 0; m <= 3; m++) {
        linha = m / 2;
        coluna = m % 2;
        for (int i = 0; i < tamanho - situacao; i++)
            for (int j = 0; j < tamanho - situacao; j++)
                soma += matriz[i + inicio[0] + linha][j + inicio[1] + coluna];

        if (maior < soma || m == 0) {
            maior = soma;
            a = linha;
            b = coluna;
        }
        soma = 0;
    }

    inicio[0] += a;
    inicio[1] += b;
}

void imprime_matriz(int **matriz, int tamanho, int situacao, int inicio[])
{
    for (int i = 0; i < tamanho - situacao; i++) {
        for (int j = 0; j < tamanho - situacao; j++)
            printf("%d\t", matriz[i + inicio[0]][j + inicio[1]]);
        printf("\n");
    }

    printf("\n");
} 

void libera_matriz(int **matriz, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
        free(matriz[i]);
    
    free(matriz);
}
