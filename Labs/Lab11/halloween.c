#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main(void) {
    p_familia tabelaHash = inicializarTabelaHash(MAX_FAM);  //inicializa a tabela hash

    //declaração de variáveis
    char operacao[MAX_CHA];
    char nome[MAX_CHA];
    char sobrenome[MAX_CHA];
    int qtdCasas;
    int qtdDoces;

    //loop principal
    while (1) {
        scanf("%s", operacao);  //lê operação a ser realizada

        //verifica a operação e executa a ação correspondente chamando a função
        if (strcmp(operacao, "ENTRAR") == 0) {
            scanf("%s %d", nome, &qtdDoces);
            entrar(tabelaHash, nome, qtdDoces, MAX_FAM);
        } 
        else if (strcmp(operacao, "SAIR") == 0) {
            scanf("%s", nome);
            sair(tabelaHash, nome, MAX_FAM);
        } 
        else if (strcmp(operacao, "COMPRAR") == 0) {
            scanf("%s %d", nome, &qtdDoces);
            comprar(tabelaHash, nome, qtdDoces, MAX_FAM);
        } 
        else if (strcmp(operacao, "TRICKORTREAT") == 0) {
            scanf("%s %s %d", nome, sobrenome, &qtdCasas);
            trickOrTreat(tabelaHash, nome, sobrenome, qtdCasas, MAX_FAM);
        } 
        else if (strcmp(operacao, "FINALIZAR") == 0)
            break;  //finaliza o loop para encerrar o programa
    }

    free(tabelaHash);  //libera a memória alocada para a tabela hash
    return 0;
}
