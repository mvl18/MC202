#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int main(void) {
    int n_panelas, n_sobreviventes, n_operacoes;
    int id, modifica, rodada = 0;
    char entrada[MAX_ENT], comando[MAX_COM], prato[MAX_PRA];  //armazena a linha de código lida

    scanf("%d %d\n", &n_panelas, &n_sobreviventes); //recebe o número de panelas e o número de sobreviventes

    p_cliente sobrevivente = alocar_sobreviventes(n_sobreviventes);
    p_hp heap = cria_heap(n_sobreviventes);

    //recebe o nome dos sobreviventes e sua prioridade e armazena no vetor "sobrevivente"
    for (int i = 0; i < n_sobreviventes; i++) {
        fgets(entrada, MAX_ENT, stdin);
        sscanf(entrada, "%[^0-9] %d", sobrevivente[i].nome, &sobrevivente[i].prioridade);
        sobrevivente[i].posicao = -1;  //indica que o sobrevivente ainda não fez nenhum pedido
    }
    
    //recebe a quantidade de pratos para a primeira rodada
    scanf("%d\n", &n_operacoes);

    //loop principal para processar as rodadas
    while (n_operacoes != 0) {
        rodada ++;
        //processa as operações de cada rodada
        for (int i = 0; i < n_operacoes; i++) {
            fgets(entrada, MAX_ENT, stdin);
            sscanf(entrada, "%s %d", comando, &id);
            //verifica o tipo de operação: novo pedido ou modificação de prioridade
            if (strcmp(comando, "novo") == 0) {
                sscanf(entrada, "%*s %*d %[^\n]", prato);
                insere_heap(heap, cria_pedido(prato, id, sobrevivente[id].prioridade),sobrevivente);
            }
            else{
                sscanf(entrada, "%*s %*d %d", &modifica);
                muda_prioridade(heap, sobrevivente[id].posicao, modifica, sobrevivente);
            }    
        }
        //imprime os resultados da rodada
        imprime_rodada(n_panelas, rodada, heap, sobrevivente);
        scanf("%d\n", &n_operacoes);  //recebe a quantidade de pratos para a próxima rodada
    }
    //processa os pratos restantes no heap após todas as rodadas
    while (heap->n_pratos != 0) {
        rodada++;
        imprime_rodada(n_panelas, rodada, heap, sobrevivente);   
    }
    //libera a memória alocada para o heap e o vetor de sobreviventes
    libera_heap(heap);
    free(sobrevivente);
}