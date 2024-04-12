#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvore.h"


p_no criar_no(char dado) {
    p_no novo = (p_no)malloc(sizeof(struct no));
    novo->dado = dado;
    novo->esquerda = novo->direita = NULL;
    return novo;
}


bool eh_operando(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


bool eh_numero(char c) {
    return (c >= '0' && c <= '9');
}


p_no cria_arvore(char expressao[]) {
    p_no pilha[TAM_PILHA]; // Pilha para construir a árvore, armazenando as subárvores esquerda e direita de um novo operador
    int topo = -1;  // Indica que a pilha está vazia

    for (int i = 0; expressao[i]; i++) {
        p_no novo = criar_no(expressao[i]);  // Cria o nó para o caractere inserido

        if (eh_operando(expressao[i])) {  // Se for um operando é adicionado na pilha, para esperar o operador
            pilha[++topo] = novo;
        } 
        else {  // Se for um operador, pego os dois nós da pilha e 'ligo' ao pai, que é o operador
            p_no operando_dir = pilha[topo--];
            p_no operando_esq = pilha[topo--];

            novo->esquerda = operando_esq;
            novo->direita = operando_dir;

            // Adiciona o novo nó à pilha
            pilha[++topo] = novo;
        }
    }

    // Quando os caracteres da expressão terminam, o topo da pilha contém a raiz da árvore
    return pilha[topo];
}


p_no otimiza_arvore(p_no raiz) {
    if (raiz) {
        // Recursivamente otimiza as subárvores esquerda e direita
        raiz->esquerda = otimiza_arvore(raiz->esquerda);
        raiz->direita = otimiza_arvore(raiz->direita);

        // Verifica as regras de otimização e atualiza o nó atual, se necessário
        // Regra para o operador 'OU'
        if (raiz->dado == '|') {
            if (raiz->esquerda->dado == 'T' || raiz->direita->dado == 'T') {
                raiz->dado = 'T';
            } 
            else if (raiz->esquerda->dado == 'F' && raiz->direita->dado == 'F') {
                raiz->dado = 'F';
            }
        } 
        
        // Regra para o operador 'E'
        else if (raiz->dado == '&') {
            if (raiz->esquerda->dado == 'F' || raiz->direita->dado == 'F') {
                raiz->dado = 'F';
            } 
            else if (raiz->esquerda->dado == 'T' && raiz->direita->dado == 'T') {
                raiz->dado = 'T';
            }
        } 
        
        // Regra para o operador 'MENOR OU IGUAL'
        else if (raiz->dado == '{') {
            if (raiz->esquerda->dado == '0' || raiz->direita->dado == '9') {
                raiz->dado = 'T';
            } 
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado <= raiz->direita->dado)
                    raiz->dado = 'T';
                else
                    raiz->dado = 'F';
            }
            else if (raiz->direita->dado == raiz->esquerda->dado) {
                raiz->dado = 'T';
            }
        }

        // Regra para o operador 'MAIOR OU IGUAL'
        else if (raiz->dado == '}') {
            if (raiz->esquerda->dado == '9' || raiz->direita->dado == '0') {
                raiz->dado = 'T';
            } 
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado >= raiz->direita->dado)
                    raiz->dado = 'T';
                else
                    raiz->dado = 'F';
            }
            else if (raiz->direita->dado == raiz->esquerda->dado) {
                raiz->dado = 'T';
            }
        }

        // Regra para o operador 'MAIOR'
        else if (raiz->dado == '>') {
            if (raiz->esquerda->dado == '0' || raiz->direita->dado == '9') {
                raiz->dado = 'F';
            } 
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado > raiz->direita->dado)
                    raiz->dado = 'T';
                else
                    raiz->dado = 'F';
            }
            else if (raiz->direita->dado == raiz->esquerda->dado) {
                raiz->dado = 'F';
            }
        }

        // Regra para o operador 'MENOR'
        else if (raiz->dado == '<') {
            if (raiz->esquerda->dado == '9' || raiz->direita->dado == '0') {
                raiz->dado = 'F';
            } 
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado < raiz->direita->dado)
                    raiz->dado = 'T';
                else
                    raiz->dado = 'F';
            }
            else if (raiz->direita->dado == raiz->esquerda->dado) {
                raiz->dado = 'F';
            }
        }
        
        // Regra para o operador 'IGUALDADE'
        else if (raiz->dado == '=') {
            if ((raiz->esquerda->dado == raiz->direita->dado) & eh_operando(raiz->esquerda->dado) & eh_operando(raiz->direita->dado)) {
                raiz->dado = 'T';
            }
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado != raiz->direita->dado)
                    raiz->dado = 'F';
            }
        } 
        
        // Regra para o operador 'DIFERENÇA'
        else if (raiz->dado == '!') {
            if ((raiz->esquerda->dado == raiz->direita->dado) & eh_operando(raiz->esquerda->dado) & eh_operando(raiz->direita->dado)) {
                raiz->dado = 'F';
            } 
            else if (eh_numero(raiz->esquerda->dado) & eh_numero(raiz->direita->dado)) {
                if (raiz->esquerda->dado == raiz->direita->dado)
                    raiz->dado = 'F';
                else
                    raiz->dado = 'T';
            }
        }
    }
    
    return raiz;
}


void imprimir_arvore(p_no raiz, bool precisa_parenteses, bool eh_raiz) {
    if (raiz) {
        if (eh_operando(raiz->dado)) {  // Se for operando, apenas imprimimos ele na linha
            printf("%c", raiz->dado);
        } 
        else {
            // Colocamos os parênteses que vão à esquerda da expressão
            // Se for raiz sempre terá parênteses no início e no final, para abrir e fechar a expressão como um todo
            if (precisa_parenteses)
                printf("(");
            else if (eh_raiz)
                printf("(");

            // Começa a imprimir as subárvores esquerdas, e seta 'precisa_parenteses' como verdadeiro, pois o operador é cercado por parênteses
            imprimir_arvore(raiz->esquerda, true, false);

            printf(" %c ", raiz->dado); // Adiciona espaços em torno do operador

            // Imprime as subárvores da direita da raiz passada
            imprimir_arvore(raiz->direita, true, false);

            // Parenteses para fechar as expressões
            if (precisa_parenteses)
                printf(")");
            else if (eh_raiz)
                printf(")");
            
        }
    }
}


void libera_arvore(p_no raiz) {
    if (raiz) {
        libera_arvore(raiz->esquerda);
        libera_arvore(raiz->direita);
        free(raiz);
    }
}