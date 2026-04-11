#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"

//subfuncoes para operacoes necessarias para as funcoes basicas

// término do programa em caso de falta de memória.
void encerraProgFaltaMemoria() {
  fprintf(stderr, "Falha ao alocar memória.\n");
  exit(1);
}

// reserva memória para o nodo, retorna erro e encerra o programa caso falte memória.
struct nodo* alocarNodo(int32_t t_arvore) {
  struct nodo* novoNodo = malloc(sizeof(struct nodo));
  if(novoNodo == NULL) {
    encerraProgFaltaMemoria();
  }

  // aloca o vetor de chaves conforme a regra de árvores B
  novoNodo->chaves = malloc((2 * t_arvore -1) * sizeof(int32_t));
  if(novoNodo->chaves == NULL){
    encerraProgFaltaMemoria();
  }

  // aloca vetor de ponteiros para os filhos seguindo as regras de árvore B
  novoNodo->filhos = malloc((2 * t_arvore) * sizeof(struct nodo));
  if(novoNodo->filhos == NULL) {
    encerraProgFaltaMemoria();
  }

  //fazer todos os ponteiros apontarem para NULL para evitar segfault
  for(int i = 0; i < (2 * t_arvore); i++) {
    novoNodo->filhos[i] = NULL;
  }

  //inicializa campos do novo nodo
  novoNodo->ehFolha = true;
  novoNodo->n = 0;

  return novoNodo;
}

// aloca uma struct do tipo arvoreB com um valor t específico e retorna.
struct arvoreB* criarArvoreB(int32_t t_arvore) {
  struct arvoreB* T = malloc(sizeof(struct arvoreB));
  if(T == NULL) {
    encerraProgFaltaMemoria();
  }

  struct nodo* x = alocarNodo(t_arvore);
  T->raiz = x;
  T->t_arvore = t_arvore;

  return T;
}

// imprime a árvore B na tela em largura.
void imprimirArvoreB(struct arvoreB* arvore) {
  
}

// retorna o endereço do nodo que contém a chave buscada, caso contrário retorna NULL.
// índice de onde a chave se encontra é inserido em idxEncontrado.
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado) {


}