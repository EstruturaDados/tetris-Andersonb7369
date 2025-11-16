#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_MAX 5
#define NUM_TIPOS 5

const char *tipos[] = {"O", "I", "T", "L", "Z"};

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

// - Crie uma struct Peca com os campos: tipo (char) e id (int).
typedef struct {
    char tipo[20];
    int id;
} Peca;

// - Implemente uma fila circular com capacidade para 5 peças.
typedef struct {
    Peca p[TAM_MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().

//verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == TAM_MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

// Insere um novo item no final da fila
void inserir(Fila *f, Peca p) { // Recebe a fila e a Pessoa p que vai ser inserida
    if (f->total == TAM_MAX) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
 
    f->p[f->fim] = p; // Adiciona a pessoa no fim da fila
    f->fim = (f->fim + 1) % TAM_MAX; // logica circular da fila
    f->total++; // Atualiza o total de itens
}

// remove o elemento da frente da fila
void remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->p[f->inicio];   // Remove o primeiro item da lista          
    f->inicio = (f->inicio + 1) % TAM_MAX;  // atualiza os indices de inicio.
    f->total--; // Atualiza o total da lista depois da remoção       
}

// - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
Peca gerarPeca(int id) {
    Peca nova;
    nova.id = id;

    int indice = rand() % NUM_TIPOS; // número aleatório entre 0 e NUM_TIPOS-1
    strcpy(nova.tipo, tipos[indice]);

    return nova;
}

// - Exiba a fila após cada ação com uma função mostrarFila().
void exibirFila(Fila *f) {
    printf("\nFila: ");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % TAM_MAX) {
        printf("[%s, %d] ", f->p[idx].tipo, f->p[idx].id);
    }
    printf("\n");
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras

    Fila fila;
    inicializarFila(&fila);
    srand(time(NULL)); // inicializa gerador aleatório

    int opcao, contadorID = 1;
    Peca temp;

    // Preenche a fila inicialmente
    while (!filaCheia(&fila)) {
        inserir(&fila, gerarPeca(contadorID++));
    }
    exibirFila(&fila);
    do {
        printf("\n=== MENU TETRIS STACK ===\n\n");
        printf("1 - Jogar peça (remover da frente)\n");
        printf("0 - Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                remover(&fila, &temp);
                inserir(&fila, gerarPeca(contadorID++)); // - A cada remoção, insere uma nova peça ao final da fila
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

        exibirFila(&fila);

    } while (opcao != 0);

    return 0;
}

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
