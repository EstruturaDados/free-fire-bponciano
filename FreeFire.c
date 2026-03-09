#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10

// Estrutura do item
struct Item {
    char nome[50];
    char tipo[50];
    int quantidade;
};

// Vetor de itens
struct Item mochila[MAX_ITENS];
int totalItens = 0;

// Função para adicionar item
void adicionarItem() {

    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\nNome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);

    totalItens++;

    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem() {

    char nomeBusca[50];
    int encontrado = 0;

    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {

        if (strcmp(mochila[i].nome, nomeBusca) == 0) {

            // desloca os itens para fechar o espaço
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            encontrado = 1;

            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}

// Função para listar itens
void listarItens() {

    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n===== ITENS DA MOCHILA =====\n");
    printf("%-20s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-20s %-20s %-10d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Função principal
int main() {

    int opcao;

    do {

        printf("\n===== MENU MOCHILA =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
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

            case 0:
                printf("\nEncerrando programa...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while(opcao != 0);

    return 0;
}