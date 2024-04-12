#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"

void analise_circuitos(int n_jogadores, int n_circuitos) 
{
    circuito c;

    c.dificil = 0;
    c.mais_dificil = 0;
    c.pontuacao = calloc(n_jogadores, sizeof(int)); //cria um vetor dinâmico

    for (int i = 0; i < n_circuitos; i++)
    {   
        scanf("%d", &c.id_circuito);
        for (int j = 0; j < n_jogadores; j++)
        {   
            scanf("%d", &c.ponto);
            c.pontuacao[j] += c.ponto;
            c.dificil += c.ponto;
        }
        if (c.dificil > c.mais_dificil) //analisa se o circuito atual foi mais dificil que um anterior
        {
            c.mais_dificil = c.dificil;
            c.circuito_dificil = c.id_circuito;
        }
        c.dificil = 0;
    }
    
    for (int m = 0; m < n_jogadores; m++)
    {
        printf("Jogador %d: %d\n", m+1, c.pontuacao[m]);
    }

    free(c.pontuacao); //desaloca o vetor c.pontuacao

    printf("Circuito mais dificil: %d\n", c.circuito_dificil);
}