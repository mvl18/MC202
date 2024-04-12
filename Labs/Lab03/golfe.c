#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

int main(void)
{
    int n_partidas;
    scanf("%d", &n_partidas);

    for (int i = 1; i <= n_partidas; i++)
        dados_partida(i);

    return 0;
}