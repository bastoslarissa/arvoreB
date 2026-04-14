#include <stdio.h>
#include "arvoreB.h"

int main () {
  struct arvoreB* arvore = criarArvoreB(3);

  printf("Arvore criada\n");

  // ===== INSERÇÃO =====
  int valores[] = {10, 20, 5, 6, 12, 30, 7, 17};
  int n = sizeof(valores) / sizeof(valores[0]);

  for (int i = 0; i < n; i++) {
    printf("Inserindo %d...\n", valores[i]);
    inserirArvoreB(arvore, valores[i]);
  }

  // ===== IMPRIMIR ESTRUTURA =====
  printf("\nEstrutura da arvore:\n");
  imprimirArvoreB(arvore);

  // ===== IMPRIMIR EM ORDEM =====
  printf("\nElementos em ordem:\n");
  imprimirEmOrdem(arvore);
  printf("\n");

  // ===== BUSCAS =====
  int32_t idx;

  int buscas[] = {6, 15, 17, 99};
  int nb = sizeof(buscas) / sizeof(buscas[0]);

  printf("\nTestes de busca:\n");

  for (int i = 0; i < nb; i++) {
    struct nodo* res = buscarArvoreB(arvore, buscas[i], &idx);

    if (res != NULL) {
      printf("Chave %d encontrada no indice %d\n", buscas[i], idx);
    } else {
      printf("Chave %d NAO encontrada\n", buscas[i]);
    }
  }

  return 0;
}