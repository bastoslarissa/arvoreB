#include <stddef.h>
#include "arvoreB.h"

//subfuncoes para operacoes necessarias para as funcoes basicas

// Término do programa em caso de falta de memória.
void EncerraProgramaFaltaMemoria() {
  fprint(stderr, "Falha ao alocar memória.\n");
  exit(1);
}


// Aloca uma struct do tipo arvoreB com um valor T específico e retorna.
struct arvoreB* criarArvoreB(int32_t t_arvore) {

}

// Imprime a árvore B na tela em largura.
void imprimirArvoreB(struct arvoreB* arvore) {
  
}

// Retorna o endereço do nodo que contém a chave buscada, caso contrário retorna NULL.
// Índice de onde a chave se encontra é inserido em idxEncontrado.
union ou struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado) {


}