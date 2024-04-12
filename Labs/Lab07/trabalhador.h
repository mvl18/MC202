#include "torno.h"
#include "pilha.h"
#include "esteira.h"

/*armazena a quantidade de peças que o trabalhador pegou, e enviou
além da peça que está trabalhando no momento*/
typedef struct trabalhador *p_trabalhador;
struct trabalhador {
    int pegou, enviou;
    p_peca torno;
};

//função que inicia um trabalhador com uma peça de inicialização
p_trabalhador criar_trabalhador(p_peca torno);

//função em que o classificador retira um torno da esteira para iniciar o trabalho
void classificador_pega_peca(p_fila esteira, p_trabalhador classificador);

//função em que o classificador envia para a pilha o torno finalizado retornando 1 quando executada
int classificador_envia_peca(p_pilha pilha, p_trabalhador classificador, p_peca vazio);

//função em que o classificador retira um torno da pilha para iniciar o trabalho
void embalador_pega_peca(p_pilha pilha, p_trabalhador embalador);

//função em que o embalador envia para a saída o torno finalizado retornando 1 quando executada
int embalador_envia_peca(p_trabalhador embalador, p_peca vazio);

//função que desaloca o funcionário
void dispensa_funcionario(p_trabalhador funcionario);