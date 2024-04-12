#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

p_pilha criar_pilha(int tam_pilha)
{
    p_pilha pilha = malloc(sizeof(struct pilha));
    
    pilha->tamanho = tam_pilha;
    pilha->usado = 0;
    pilha->topo = NULL;

    return pilha;
}

void adiciona_peca_pilha(p_pilha pilha , p_peca torno) {
    p_no novo = malloc(sizeof(struct no));
    novo->dado = torno;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->usado ++;
}

p_no remove_peca_pilha(p_pilha pilha) {
    p_no topo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    pilha->usado --;

    return topo;
}

void destruir_pilha(p_pilha pilha) {
    while (pilha->topo != NULL) {
        p_no temp = pilha->topo;
        pilha->topo = pilha->topo->prox;
        free(temp);
    }
    free(pilha);
}