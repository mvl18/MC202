#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"

int main(void) {
    
    int n_expressoes;
    char expressao[MAX];
    scanf("%d\n", &n_expressoes);  // Recebe o número de expressões que serão otimizadas

    for (int i = 0; i < n_expressoes; i++) {
        scanf("%s", expressao);  // Recebe a expressão pós-fixa

        p_no raiz = cria_arvore(expressao);
        imprimir_arvore(raiz, false, true); // Inicia com 'precisa_parenteses' como falso e 'eh_raiz' como verdadeiro
        printf("\n");

        p_no raiz_otimizada = otimiza_arvore(raiz);  // Otimiza a própria árvore, alterando as subárvores
        imprimir_arvore(raiz_otimizada, false, true); // Inicia com 'precisa_parenteses' como falso e 'eh_raiz' como verdadeiro
        printf("\n\n");
        
        libera_arvore(raiz);
    }
    
    return 0;
}
