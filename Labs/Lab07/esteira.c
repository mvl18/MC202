#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esteira.h"

p_fila criar_esteira(int tam_esteira)
{
    p_fila esteira = malloc(sizeof(struct fila));
    esteira->vetor = malloc(tam_esteira * sizeof(p_peca));  

    esteira->ini = 0;
    esteira->fim = 0;
    esteira->tamanho = tam_esteira;
    esteira->usado = 0;

    return esteira;
}

p_fila adiciona_peca_esteira(p_fila esteira, p_peca torno) {
    esteira->vetor[esteira->fim] = torno;
    esteira->fim = (esteira->fim + 1) % esteira->tamanho;
    esteira->usado ++;

    return esteira;
}

p_peca remove_peca_esteira(p_fila esteira) {
    p_peca torno = esteira->vetor[esteira->ini];
    esteira->ini = (esteira->ini + 1) % esteira->tamanho;
    esteira->usado --;
    
    return torno;
}

void destruir_esteira(p_fila esteira)
{
    free(esteira->vetor);  // Libera a memória alocada para o vetor
    free(esteira);  // Libera a memória alocada para a estrutura da fila
}
