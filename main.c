#include <stdio.h>
#include "arvoreB.h"

int main () {

  struct arvoreB* arvore = criarArvoreB(3);  // grau mínimo = 2

  inserirArvoreB(arvore, 10);
  inserirArvoreB(arvore, 20);
  inserirArvoreB(arvore, 5);
  inserirArvoreB(arvore, 6);
  inserirArvoreB(arvore, 12);
}