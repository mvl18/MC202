#include <stdio.h>

void seguimento(int anterior, int valor, int serie[]);  //inicia a função "seguimento"

int main(void) {
    int vendas, valor, cinco = 0, sete = 0, dez = 0, anterior = 0;
    int serie[3] = {0,0,1};  //array que armazena o valor mais recorrente na primeira posição, recorrência na segunda e recorrência momentânea na terceira.
    scanf("%d", &vendas);  //recebe do usuário um número inteiro que indica o número de vendas
    
    for (int i = 0; i < vendas; i++) {
        scanf("%d", &valor);  //recebe valor a valor e já analisa antes de receber o próximo por conta do loop for

        if (valor == 5){
            cinco++;
            seguimento(anterior, valor, serie);
        }
        else if (valor == 7){
            sete++;
            seguimento(anterior, valor, serie);
        }
        else if (valor == 10){
            dez++;
            seguimento(anterior, valor, serie);
        }
        anterior = valor;  //valor é armazenado na variável "anterior" para posterior comparação
    }

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", cinco, sete, dez);
    printf("James vendeu %d saladas de %d reais consecutivamente\n", serie[1], serie[0]);

    return 0;
}

void seguimento(int anterior, int valor, int serie[]) {
    if (anterior == valor) {
        serie[2]++;  //se o valor momentâneo for igual ao anterior adicionamos +1
        if (serie[2] > serie[1]) {  //caso a recorrência momentânea seja maior que a maior recorrência já encontrada fazemos:
            serie[0] = valor;  //a primeira posição da array recebe o valor
            serie[1] = serie[2];  //a segunda posição da array recebe a maior recorrência já encontrada até o momento 
        }      
    }
    else
        serie[2] = 1;  //reseta a recorrência momentânea
}
