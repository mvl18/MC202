#ifndef PILHA_H
#define PILHA_H
#include "torno.h"

//struct para criar uma lista ligada para ser utilizada na pilha
typedef struct no *p_no;
struct no {
    p_peca dado;
    p_no prox;
};

//armazena as peças em uma pilha, além do tamanho total da pilha e o que é utilizado
typedef struct pilha *p_pilha;
struct pilha {
    p_no topo;
    int tamanho, usado;
};

//função que recebe um inteiro referente ao tamanho da pilha e retorna uma pilha iniciada
p_pilha criar_pilha(int tam_pilha);

//função que adiciona uma peça desejada na pilha 
void adiciona_peca_pilha(p_pilha pilha , p_peca torno);

//função que remove a peça do topo da pilha e retorna os dados da peça
p_no remove_peca_pilha(p_pilha pilha);

//função que desaloca a pilha, já que ela é feita com lista ligada
void destruir_pilha(p_pilha pilha);

#endif