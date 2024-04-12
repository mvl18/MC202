#include <stdio.h>
#define PALAVRAMAX 21
#define MATRIXMAX 301

void analise(int n_linha, int n_coluna, char matriz[][MATRIXMAX], char palavra[PALAVRAMAX]);
int busca(int letra, int vertical, int horizontal, int n_linha, int linha, int n_coluna, int coluna, char matriz[][MATRIXMAX], char palavra[PALAVRAMAX]);

int main(void)
{   //função que recebe o tamanho da matriz, o número de palavras, os caracteres da matriz e as palavras.
    //cada palavra é analisada imediatamente ao ser recebida, sem ocupar memória.
    int n_linha, n_coluna, n_palavras;
    char matriz[MATRIXMAX][MATRIXMAX], palavra[PALAVRAMAX];
    scanf("%d %d %d", &n_linha, &n_coluna, &n_palavras);

    for (int i = 0; i < n_linha; i++)
        for (int j = 0; j < n_coluna; j++)
            scanf(" %c", &matriz[i][j]);

    for (int m = 0; m < n_palavras; m++)
    {
        scanf("%s", palavra);
        analise(n_linha, n_coluna, matriz, palavra);
    }

    return 0;
}

void analise(int n_linha, int n_coluna, char matriz[][MATRIXMAX], char palavra[PALAVRAMAX])
{   //função que analisa onde está a primeira letra da palavra na matriz de caracteres.
    int verifica = 0;

    for (int i = 0; !verifica && i < n_linha; i++)
        for (int j = 0; !verifica && j < n_coluna; j++)
            if (palavra[0] == matriz[i][j])
            {   //ao encontrar a letra na matriz é chamada a função busca para cada um dos sentidos para analisar a segunda letra da palavra
                //o segundo e o terceiro elementos da função busca passam o sentido da busca (linha, coluna)
                verifica = busca(1, 0, 1, n_linha, i, n_coluna, j, matriz, palavra); //busca para direita
                if (!verifica)
                    verifica = busca(1, 0, -1, n_linha, i, n_coluna, j, matriz, palavra);  //busca para esquerda
                if (!verifica)
                    verifica = busca(1, 1, 0, n_linha, i, n_coluna, j, matriz, palavra);  //busca para baixo
                if (!verifica)
                    verifica = busca(1, -1, 0, n_linha, i, n_coluna, j, matriz, palavra);  //busca para cima
            }

    if (verifica)
        printf("A palavra %s está no texto!\n", palavra);
    else
        printf("A palavra %s não está no texto!\n", palavra);
}

int busca(int letra, int vertical, int horizontal, int n_linha, int linha, int n_coluna, int coluna, char matriz[][MATRIXMAX], char palavra[PALAVRAMAX])
{   //indica que a palavra foi encontrada e retorna "1" para a variável "verifica" da função busca
    if (palavra[letra] == '\0')
        return 1;

    //após verificar os limites da matriz, verifica se a próxima letra está na matriz. 
    //caso esteja, entramos em uma recursividade, adicionando "1" na "letra" até que a última letra da palavra seja encontrada.
    if (linha + vertical >= 0 && linha + vertical < n_linha && coluna + horizontal >= 0 && coluna + horizontal < n_coluna) {
        if (palavra[letra] == matriz[linha + vertical][coluna + horizontal])
            return busca(letra + 1, vertical, horizontal, n_linha, linha + vertical, n_coluna, coluna + horizontal, matriz, palavra);        
    }

    return 0; 
}
