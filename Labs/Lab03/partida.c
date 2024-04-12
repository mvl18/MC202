#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "circuito.h"

void dados_partida(int id_partida) 
{
    dados d;

    scanf("%d %d %d", &d.n_jogadores, &d.n_circuitos, &d.n_equipamentos);
    printf("Partida %d\n", id_partida);
    printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de Equipamentos: %d\n", d.n_jogadores, d.n_circuitos, d.n_equipamentos);
    d.aluguel = 10*d.n_circuitos + 17.5*d.n_equipamentos; //calcula o valor do aluguel de cada partida
    printf("Valor do Aluguel: R$ %.2f\n", d.aluguel);

    analise_circuitos(d.n_jogadores, d.n_circuitos);
    
    printf("##########\n");
}

