#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMANDOMAX 10
#define LIVROMAX 46
#define LINHAMAX 56

//cria um ponteiro para a struct _no
typedef struct _no *p_no;

// struct para criar a lista ligada que recebe o nome do livro
struct _no{
    char livro[LINHAMAX];
    p_no prox;
};

// função que adiciona o nome do livro na lista na posição desejada
p_no adicionar_livro(p_no lista, char livro[], int lugar);

// função para remover um livro da lista
p_no remover_livro(p_no lista, char livro[]);

// função para imprimir a lista de livros
void imprimir_livros(p_no lista);

// função para desalocar a memória da lista ligada
void destruir_lista(p_no lista);


int main(void)
{
    p_no lista = NULL;  // inicia a lista ligada
    char linha[LINHAMAX];
    char comando[COMANDOMAX];  // armazena o comando
    char livro[LIVROMAX];  // armazena o nome do livro
    char ultimo_livro[LIVROMAX];
    int n_livros = 0;  // armazena a quantidade de livros presente na lista
    int lugar = 0;  // armazena qual posição o livro deverá ser adicionado na lista

    while (fgets(linha, sizeof(linha), stdin) != NULL)
    {
        sscanf(linha, "%s %[^\n]", comando, livro);  // separa o comando do nome do livro
        if (!strcmp(comando, "adicionar")) {
            lista = adicionar_livro(lista, livro, lugar);
            strcpy(ultimo_livro, livro);  // recebe o nome do último livro adicionado para analise do comando "remover"
            n_livros ++;
            lugar ++;  // aumenta a variável pois o próximo livro sempre deve vir à direita do último adicionado
        }
        else if (!strcmp(comando, "inicio")) {
            lugar = 0;  // quando comando início, o próximo livro deve ser adicionado na primeira posição da lista
        }
        else if (!strcmp(comando, "final")) {
            lugar = n_livros;  // quando comando final, o próximo livro deve ser adicionado na última posição da lista
        }
        else if (!strcmp(comando, "remover")) {
            lista = remover_livro(lista, livro);
            n_livros --;  // remove um livro da lista
            if (!strcmp(livro, ultimo_livro))
                lugar --;  // se o livro a ser retirado foi o último adicionado o próximo entra no lugar deste
        }
        else if (!strcmp(comando, "imprimir")) {
            imprimir_livros(lista);
        }
    }
    
    destruir_lista(lista);

    return 0;
}


p_no adicionar_livro(p_no lista, char livro[], int lugar)
{
    p_no nova;  // nó de controle
    nova = malloc(sizeof(struct _no));
    strcpy(nova->livro, livro);

    if (lugar == 0) {
        nova->prox = lista; // adiciona o livro no início da lista
        return nova;
    }

    // caso contrário, encontra a posição correta para adicionar o livro
    p_no atual = lista;
    p_no anterior = NULL;
    int posicao = 0;

    // percorre a lista até encontrar a posição desejada ou o final da lista
    while (atual != NULL && posicao < lugar) {
        anterior = atual;
        atual = atual->prox;
        posicao++;
    }

    // insere o livro na posição desejada
    nova->prox = atual;
    if (anterior != NULL) {
        anterior->prox = nova;
        return lista; // retorna a lista original com a alteração
    } else {
        return nova; // se anterior for NULL, significa que o livro foi inserido no início
    }
}


p_no remover_livro(p_no lista, char livro[])
{
    p_no atual = lista;
    p_no anterior = NULL;

    // percorre a lista para encontrar o livro
    while (atual != NULL) {
        if (!strcmp(atual->livro, livro)) {
            // ao encontrar o livro, os ponteiros são ajustados para remover o nó
            if (anterior == NULL) {
                // o livro a ser removido é o primeiro da lista
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual); // libera a memória do nó
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return lista;
}


void imprimir_livros(p_no lista)
{ 
    p_no atual;  // nó de controle
    for (atual = lista; atual != NULL; atual = atual->prox)
    {
        printf("%s", atual ->livro);
        if (atual->prox != NULL) {
            printf(", ");  //imprimir uma vírgula e um espaço se não for o último livro
        }
    }
    printf("\n");
}


void destruir_lista(p_no lista)
{
    if (lista != NULL) {  // função recursiva que vai dando free até o último elemento da lista
        destruir_lista(lista->prox); 
        free(lista);
    }
}
