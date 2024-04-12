//struct que analisa os circuitos
typedef struct _circuito{
    int *pontuacao;
    int ponto;
    int dificil;
    int mais_dificil;
    int circuito_dificil;
    int id_circuito;
} circuito;

//função que recebe dois inteiros, sendo o número de jogadores e o número de circuitos de cada partida
void analise_circuitos(int n_jogadores, int n_circuitos);
