#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

p_grafo criar_grafo(int vertices_max) {
    p_grafo rede = malloc(sizeof(struct grafo));
    rede->vertices_max = vertices_max;
    rede->adj = malloc(vertices_max * sizeof(p_no_grafo));

    for (int i = 0; i < vertices_max; i++)
        rede->adj[i] = NULL;

    return rede;
}

void insere_vertice(p_grafo rede, int valor) {
        p_no_grafo novo = malloc(sizeof(struct no_grafo));
        novo->vertice = valor;
        novo->prox = rede->adj[valor];
        rede->adj[valor] = novo;
}

int tem_aresta(p_grafo rede, int u, int v) {
    for (p_no_grafo temp = rede->adj[u]; temp != NULL; temp = temp->prox)
        if (temp->vertice == v)
            return 1;

    return 0;
}

void insere_aresta(p_grafo rede, int u, int v) {
    //se a aresta ainda não existe
    if (!tem_aresta(rede, u, v)) {
        rede->adj[v] = insere_lista(rede->adj[v], u);
        rede->adj[u] = insere_lista(rede->adj[u], v);
    }
}

void remove_aresta(p_grafo rede, int u, int v) {
    //se existe aresta entre os vértices
    if (tem_aresta(rede, u, v)) {
        rede->adj[u] = remove_lista(rede->adj[u], v);
        rede->adj[v] = remove_lista(rede->adj[v], u);
    }
}

void destroi_grafo(p_grafo rede) {
    for (int i = 0; i < rede->vertices_max; i++)
        libera_lista(rede->adj[i]);

    free(rede->adj);
    free(rede);
}

p_no_grafo insere_lista(p_no_grafo lista , int valor) {
    p_no_grafo novo = malloc(sizeof(struct no_grafo));
    novo->vertice = valor;
    novo->prox = lista;

    return novo;
}

p_no_grafo remove_lista(p_no_grafo lista , int valor) {
    if (lista == NULL)
        return NULL;
    else if (lista->vertice == valor) {
        p_no_grafo proximo = lista->prox;
        free(lista);
        return proximo;
    }
    else {
        lista->prox = remove_lista(lista->prox, valor);
        return lista;
    }
}

void libera_lista(p_no_grafo lista) {
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void vertices_conexos(p_grafo rede, int *conexos) {
    int n_conexao = 0;
    for (int i = 0; i < rede->vertices_max; i++)
        conexos[i] = -1;
    for (int v = 0; v < rede->vertices_max; v++)
        if (conexos[v] == -1  && rede->adj[v] != NULL) {
            visita_rec(rede, conexos, n_conexao, v);
            n_conexao++;
        }
}

void visita_rec(p_grafo rede, int *conexos , int n_conexao , int v) {
    conexos[v] = n_conexao;
    for (p_no_grafo temp = rede->adj[v]; temp != NULL; temp = temp->prox)
        if (conexos[temp->vertice] == -1)
            visita_rec(rede, conexos, n_conexao, temp->vertice);
}

void busca_largura(p_grafo rede, int inicio, int fim) {
    int *visitado = malloc(rede->vertices_max * sizeof(int));
    int *anterior = malloc(rede->vertices_max * sizeof(int));

    for (int i = 0; i < rede->vertices_max; i++) {
        visitado[i] = 0;
        anterior[i] = -1;
    }

    //inicializa a fila
    int *fila = malloc(rede->vertices_max * sizeof(int));
    int frente = 0, fim_fila = 0;

    //adiciona o vértice inicial à fila
    fila[fim_fila++] = inicio;
    visitado[inicio] = 1;

    while (frente != fim_fila) {
        int atual = fila[frente++];
        
        //processa os vértices adjacentes
        for (p_no_grafo temp = rede->adj[atual]; temp != NULL; temp = temp->prox) {
            int vizinho = temp->vertice;

            if (!visitado[vizinho]) {
                fila[fim_fila++] = vizinho;
                visitado[vizinho] = 1;
                anterior[vizinho] = atual;

                //se chegou ao vértice de destino, interrompe a busca
                if (vizinho == fim) {
                    free(fila);
                    free(visitado);

                    int caminho[MAX];
                    int indice = 0;
                    for (int v = fim; v != -1; v = anterior[v])
                        caminho[indice++] = v;

                    for (int i = indice - 1; i >= 0; i--)
                        printf("%d%s", caminho[i], (i == 0) ? "\n" : " -> ");

                    free(anterior);
                    return;
                }
            }
        }
    }

    free(fila);
    free(visitado);
    free(anterior);

    printf("Não existe conexão entre os nós.\n");
}