#ifndef TORNO_H
#define TORNO_H
#define MAX 8
#define VAZIO 4
#define TERMINOU -1

//armazena o tempo de trabalho requerido para o classificador e embalador
typedef struct peca *p_peca;
struct peca {
    int tempo_classificador, tempo_embalador;
};

//função que pergunta ao usuário o tipo de peça desejado e retorna p_peca
p_peca adiciona_torno(int modo);

//função que desaloca a peça
void destruir_peca(p_peca peca);


#endif