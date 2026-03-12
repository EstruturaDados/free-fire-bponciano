#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

// estrutura do item da mochila
struct Item{
    char nome[50];
    char tipo[50];
    int quantidade;
    int prioridade;
};

// vetor da mochila
struct Item mochila[MAX_ITENS];
int totalItens = 0;

// controle para saber se está ordenado por nome
bool ordenadoNome = false;


// ------------------------
// ADICIONAR ITEM
// ------------------------
void adicionarItem(){

    if(totalItens >= MAX_ITENS){
        printf("\nA mochila está cheia!\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", mochila[totalItens].nome);

    printf("Digite o tipo do item: ");
    scanf(" %[^\n]", mochila[totalItens].tipo);

    printf("Quantidade: ");
    scanf("%d",&mochila[totalItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d",&mochila[totalItens].prioridade);

    totalItens++;

    ordenadoNome = false;

    printf("\nItem adicionado com sucesso!\n");
}


// ------------------------
// LISTAR ITENS
// ------------------------
void listarItens(){

    if(totalItens == 0){
        printf("\nNão tem itens na mochila.\n");
        return;
    }

    printf("\n======= ITENS NA MOCHILA =======\n");

    for(int i = 0; i < totalItens; i++){

        printf("\nItem %d\n", i+1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
        printf("Prioridade: %d\n", mochila[i].prioridade);
    }
}


// ------------------------
// REMOVER ITEM
// ------------------------
void removerItem(){

    char nomeBusca[50];
    int achou = 0;

    printf("\nDigite o nome do item que quer remover: ");
    scanf(" %[^\n]", nomeBusca);

    for(int i = 0; i < totalItens; i++){

        if(strcmp(mochila[i].nome, nomeBusca) == 0){

            for(int j = i; j < totalItens - 1; j++){
                mochila[j] = mochila[j+1];
            }

            totalItens--;
            achou = 1;

            printf("\nItem removido!\n");
            break;
        }
    }

    if(!achou){
        printf("\nItem não encontrado.\n");
    }
}


// ------------------------
// BUSCA SEQUENCIAL
// ------------------------
void buscaSequencial(){

    char nomeBusca[50];
    int achou = 0;

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    for(int i = 0; i < totalItens; i++){

        if(strcmp(mochila[i].nome, nomeBusca) == 0){

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d\n", mochila[i].prioridade);

            achou = 1;
            break;
        }
    }

    if(!achou){
        printf("\nItem não encontrado.\n");
    }
}


// ------------------------
// ORDENAR (INSERTION SORT)
// ------------------------
void ordenarItens(){

    int opcao;

    printf("\nOrdenar por:\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Prioridade\n");
    printf("Escolha: ");
    scanf("%d",&opcao);

    for(int i = 1; i < totalItens; i++){

        struct Item aux = mochila[i];
        int j = i - 1;

        while(j >= 0){

            int comparar = 0;

            if(opcao == 1){
                comparar = strcmp(mochila[j].nome, aux.nome);
            }
            else if(opcao == 2){
                comparar = strcmp(mochila[j].tipo, aux.tipo);
            }
            else if(opcao == 3){
                comparar = mochila[j].prioridade - aux.prioridade;
            }

            if(comparar > 0){
                mochila[j+1] = mochila[j];
                j--;
            }
            else{
                break;
            }
        }

        mochila[j+1] = aux;
    }

    if(opcao == 1)
        ordenadoNome = true;
    else
        ordenadoNome = false;

    printf("\nItens ordenados!\n");
}


// ------------------------
// BUSCA BINARIA
// ------------------------
void buscaBinaria(){

    if(!ordenadoNome){
        printf("\nPrimeiro ordene por NOME para usar busca binária.\n");
        return;
    }

    char nomeBusca[50];

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int inicio = 0;
    int fim = totalItens - 1;

    while(inicio <= fim){

        int meio = (inicio + fim) / 2;

        int resultado = strcmp(mochila[meio].nome, nomeBusca);

        if(resultado == 0){

            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);

            return;
        }

        if(resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nItem não encontrado.\n");
}


// ------------------------
// MAIN
// ------------------------
int main(){

    int op;

    do{

        printf("\n====== MENU ======\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("5 - Ordenar itens\n");
        printf("6 - Busca binaria\n");
        printf("0 - Sair\n");

        printf("Escolha: ");
        scanf("%d",&op);

        switch(op){

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
                buscaSequencial();
                break;

            case 5:
                ordenarItens();
                break;

            case 6:
                buscaBinaria();
                break;

            case 0:
                printf("\nSaindo do programa...\n");
                break;

            default:
                printf("\nOpcao invalida\n");
        }

    }while(op != 0);

    return 0;
}