#define MAX_ENT 100
#define MAX_COM 7
#define MAX_PRA 28
#define MAX_NOM 32
#define PAI(i) ((i-1) /2) // Pai de i
#define F_ESQ(i) (2*i+1)  // Filho esquerdo de i
#define F_DIR(i) (2*i+2)  // Filho direito de i

// Armazena o nome do cliente, sua prioridade e posição se seu prato no heap
typedef struct cliente *p_cliente;
struct cliente{
    char nome[MAX_NOM]; //nome e sobrenome do sobrevivente
    int prioridade;     //quantidade de dias sobrevivendo
    int posicao;
};

// Armazena o nome do prato, o id do sobrevivente que pediu, e a prioridade do prato
typedef struct {
    char prato[MAX_PRA];
    int id_sobrevivente;
    int prioridade;
} pedido;

// Heap para manipular a prioridade dos pratos
typedef struct HP *p_hp;
struct HP{
    pedido *v;              //vetor do pedido alocado dinamicamente
    int n_pratos, tamanho;  //quantidade de pratos no heap, quantidade total
};

// Cria um vetor alocado dinamicamente para os sobreviventes
p_cliente alocar_sobreviventes(int n_sobreviventes);

// Inicializa heap para prioridade dos pratos
p_hp cria_heap(int tam);

// Cria um pedido com informações fornecidas
pedido cria_pedido(char prato[], int id, int prioridade);

// Insere o prato com sua prioridade no heap, além do id do sobrevivente
void insere_heap(p_hp heap, pedido item, p_cliente sobrevivente);

// Move um elemento para cima na árvore heap, mantendo a propriedade do heap
void sobe_heap(p_hp heap, int k, p_cliente sobrevivente);

// Move um elemento para baixo na árvore heap, mantendo a propriedade do heap
void desce_heap(p_hp heap, int k, p_cliente sobrevivente);

// Extrai o prato com maior prioridade do heap
pedido extrai_maximo(p_hp heap, p_cliente sobrevivente);

// Modifica a prioridade de um elemento no heap e ajusta a árvore heap conforme necessário
void muda_prioridade(p_hp heap, int k, int valor, p_cliente sobrevivente);

// Função para fazer a troca dos nós do heap
void troca(pedido *a, pedido *b);

// Imprime os pedidos de uma rodada até que o número de panelas seja alcançado ou o heap esteja vazio
void imprime_rodada(int n_panelas, int rodada, p_hp heap, p_cliente sobrevivente);

// Libera a memória alocada para o heap
void libera_heap(p_hp heap);