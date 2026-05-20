#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "arvoreB.h"

/* -------------------- Funções auxiliares da main -------------------- */

static void mostrarBusca(struct arvoreB* arvore, int32_t chave) {
    int32_t idx = -1;
    struct nodo* nodoEncontrado = buscarArvoreB(arvore, chave, &idx);

    if (nodoEncontrado) {
        printf("Busca %d: ENCONTRADA no índice %d do nodo [", chave, idx);

        for (int i = 0; i < nodoEncontrado->n; i++) {
            printf("%d%s",
                   nodoEncontrado->chaves[i],
                   i < nodoEncontrado->n - 1 ? " " : "");
        }

        printf("]\n");
    } else {
        printf("Busca %d: NÃO ENCONTRADA\n", chave);
    }
}

static void removerEImprimir(struct arvoreB* arvore, int32_t chave) {
    printf("\n--------------------------------------------------\n");
    printf("Removendo %d...\n", chave);
    printf("--------------------------------------------------\n");

    bool removeu = removerChaveArvoreB(arvore, chave);

    if (removeu) {
        printf("Chave %d removida com sucesso.\n", chave);
    } else {
        printf("Chave %d não foi encontrada.\n", chave);
    }

    printf("\nÁrvore em largura:\n");
    imprimirArvoreB(arvore);

    printf("\nÁrvore em ordem:\n");
    imprimirEmOrdem(arvore);
}

/* ------------------------------ MAIN ------------------------------ */

int main(void) {

    printf("\n==================================================\n");
    printf("TESTE GERAL - ÁRVORE B COM DELEÇÃO\n");
    printf("==================================================\n");

    struct arvoreB* arvore = criarArvoreB(3);

    /* ============================================================
       TESTE 1: INSERÇÕES
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 1 - INSERÇÕES\n");
    printf("==================================================\n");

    int32_t chavesInserir[] = {
        10, 20, 5, 6, 12, 30, 7, 17,
        3, 4, 2, 1, 8, 9, 11, 13,
        14, 15, 16, 18, 19, 21, 22,
        23, 24, 25
    };

    int qtdInsercoes = sizeof(chavesInserir) / sizeof(chavesInserir[0]);

    for (int i = 0; i < qtdInsercoes; i++) {
        inserirArvoreB(arvore, chavesInserir[i]);
    }

    printf("\nÁrvore após as inserções:\n");
    imprimirArvoreB(arvore);

    printf("\nImpressão em ordem:\n");
    imprimirEmOrdem(arvore);


    /* ============================================================
       TESTE 2: BUSCAS
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 2 - BUSCAS\n");
    printf("==================================================\n");

    mostrarBusca(arvore, 1);
    mostrarBusca(arvore, 10);
    mostrarBusca(arvore, 17);
    mostrarBusca(arvore, 25);
    mostrarBusca(arvore, 99);


    /* ============================================================
       TESTE 3: REMOÇÃO DE CHAVE EM FOLHA
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 3 - REMOÇÃO DE CHAVE EM FOLHA\n");
    printf("==================================================\n");

    removerEImprimir(arvore, 25);


    /* ============================================================
       TESTE 4: REMOÇÃO DE CHAVE INTERNA
       Dependendo da estrutura, deve usar predecessor,
       sucessor ou merge.
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 4 - REMOÇÃO DE CHAVE INTERNA\n");
    printf("==================================================\n");

    removerEImprimir(arvore, 12);


    /* ============================================================
       TESTE 5: REMOÇÕES SUCESSIVAS
       Devem provocar redistribuições e merges.
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 5 - REMOÇÕES SUCESSIVAS\n");
    printf("==================================================\n");

    int32_t chavesRemover[] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        9, 10, 11, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24
    };

    int qtdRemocoes = sizeof(chavesRemover) / sizeof(chavesRemover[0]);

    for (int i = 0; i < qtdRemocoes; i++) {
        removerEImprimir(arvore, chavesRemover[i]);
    }


    /* ============================================================
       TESTE 6: REMOÇÃO DE CHAVE INEXISTENTE
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 6 - REMOÇÃO DE CHAVE INEXISTENTE\n");
    printf("==================================================\n");

    removerEImprimir(arvore, 999);


    /* ============================================================
       TESTE 7: BUSCAS APÓS AS REMOÇÕES
       ============================================================ */

    printf("\n==================================================\n");
    printf("TESTE 7 - BUSCAS APÓS REMOÇÕES\n");
    printf("==================================================\n");

    mostrarBusca(arvore, 1);
    mostrarBusca(arvore, 12);
    mostrarBusca(arvore, 25);
    mostrarBusca(arvore, 999);


    /* ============================================================
       FINALIZAÇÃO
       ============================================================ */

    deletarArvore(arvore);

    printf("\n==================================================\n");
    printf("FIM DOS TESTES\n");
    printf("==================================================\n");

    return 0;
}