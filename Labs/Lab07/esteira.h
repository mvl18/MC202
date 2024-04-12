#ifndef ESTEIRA_H
#define ESTEIRA_H
#include "torno.h"

//armazena as peças em uma fila, além do tamanho total da lista e o que é utilizado
typedef struct fila *p_fila;
struct fila {
    p_peca *vetor;
    int ini, fim, tamanho, usado;
};

/*função que recebe um inteiro referente ao tamanho da esteira e retorna uma
fila iniciada criada com a estrutura de vetor circular*/
p_fila criar_esteira(int tam_esteira);

//função que adiciona uma peça desejada na fila e retorna 1 quando chamada
p_fila adiciona_peca_esteira(p_fila esteira, p_peca torno);

//função que remove a peça da esteira e retorna os dados da peça
p_peca remove_peca_esteira(p_fila esteira);

//função que desaloca a esteira, já que ela é feita com vetor dinamicamente alocado
void destruir_esteira(p_fila esteira);

#endif