#define MAX 1000
#define TAM_PILHA 2

// Estrutura de um nó da árvore
typedef struct no *p_no;
struct no {
    char dado;
    p_no esquerda, direita;
};

// Função para criar um novo nó da árvore
p_no criar_no(char dado);

// Função para verificar se um caractere é um operando
bool eh_operando(char c);

// Função para verificar se um caractere é um número
bool eh_numero(char c);

// Função para construir a árvore a partir de uma expressão pós-fixa
p_no cria_arvore(char expressao[]);

// Função para otimizar a árvore
p_no otimiza_arvore(p_no raiz);

// Função para percorrer a árvore em ordem (infixa) e imprimir
void imprimir_arvore(p_no raiz, bool precisa_parenteses, bool eh_raiz);

// Função para liberar a memória dos nós da árvore
void libera_arvore(p_no raiz);