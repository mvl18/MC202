#define MAX 200
#define MAX_TIP 7
#define MAX_OPE 2
#define MAX_VAR 50

// Estrutura de um nó da árvore rubro-negra esquerdista
enum cor {VERMELHO, PRETO};
typedef struct no *p_no;
struct no {
    char variavel[MAX_VAR];
    char tipo[MAX_TIP];
    enum cor cor;
    p_no esq, dir;
};

// Função que insere novo nó na árvore
p_no inserir(p_no raiz, char variavel[], char tipo[]);

// Função auxiliar para chamar os devidos ajustes para os nós, deixando a árvore balanceada
p_no inserir_rec(p_no raiz, char variavel[], char tipo[]);

// Função auxiliar para balancear a árvore deixando o pai vermelho e os filhos preto
void sobe_vermelho(p_no raiz);

// Função auxiliar para balancear a árvore rotacionando subárvores para a direita
p_no rotaciona_para_direita (p_no raiz);

// Função auxiliar para balancear a árvore rotacionando subárvores para a esquerda
p_no rotaciona_para_esquerda (p_no raiz);

// Indica se o nó é vermelho
int eh_Vermelho(p_no x);

// Indica se o nó é preto
int eh_Preto(p_no x);

// Função para buscar o tipo associado a uma variável
const char * buscar_tipo(p_no raiz , const char variavel[]);

// Função para percorrer a árvore in-ordem e imprimir os nós
void arvore_inordem(p_no raiz);

// Função para liberar a memória alocada pela árvore
void liberar_arvore(p_no raiz);