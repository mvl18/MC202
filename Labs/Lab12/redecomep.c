#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main (void) {
    int comando, valor_1, valor_2;   //recebe o comando e o valor dos vértices para as operações
    p_grafo rede = criar_grafo(MAX); //cria o grafo alocando memória para ele
    int *conexos = malloc(rede->vertices_max * sizeof(int));  //cria vetor para as operações 4 e 6

    scanf("%d", &comando);
    while (1) {
        //adiciona um novo vértice na rede
        if (comando == 1) {
            scanf("%d", &valor_1);
            insere_vertice(rede, valor_1);
        }
        //conecta dois vértices da rede, se a conexão já existe, o comando é ignorado
        else if (comando == 2) {
            scanf("%d %d", &valor_1, &valor_2);
            insere_aresta(rede, valor_1, valor_2);
        }
        //desconecta dois vértices da rede, se a conexão já existe, o comando é ignorado
        else if (comando == 3) {
            scanf("%d %d", &valor_1, &valor_2);
            remove_aresta(rede, valor_1, valor_2);
        }
        //verifica se há conexão direta ou indireta entre dois vértices da rede;
        else if (comando == 4) {
            scanf("%d %d", &valor_1, &valor_2);
            vertices_conexos(rede, conexos);

            if (conexos[valor_1] == conexos[valor_2])
                printf("Existe conexão entre os nós.\n");
            else
                printf("Não existe conexão entre os nós.\n");
        }
        //encontra a conexão mais curta entre dois vértices da rede
        else if (comando == 5) {
            scanf("%d %d", &valor_1, &valor_2);
            busca_largura(rede, valor_1, valor_2);            
        }
        //para cada vértice da rede encontra seus vértices com conexão direta ou indireta
        else if (comando == 6) {
            vertices_conexos(rede, conexos);
            for (int i = 0; i < rede->vertices_max; i++) {
                if (conexos[i] != -1) {
                    printf("Ponto %d (Pontos diretamente ou indiretamente conectados): ", i);
                    int n_conexao = conexos[i];
                    for (int v = 0; v < rede->vertices_max; v++) {
                        if (conexos[v] == n_conexao) {
                            printf("%d ", v);
                        }
                    }
                    printf("\n");
                }
            }            
        }
        //encerra o programa
        else
            break;
        
        scanf("%d", &comando);
    }

    free(conexos);  //libera memória do vetor conexos
    destroi_grafo(rede);    //libera memória alocada para o grafo
    
    return 0;
}