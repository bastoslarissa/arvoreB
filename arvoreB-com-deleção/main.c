#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "arvoreB.h"

static void mostrarArvore(struct arvoreB *arvore) {
  printf("\nÁrvore em largura:\n");
  imprimirArvoreB(arvore);

  printf("\nÁrvore em ordem:\n");
  imprimirEmOrdem(arvore);
  printf("\n");
}

static void testarBusca(struct arvoreB *arvore, int32_t chave) {
  int32_t indice = -1;
  struct nodo *nodoEncontrado = buscarArvoreB(arvore, chave, &indice);

  if (nodoEncontrado != NULL) {
    printf("Busca %d: ENCONTRADA no índice %d do nodo [", chave, indice);

    for (int i = 0; i < nodoEncontrado->n; i++) {
      printf("%d", nodoEncontrado->chaves[i]);

      if (i < nodoEncontrado->n - 1) {
        printf(" ");
      }
    }

    printf("]\n");
  }
  else {
    printf("Busca %d: NÃO ENCONTRADA\n", chave);
  }
}

static void removerEImprimir(struct arvoreB *arvore, int32_t chave) {
  printf("\n--------------------------------------------------\n");
  printf("Removendo %d...\n", chave);
  printf("\n--------------------------------------------------\n");

  if (removerChaveArvoreB(arvore, chave)) {
    printf("Chave %d removida com sucesso.\n", chave);
  }
  else {
    printf("Chave %d não foi encontrada.\n", chave);
  }

  mostrarArvore(arvore);
}

int main(void) {
  struct arvoreB *arvore = criarArvoreB(3);

  int32_t chavesInsercao[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 18,
    19, 20, 21, 22, 23, 24, 25, 30
  };

  int32_t buscasIniciais[] = {1, 10, 17, 25, 99};

  int32_t remocoes[] = {
    25, 12,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
    11, 13, 14, 15, 16, 17, 18, 19,
    20, 21, 22, 23, 24
  };

  int32_t buscasFinais[] = {1, 12, 25, 999};

  int qtdInsercoes = sizeof(chavesInsercao) / sizeof(chavesInsercao[0]);
  int qtdBuscasIniciais = sizeof(buscasIniciais) / sizeof(buscasIniciais[0]);
  int qtdRemocoes = sizeof(remocoes) / sizeof(remocoes[0]);
  int qtdBuscasFinais = sizeof(buscasFinais) / sizeof(buscasFinais[0]);

  printf("==================================================\n");
  printf("TESTE GERAL - ÁRVORE B COM DELEÇÃO\n");
  printf("==================================================\n");

  printf("\n==================================================\n");
  printf("TESTE 1 - INSERÇÕES\n");
  printf("==================================================\n");

  for (int i = 0; i < qtdInsercoes; i++) {
    inserirArvoreB(arvore, chavesInsercao[i]);
  }

  printf("\nÁrvore após as inserções:\n");
  imprimirArvoreB(arvore);

  printf("\nImpressão em ordem:\n");
  imprimirEmOrdem(arvore);
  printf("\n");

  printf("\n==================================================\n");
  printf("TESTE 2 - BUSCAS\n");
  printf("==================================================\n");

  for (int i = 0; i < qtdBuscasIniciais; i++) {
    testarBusca(arvore, buscasIniciais[i]);
  }

  printf("\n==================================================\n");
  printf("TESTE 3 - REMOÇÕES\n");
  printf("==================================================\n");

  for (int i = 0; i < qtdRemocoes; i++) {
    removerEImprimir(arvore, remocoes[i]);
  }

  printf("\n==================================================\n");
  printf("TESTE 4 - REMOÇÃO DE CHAVE INEXISTENTE\n");
  printf("==================================================\n");

  removerEImprimir(arvore, 999);

  printf("\n==================================================\n");
  printf("TESTE 5 - BUSCAS APÓS REMOÇÕES\n");
  printf("==================================================\n");

  for (int i = 0; i < qtdBuscasFinais; i++) {
    testarBusca(arvore, buscasFinais[i]);
  }

  printf("\n==================================================\n");
  printf("FIM DOS TESTES\n");
  printf("==================================================\n");

  deletarArvore(arvore);

    return 0;

}