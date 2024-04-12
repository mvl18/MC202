#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "arvore.h"

int main(void) {
    // Inicialização de variáveis e da árvore
    p_no raiz = NULL;                   // Raiz da árvore
    int erro = 0;                       // Flag para rastrear erros
    int n_linha = 0;                    // Contador de linhas do código
    char expressao[MAX];                // Armazena a linha de código lida
    char operador[MAX_OPE];             // Armazena operador em expressões
    char variaveis[3][MAX_VAR] = {};    // Armazenas as variáveis
    char tipos[3][MAX_TIP] = {};        // Armazena os tipos
    const char *tipo_encontrado;        // Recebe o tipo da variável  

    // Loop para processar cada linha do código até chegar no final do arquivo, com seu rótulo
    proxima_linha: while (fgets(expressao, MAX, stdin) != NULL) {         
        n_linha ++; // Conta em que linha do código estamos

        // Verificar se a linha possui parenteses ou se é apenas uma linha de enter
        if (strchr(expressao, '(') != NULL || strspn(expressao, " \t\n") == strlen(expressao)){
            goto proxima_linha;  // Ignora linhas sem expressões válidas
        }

        sscanf(expressao, "%s", variaveis[0]); // Recebe a primeira palavra da linha

        // Verifica se a primeira palavra não começa com uma letra, ou se não é "return"
        if (isalpha(variaveis[0][0]) == 0 || strcmp(variaveis[0], "return") == 0) {
            goto proxima_linha;  // Move para a próxima linha. Sei que posso usar "continue" ao invés de "goto"
        }

        // Verifica se é uma declaração de variável
        if (strcmp(variaveis[0], "int") == 0 || strcmp(variaveis[0], "double") == 0 || strcmp(variaveis[0], "char") == 0) {
            sscanf(expressao, "%*s %[^;]", variaveis[1]);
            raiz = inserir(raiz, variaveis[1], variaveis[0]); // Armazena na árvore o nome da variável declarada e seu tipo
            goto proxima_linha;
        }

        // Salva as outras variáveis com o cuidado de retirar o ';'
        sscanf(expressao, "%*s %*s %s %s %[^;]", variaveis[1], operador, variaveis[2]);
        
        // Para analisar uma expressão, busca os tipos associados às variáveis na árvore
        for (int i = 0; i < 3; i++) {     
            tipo_encontrado = buscar_tipo(raiz, variaveis[i]);
            if (tipo_encontrado != NULL)
                strcpy(tipos[i], tipo_encontrado);
            else {
                printf("Linha %d: o símbolo %s não foi definido.\n", n_linha, variaveis[i]);
                erro = 1;
                goto proxima_linha;
            }
        }
        
        // Verifica se os tipos nas expressões são compatíveis
        if (strcmp(tipos[1], tipos[2]) != 0) {
            printf("Linha %d: tipos incompatíveis: %s (%s) %s %s (%s).\n", n_linha, variaveis[1], tipos[1], operador, variaveis[2], tipos[2]);
            erro = 1;
            goto proxima_linha;
        }
        
        // Verifica se o tipo esperado é igual ao tipo obtido
        if (strcmp(tipos[0], tipos[1]) != 0) {
            printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n",n_linha, variaveis[0], tipos[0], tipos[1]);
            erro = 1;
            goto proxima_linha;
        }
    }

    // Imprime mensagem caso tenha ausência de erros de tipo
    if (erro == 0)
        printf("Não há erros de tipo.\n");

    // Imprime as variáveis e seus tipos em ordem alfabética (inordem na árvore)
    arvore_inordem(raiz);

    // Libera a memória alocada pela árvore
    liberar_arvore(raiz);
    
    return 0;
}