#define MAX 20  //tamanho máximo do grafo

// Estrutura para representar um nó na lista de adjacência
typedef struct no_grafo *p_no_grafo;
struct no_grafo {
    int vertice;
    p_no_grafo prox;
};

// Estrutura para representar o grafo
typedef struct grafo *p_grafo;
struct grafo {
    p_no_grafo *adj;
    int vertices_max;
};

// Função para criar um grafo com um número máximo de vértices
p_grafo criar_grafo(int vertices_max);

// Função para inserir um vértice no grafo
void insere_vertice(p_grafo rede, int valor);

// Função para verificar se existe uma aresta entre dois vértices no grafo
int tem_aresta(p_grafo rede, int u, int v);

// Função para inserir uma aresta entre dois vértices no grafo
void insere_aresta(p_grafo rede, int u, int v);

// Função para remover uma aresta entre dois vértices no grafo
void remove_aresta(p_grafo rede, int u, int v);

// Função para destruir o grafo e liberar toda a memória alocada
void destroi_grafo(p_grafo rede);

// Função para encontrar os vértices conexos em um grafo por busca em profundidade
void vertices_conexos(p_grafo rede, int *conexos);

// Função para realizar uma busca em largura no grafo e encontrar o menor caminho entre dois vértices
void busca_largura(p_grafo rede, int inicio, int fim);

// Função auxiliar para realizar uma visita recursiva a partir de um vértice
void visita_rec(p_grafo rede, int *conexos , int n_conexao , int v);

// Função auxiliar para inserir um elemento no início de uma lista
p_no_grafo insere_lista(p_no_grafo lista , int valor);

// Função auxiliar para remover um elemento de uma lista
p_no_grafo remove_lista(p_no_grafo lista , int valor);

// Função auxiliar para liberar memória ocupada por uma lista
void libera_lista(p_no_grafo lista);