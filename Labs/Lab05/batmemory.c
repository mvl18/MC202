#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PALAVRAMAX 10

//cria um ponteiro para a struct _vetor
typedef struct _vetor *p_vetor;

// cria a struct que salvará os dados para o batman
struct _vetor{
    int *dados;
    int alocado;
    int utilizado;
};

//função para alocar o vetor com espaço de 8 inteiros
p_vetor alocar_vetor();

//função para desalocar o vetor do batmemory
void desalocar_vetor();

// função para descobrir o primeiro espaço na memória em que será possível fazer bat-alloc
int bat_local(int quantidade, p_vetor memoria);

// função para duplicar o espaço alocado do vetor do batmemory caso não haja espaço para fazer bat-alloc
void bat_duplica(p_vetor memoria);

// função para reduzir pela metade o vetor do batmemory, caso apenas o primeiro 1/4 do vetor esteja sendo utilizado
void bat_reduz(p_vetor memoria);

// função que passará uma lista de inteiros para serem alocados na batmemory
void bat_alloc(p_vetor memoria);

// função para desalocar uma determinada lista da batmemory
void bat_free(p_vetor memoria);

// função para imprimir alguma lista alocada na batmemory
void bat_print(p_vetor memoria);

// função para saber quantos espaços de memória estão em uso do total alocado pela batmemory
void bat_uso(p_vetor memoria);


int main(void)
{   
    p_vetor memoria;
    int n_comandos;
    char comando[PALAVRAMAX];
    scanf("%d", &n_comandos);  // recebe o número de comandos realizados pelo batman
    memoria = alocar_vetor();  // inicia a memória do batmemory

    for (int i = 0; i < n_comandos; i++)
    {   // verifica qual dos comandos foi chamado
        scanf("%s", comando);
        if (!strcmp(comando, "bat-alloc")) {
            bat_alloc(memoria);
        }
        else if (!strcmp(comando, "bat-free")) {
            bat_free(memoria);
        }
        else if (!strcmp(comando, "bat-print")) {
            bat_print(memoria);
        }
        else if (!strcmp(comando, "bat-uso")) {
            bat_uso(memoria);
        }
    }

    desalocar_vetor(memoria);  // desaloca a batmemory

    return 0;
}

void bat_alloc(p_vetor memoria)
{
    int quantidade, valor, inicio;
    scanf("%d ", &quantidade);  // recebe quantos valores fazer parte da lista a ser alocada
    inicio = bat_local(quantidade + 1, memoria);  // verifica em qual posição da memória iremos alocar

    memoria->dados[inicio] = quantidade;  // guardamos o tamanho da lista na memória
    memoria->utilizado += 1;  // alteramos a quantidade de espaços utilizados na batmemory

    for (int i = inicio + 1; i < quantidade + inicio + 1; i++)
    {   // recebe cada um dos elementos da lista e guarda na batmemory
        scanf("%d", &valor);
        memoria->dados[i] = valor;
        memoria->utilizado += 1;
    }

    printf("%d\n", inicio);  // imprime a posição inicial desta lista na batmemory
}

int bat_local(int quantidade, p_vetor memoria)
{
    int inicio, i = 0;
    while (i < memoria->alocado)
    {
        // Indica a primeira posição de memória que está vazia
        if (memoria->dados[i] == 0) {
            inicio = i;
            // Verifica se é necessário aumentar o tamanho da bat-memory quando se tem memoria desalocada no final
            if (i + quantidade > memoria->alocado) {
                int m = inicio;
                for (; m < memoria->alocado - 1; m++)
                    if (memoria->dados[m] != 0)
                        break;

                if (m == memoria->alocado - 1) {
                    bat_duplica(memoria);
                    return inicio;
                }
            }
            // Percorre a batmemory a partir do início encontrado para ver se o espaço é suficiente
            int j;
            for (j = i + 1; j < i + quantidade; j++)
                if (memoria->dados[j] != 0)
                    break; // Saia do loop se encontrar um espaço ocupado

            if (j == i + quantidade)
                return inicio;

            // Caso contrário, continue procurando a partir de onde paramos
            i = j;
        }
        else
            i++;
    }
    // Caso não exista espaço para alocar a lista, iremos duplicar o tamanho da batmemory
    bat_duplica(memoria);
    return (memoria->alocado) / 2;  //passamos como início logo o primeiro espaço de memória da extensão
}

void bat_duplica(p_vetor memoria)
{
    int *breve, antigo;
    antigo = memoria->alocado;
    breve = memoria->dados;

    memoria->alocado *= 2;  // dobra a memória alocada para o batmemory
    memoria->dados = calloc(memoria->alocado, sizeof(int));
    for (int i = 0; i < antigo; i++)
        memoria->dados[i] = breve[i];

    free(breve);  // desaloca o vetor criado para transcrição
}

void bat_free(p_vetor memoria)
{
    int alvo, quantidade, verifica = 0;
    scanf("%d", &alvo);  // espaço de memória que indica o tamanho da lista a ser desalocada
    quantidade = memoria->dados[alvo];
    for (int i = 0; i <= quantidade; i++)
    {
        memoria->dados[i + alvo] = 0;
        memoria->utilizado -= 1;
    }

    if (memoria->alocado > 8) {  // garante que o tamanho da batmemory não seja menor que 8
        for (int i = 0; i < 3 * (memoria->alocado)/4; i++)
            if (memoria->dados[(memoria->alocado)/4 + i] == 0)
                verifica ++;  // verifica se a memória após um quarto da batmemory está desalocada
            else
                break;
        
        if (verifica == 3 * (memoria->alocado)/4)
            bat_reduz(memoria);
    }
}

void bat_reduz(p_vetor memoria)
{
    int *breve, antigo;
    antigo = (memoria->alocado)/4;
    breve = memoria->dados;

    memoria->alocado = (memoria->alocado)/2;  // diminui a memoria alocada pela metade
    memoria->dados = calloc(memoria->alocado, sizeof(int));
    for (int i = 0; i < antigo; i++)
        memoria->dados[i] = breve[i];

    free(breve);  // desaloca o vetor criado para transcrição
}

void bat_print(p_vetor memoria)
{
    int alvo;
    scanf("%d", &alvo);  //recebe a posição que indica o tamanho da lista a ser impressa
    for (int i = 0; i < memoria->dados[alvo]; i++)
        printf("%d ", memoria->dados[i + alvo + 1]);
    
    printf("\n");
}

void bat_uso(p_vetor memoria)
{
    printf("%d de %d\n", memoria->utilizado, memoria->alocado);
}

p_vetor alocar_vetor()
{
    p_vetor v;
    v = malloc(sizeof(struct _vetor));
    v->dados = calloc(8, sizeof(int));
    v->alocado = 8;
    v->utilizado = 0;

    return v;
}

void desalocar_vetor(p_vetor memoria)
{
    free(memoria->dados);
    free(memoria);
}
