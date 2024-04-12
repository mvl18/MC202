#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "torno.h"


p_peca adiciona_torno(int modo) 
{   
    p_peca torno = malloc(sizeof(struct peca));

    /*modo que recebe o nome da peça e seu tipo e transforma no
    tempo de trabalho do embalador e do classificador*/
    if (modo == 1) {
        int tam_pacote;
        char tip_pacote[MAX];
        scanf("%s %d", tip_pacote, &tam_pacote);

        if (!strcmp(tip_pacote, "pequena")) {
            torno->tempo_classificador = 1;
            if (tam_pacote == 1)
                torno->tempo_embalador = 1;
            else
                torno->tempo_embalador = 2;   
        }

        else if (!strcmp(tip_pacote, "media")) {
            torno->tempo_classificador = 2;
            if (tam_pacote == 1)
                torno->tempo_embalador = 2;
            else
                torno->tempo_embalador = 3;   
        }

        else if (!strcmp(tip_pacote, "grande")) {
            torno->tempo_classificador = 3;
            if (tam_pacote == 1)
                torno->tempo_embalador = 2;
            else
                torno->tempo_embalador = 3;   
        }
    }
    
    //inicializa o modo em que o trabalhador não possui uma peça trabalhável nas mãos
    else {
        torno->tempo_classificador = VAZIO;
        torno->tempo_embalador = VAZIO;
    }
    
    return torno;
}

void destruir_peca(p_peca peca) {
    free(peca); //libera a memoria alocada para a peça
}
