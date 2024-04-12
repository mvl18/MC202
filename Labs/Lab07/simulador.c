#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "torno.h"
#include "esteira.h"
#include "pilha.h"
#include "trabalhador.h"

int main(void)
{
    int tam_esteira, tam_pilha, n_pecas_entrada, n_pecas, atraso = 0, minuto = 1;

    scanf("%d %d", &tam_esteira, &tam_pilha); //recebe o tamanho máximo da esteira e da pilha
    scanf("%d", &n_pecas); //recebe o número máximo de peças que serão trabalhadas
    n_pecas_entrada = n_pecas;

    p_peca torno; //inicia as peças que entrarão na esteira
    p_peca vazio = adiciona_torno(0); //cria o estado de não trabalho dos trabalhadores
    p_fila esteira = criar_esteira(tam_esteira); //cria a esteira
    p_pilha pilha = criar_pilha(tam_pilha); //cria a pilha
    p_trabalhador classificador = criar_trabalhador(vazio); //cria o trabalhador classificador
    p_trabalhador embalador = criar_trabalhador(vazio); //cria o trabalhador embalador

    printf("##### Simulação\n");
    // enquanto o embalador não enviar a última peça a simulação continua
    while (embalador->enviou != n_pecas)
    {   
        int entrou_esteira = 0, saiu_esteira = 0, entrou_pilha = 0, saiu_pilha = 0;
        
        //se o embalador ainda está embalando uma peça
        if (embalador->torno->tempo_embalador != VAZIO) {
            embalador->torno->tempo_embalador --; //diminuímos em um minuto o tempo restante de trabalho
            //caso termine de trabalhar na peça
            if (embalador->torno->tempo_embalador == TERMINOU)
                //envia a peça para a saída e indica no minuto da simulação que uma peça foi para a saída
                saiu_pilha = embalador_envia_peca(embalador, vazio);
        }
        //se o embalador está sem serviço e tem uma peça na pilha
        if (embalador->torno->tempo_embalador == VAZIO && pilha->usado != 0) {
            embalador_pega_peca(pilha, embalador);  //o embalador pega a peça da pilha
            embalador->torno->tempo_embalador --; //diminuímos em um minuto o tempo restante de trabalho
        }
        
                
        //se o classificador ainda está classificando uma peça
        if (classificador->torno->tempo_classificador != VAZIO) {
            classificador->torno->tempo_classificador --; //diminuímos em um minuto o tempo restante de trabalho
            //caso termine de trabalhar na peça e a pilha não esteja cheia
            if (classificador->torno->tempo_classificador <= TERMINOU && pilha->usado != pilha->tamanho)
                //envia a peça para a pilha e indica no minuto da simulação que uma peça foi concluída pelo classificador e entrou na pilha 
                entrou_pilha = saiu_esteira = classificador_envia_peca(pilha, classificador, vazio);
        }
        //se o classificador está sem serviço e tem uma peça na esteira
        if (classificador->torno->tempo_classificador == VAZIO && esteira->usado != 0) {
            classificador_pega_peca(esteira, classificador);  //o classificador pega a peça da esteira
            classificador->torno->tempo_classificador --; //diminuímos em um minuto o tempo restante de trabalho
        }


        //se tiver espaço na esteira e ainda tiver peças para serem processadas
        if (esteira->usado != esteira->tamanho && n_pecas_entrada > 0) {
            torno = adiciona_torno(1);  //recebemos o tipo de peça que entrará na esteira
            //adicionamos a peça na esteira e indica no minuto da simulação que uma peça entrou na esteira
            esteira = adiciona_peca_esteira(esteira, torno);
            entrou_esteira = 1;
            n_pecas_entrada --;  //identificamos que temos uma peça a menos para processar na linha de produção
        }

        //se ainda temos peças para serem processadas mas não tem espaço na esteira
        else if (esteira->usado == esteira->tamanho && n_pecas_entrada > 0)
            atraso ++;  //aumentamos o atraso em um minuto


        printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", minuto, entrou_esteira, saiu_esteira, entrou_pilha, saiu_pilha);
        minuto ++; // passa o tempo para o próximo loop
    }
    
    printf("Tempo atraso: %d.\n", atraso);
    destruir_esteira(esteira);
    destruir_pilha(pilha);
    dispensa_funcionario(classificador);
    dispensa_funcionario(embalador);
    destruir_peca(vazio);

    return 0;
}