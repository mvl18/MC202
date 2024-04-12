#define MAX_FAM 3041    //primo maior que o dobro de 1500 e distante de uma potência de 2
#define MAX_CHA 13      //tamanho máximo dos chars

// Estrutura para armazenar informações da família
typedef struct familia *p_familia;
struct familia {
    char nome[MAX_CHA]; //sobrenome da família
    int qtdDoces;       //quantidade de doces que a família possui
    int disponivel;     //1 se a família está disponível, 0 se não, e -1 se saiu
};

// Função de hash simples
int hash(char *nome, int tamanho);

// Função para achar o mínimo entre dois inteiros
int min(int a, int b);

// Função para inicializar a tabela hash
p_familia inicializarTabelaHash(int tamanho);

// Função para inserir uma família na tabela hash
void entrar(p_familia tabela, char *nome, int qtdDoces, int tamanho);

// Função para remover uma família da tabela hash
void sair(p_familia tabela, char *nome, int tamanho);

// Função para atualizar a quantidade de doces de uma família
void comprar(p_familia tabela, char *nome, int qtdDoces, int tamanho);

// Função para realizar a operação de "Trick or Treat"
void trickOrTreat(p_familia tabela, char *nome, char *sobrenome, int qtdCasas, int tamanho);