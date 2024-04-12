#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalhador.h"
#include "pilha.h"
#include "esteira.h"

p_trabalhador criar_trabalhador(p_peca torno)
{
    p_trabalhador funcionario = malloc(sizeof(struct trabalhador));

    funcionario->enviou = 0;
    funcionario->pegou = 0;
    funcionario->torno = torno;

    return funcionario;
}

void classificador_pega_peca(p_fila esteira, p_trabalhador classificador)
{
    p_peca pega = remove_peca_esteira(esteira);
    classificador->torno = pega;
    classificador->pegou ++;  //aumenta em 1 o número de peças que foram retiradas da esteira
}

int classificador_envia_peca(p_pilha pilha, p_trabalhador classificador, p_peca vazio)
{
    adiciona_peca_pilha(pilha, classificador->torno);
    classificador->enviou ++;  //aumenta em 1 o número de peças que foram classificadas
    classificador->torno = vazio;

    return 1;
}

void embalador_pega_peca(p_pilha pilha, p_trabalhador embalador)
{
    p_no pega = remove_peca_pilha(pilha);
    embalador->torno = pega->dado;
    free(pega);
    embalador->pegou ++;  //aumenta em 1 o número de peças que foram retiradas da pilha
}

int embalador_envia_peca(p_trabalhador embalador, p_peca vazio)
{
    embalador->enviou ++;  //aumenta em 1 o número de peças que foram embaladas
    destruir_peca(embalador->torno);  //desaloca o espaço de memória do torno
    embalador->torno = vazio;
    
    return 1;
}

void dispensa_funcionario(p_trabalhador funcionario)
{
    free(funcionario);  // Libera a memória alocada para o funcionario
}

