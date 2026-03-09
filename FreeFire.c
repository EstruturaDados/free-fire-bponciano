#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Critérios de ordenação
enum CriterioOrdenacao {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
};

// Estrutura do item
struct Item {
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
};

struct Item mochila[MAX_ITENS];
int totalItens = 0;

// controle de estado para busca binária
bool ordenadoPorNome = false;


// =============================
// ADICIONAR ITEM
// =============================
void adicionarItem() {

    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[totalItens].prioridade);

    totalItens++;

    ordenadoPorNome = false;

    printf("\nItem adicionado!\n");
}


// =============================
// LISTAR ITENS
// =============================
void listarItens() {

    if (totalItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n================ MOCHILA ================\n");
    printf("%-15s %-15s %-10s %-10s\n","Nome","Tipo","Qtd","Prioridade");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {

        printf("%-15s %-15s %-10d %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}


// =============================
// REMOVER ITEM
// =============================
void removerItem() {

    char nomeBusca[50];
    bool encontrado = false;

    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            encontrado = true;
            printf("\nItem removido.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}


// =============================
// BUSCA SEQUENCIAL
// =============================
void buscarItemSequencial() {

    char nomeBusca[50];
    bool encontrado = false;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d\n", mochila[i].prioridade);

            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}


// =============================
// ORDENAÇÃO (INSERTION SORT)
// =============================
void ordenarItens() {

    int criterio;
    int comparacoes = 0;

    printf("\nOrdenar por:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("Escolha: ");
    scanf("%d", &criterio);

    for (int i = 1; i < totalItens; i++) {

        struct Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {

            int resultado = 0;

            if (criterio == ORDENAR_NOME) {
                resultado = strcmp(mochila[j].nome, chave.nome);
            }
            else if (criterio == ORDENAR_TIPO) {
                resultado = strcmp(mochila[j].tipo, chave.tipo);
            }
            else if (criterio == ORDENAR_PRIORIDADE) {
                resultado = mochila[j].prioridade - chave.prioridade;
            }

            comparacoes++;

            if (resultado > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }

        mochila[j + 1] = chave;
    }

    if (criterio == ORDENAR_NOME)
        ordenadoPorNome = true;
    else
        ordenadoPorNome = false;

    printf("\nItens ordenados!\n");
    printf("Comparações realizadas: %d\n", comparacoes);
}


// =============================
// BUSCA BINÁRIA
// =============================
void buscaBinaria() {

    if (!ordenadoPorNome) {
        printf("\nA mochila precisa estar ordenada por NOME para busca binária.\n");
        return;
    }

    char nomeBusca[50];

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int inicio = 0;
    int fim = totalItens - 1;

    while (inicio <= fim) {

        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {

            printf("\nItem encontrado:\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }

        if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem não encontrado.\n");
}


// =============================
// MENU
// =============================
int main() {

    int opcao;

    do {

        printf("\n========== MENU ==========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (sequencial)\n");
        printf("5 - Ordenar itens\n");
        printf("6 - Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                adicionarItem();
                break;

            case 2:
                removerItem();
                break;

            case 3:
                listarItens();
                break;

            case 4:
                buscarItemSequencial();
                break;

            case 5:
                ordenarItens();
                break;

            case 6:
                buscaBinaria();
                break;

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpção inválida.\n");
        }

    } while(opcao != 0);

    return 0;
}