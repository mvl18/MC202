#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int hash(char *nome, int tamanho) {
    int i, n = 0;
    //itera sobre os caracteres da string e calcula o hash usando multiplicação
    for (i = 0; i < strlen(nome); i++)
        n = (256 * n + nome[i]) % tamanho;
    
    return n;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

p_familia inicializarTabelaHash(int tamanho) {
    //aloca memória para a tabela
    p_familia tabela = (p_familia)malloc(tamanho * sizeof(struct familia));
    //inicializa o campo disponivel com 0
    for (int i = 0; i < tamanho; i++)
        tabela[i].disponivel = 0;

    return tabela;
}

void entrar(p_familia tabela, char *nome, int qtdDoces, int tamanho) {
    //calcula o índice usando a função de hash
    int index = hash(nome, tamanho);
    //resolve colisões usando sondagem linear
    while (tabela[index].disponivel == 1 || tabela[index].disponivel == -1)
        index = (index + 1) % tamanho;
    //copia o nome da família para a tabela
    strcpy(tabela[index].nome, nome);
    //define a quantidade de doces e marca como disponível
    tabela[index].qtdDoces = qtdDoces;
    tabela[index].disponivel = 1;
}

void sair(p_familia tabela, char *nome, int tamanho) {
    int index = hash(nome, tamanho);

    while (tabela[index].disponivel == 1 || tabela[index].disponivel == -1) {
        //se encontra a família, imprime a mensagem, marca como removida
        if (strcmp(tabela[index].nome, nome) == 0) {
            printf("A familia %s saiu com %d doce(s) sobrando.\n", nome, tabela[index].qtdDoces);
            tabela[index].disponivel = -1;
            return;
        }
        index = (index + 1) % tamanho;
    }
}

void comprar(p_familia tabela, char *nome, int qtdDoces, int tamanho) {
    int index = hash(nome, tamanho);

    while (tabela[index].disponivel == 1 || tabela[index].disponivel == -1) {
        //se encontra a família, adiciona a quantidade correta de doces e imprime mensagem
        if (strcmp(tabela[index].nome, nome) == 0) {
            tabela[index].qtdDoces += qtdDoces;
            printf("A familia %s agora possui %d doces.\n", nome, tabela[index].qtdDoces);
            return;
        }
        index = (index + 1) % tamanho;
    }
}

void trickOrTreat(p_familia tabela, char *nome, char *sobrenome, int qtdCasas, int tamanho) {
    int totalDoces = 0;
    //loop para cada casa visitada pelas crianças
    for (int i = 0; i < qtdCasas; i++) {
        char nomeFamilia[MAX_CHA];
        char nota[MAX_CHA];
        scanf("%s %s", nomeFamilia, nota);  //lê o nome da família e a nota da casa

        int index = hash(nomeFamilia, tamanho);

        while (tabela[index].disponivel == 1 || tabela[index].disponivel == -1) {
            //se encontra a família, distribui os doces conforme a nota
            if (strcmp(tabela[index].nome, nomeFamilia) == 0  && tabela[index].qtdDoces != 0) {
                if (strcmp(nota, "Boa") == 0) {
                    totalDoces += min(3, tabela[index].qtdDoces);
                    tabela[index].qtdDoces -= min(3, tabela[index].qtdDoces);
                } 
                else if (strcmp(nota, "Media") == 0) {
                    totalDoces += min(2, tabela[index].qtdDoces);
                    tabela[index].qtdDoces -= min(2, tabela[index].qtdDoces);
                } 
                else if (strcmp(nota, "Ruim") == 0) {
                    totalDoces += min(1, tabela[index].qtdDoces);
                    tabela[index].qtdDoces -= min(1, tabela[index].qtdDoces);
                }
                //se a família ficou sem doces, imprime mensagem
                if (tabela[index].qtdDoces == 0) {
                    printf("A familia %s ficou sem doces.\n", nomeFamilia);
                }
                break;
            }
            index = (index + 1) % tamanho;
        }
    }
    //imprime mensagem com base no total de doces obtidos
    if (totalDoces == 0)
        printf("%s %s recebeu 10 doces da prefeitura.\n", nome, sobrenome);
    else
        printf("%s %s recebeu %d doce(s) das familias.\n", nome, sobrenome, totalDoces);
}
