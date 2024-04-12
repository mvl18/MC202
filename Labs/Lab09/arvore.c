#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"


int eh_Vermelho(p_no x) {
    if (x == NULL)
        return 0;

    return x->cor == VERMELHO;
}


int eh_Preto(p_no x) {
    if (x == NULL)
        return 1;

    return x->cor == PRETO;
}


void sobe_vermelho(p_no raiz) {
    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}


p_no rotaciona_para_direita (p_no raiz) {
    p_no x = raiz->esq;
    raiz->esq = x->dir;
    x->dir = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}


p_no rotaciona_para_esquerda (p_no raiz) {
    p_no x = raiz->dir;
    raiz->dir = x->esq;
    x->esq = raiz;
    x->cor = raiz->cor;
    raiz->cor = VERMELHO;

    return x;
}


p_no inserir_rec(p_no raiz, char variavel[], char tipo[]) {
    p_no novo;
    if (raiz == NULL) {
        novo = malloc(sizeof(struct no));
        novo->esq = novo->dir = NULL;
        strcpy(novo->variavel, variavel);
        strcpy(novo->tipo, tipo);
        novo->cor = VERMELHO;
        return novo;
    }

    if (strcmp(variavel, raiz->variavel) < 0)
        raiz->esq = inserir_rec(raiz->esq, variavel, tipo);

    else
        raiz->dir = inserir_rec(raiz->dir, variavel, tipo);

    
    if (eh_Vermelho(raiz->dir) && eh_Preto(raiz->esq))
        raiz = rotaciona_para_esquerda (raiz);

    if (eh_Vermelho(raiz->esq) && eh_Vermelho(raiz->esq->esq))
        raiz = rotaciona_para_direita (raiz);

    if (eh_Vermelho(raiz->esq) && eh_Vermelho(raiz->dir))
        sobe_vermelho(raiz);

    return raiz;
}


p_no inserir(p_no raiz, char variavel[], char tipo[]) {
    raiz = inserir_rec(raiz, variavel, tipo);
    raiz->cor = PRETO;
    return raiz;
}


const char * buscar_tipo(p_no raiz , const char variavel[]) {
    if (raiz == NULL)
        return NULL;

    if (strcmp(variavel, raiz->variavel) == 0)
        return raiz->tipo;

    if (strcmp(variavel, raiz->variavel) < 0)
        return buscar_tipo(raiz->esq, variavel);

    else
        return buscar_tipo(raiz->dir, variavel);
}


void arvore_inordem(p_no raiz) {
    if (raiz != NULL) {
        arvore_inordem(raiz->esq);
        printf("%s %s\n", raiz->variavel, raiz->tipo);
        arvore_inordem(raiz->dir);
    }
}


void liberar_arvore(p_no raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz);
    }
}