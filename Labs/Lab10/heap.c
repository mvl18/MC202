#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

p_cliente alocar_sobreviventes(int n_sobreviventes) {
    p_cliente v;
    v = malloc(n_sobreviventes * sizeof(struct cliente));

    return v;
}

p_hp cria_heap(int tam) {
    p_hp heap = malloc(sizeof(struct HP));
    heap->v = malloc(tam * sizeof(pedido));
    heap->n_pratos = 0;
    heap->tamanho = tam;
    
    return heap;
}

pedido cria_pedido(char prato[], int id, int prioridade) {
    pedido p;
    strcpy(p.prato, prato);
    p.id_sobrevivente = id;
    p.prioridade = prioridade;

    return p;
}

void insere_heap(p_hp heap, pedido item, p_cliente sobrevivente) {
    heap->v[heap->n_pratos] = item;  //adiciona o novo pedido ao final do vetor do heap
    //atualiza para o sobrevivente a posição de seu prato
    sobrevivente[item.id_sobrevivente].posicao = heap->n_pratos;
    heap->n_pratos++;  //incrementa o número total de pratos no heap
    sobe_heap(heap, heap->n_pratos-1, sobrevivente);
}

void sobe_heap(p_hp heap, int k, p_cliente sobrevivente) {
    if (k > 0 && heap->v[PAI(k)].prioridade < heap->v[k].prioridade) {
        troca(&heap->v[k], &heap->v[PAI(k)]);  //se a prioridade do pai for menor que a do filho, trocamos
        sobrevivente[heap->v[k].id_sobrevivente].posicao = k;  //atualiza a posição do prato "filho" para o cliente
        sobrevivente[heap->v[PAI(k)].id_sobrevivente].posicao = PAI(k); //atualiza a posição do prato "pai" para o cliente
        sobe_heap(heap, PAI(k), sobrevivente);
    }
}

void desce_heap(p_hp heap, int k, p_cliente sobrevivente) {
    int maior_filho;
    if (F_ESQ(k) < heap->n_pratos) {
        maior_filho = F_ESQ(k);
        if (F_DIR(k) < heap->n_pratos && heap->v[F_ESQ(k)].prioridade < heap->v[F_DIR(k)].prioridade)
            maior_filho = F_DIR(k);
        if (heap->v[k].prioridade < heap->v[maior_filho].prioridade) {
            troca(&heap ->v[k], &heap->v[maior_filho]);
            sobrevivente[heap->v[k].id_sobrevivente].posicao = k;
            sobrevivente[heap->v[maior_filho].id_sobrevivente].posicao = maior_filho;
            desce_heap(heap, maior_filho, sobrevivente);
        }
    }
}

pedido extrai_maximo(p_hp heap, p_cliente sobrevivente) {
    pedido item = heap->v[0];
    troca(&heap->v[0], &heap->v[heap->n_pratos-1]);
    sobrevivente[heap->v[0].id_sobrevivente].posicao = 0;
    sobrevivente[heap->v[heap->n_pratos-1].id_sobrevivente].posicao = -1;
    heap->n_pratos--;
    desce_heap(heap, 0, sobrevivente);

    return item;
}

void muda_prioridade(p_hp heap, int k, int valor, p_cliente sobrevivente) {
    if (valor > 0) {
        heap->v[k].prioridade += valor;
        sobe_heap(heap, k, sobrevivente);
    } 
    else {
        heap->v[k].prioridade += valor;
        desce_heap(heap, k, sobrevivente);
    }
}

void troca(pedido *a, pedido *b) {
    pedido temp = *a;
    *a = *b;
    *b = temp;
}

void imprime_rodada(int n_panelas, int rodada, p_hp heap, p_cliente sobrevivente) {
    printf("---- rodada %d ----\n", rodada);
    while (n_panelas > 0 && heap->n_pratos !=0) {
        pedido item = extrai_maximo(heap, sobrevivente);  //recebe 
        printf("%s%s %d\n", sobrevivente[item.id_sobrevivente].nome, item.prato, item.prioridade);
        n_panelas--;
    }
}

void libera_heap(p_hp heap) {
    free(heap->v);  //libera a memória do vetor de pedidos
    free(heap);
}