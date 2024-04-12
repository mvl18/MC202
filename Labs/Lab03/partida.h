//struct de dados de cada partida
typedef struct _dados{
    int n_jogadores;
    int n_circuitos;
    int n_equipamentos;
    float aluguel;
} dados;

// função que recebe um inteiro, indicador do id da partida
void dados_partida(int id_partida);