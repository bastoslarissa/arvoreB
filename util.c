#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "util.h"

//---------------------- Funções auxiliares -------------------------

// término do programa em caso de falta de memória.
void encerraProgFaltaMemoria() {
  fprintf(stderr, "Falha ao alocar memória.\n");
  exit(1);
}

// reserva memória para o nodo, retorna erro e encerra o programa caso falte memória.
struct nodo* alocarNodo(int32_t t_arvore) {
  struct nodo* novoNodo = malloc(sizeof(struct nodo));
  if (!novoNodo) {
    encerraProgFaltaMemoria();
  }

  // aloca o vetor de chaves conforme a regra de árvores B
  novoNodo->chaves = malloc((2 * t_arvore -1) * sizeof(int32_t));
  if (!novoNodo->chaves){
    encerraProgFaltaMemoria();
  }

  // aloca vetor de ponteiros para os filhos seguindo as regras de árvore B
  novoNodo->filhos = malloc((2 * t_arvore) * sizeof(struct nodo));
  if (!novoNodo->filhos) {
    encerraProgFaltaMemoria();
  }

  //fazer todos os ponteiros apontarem para NULL para evitar segfault
  for (int i = 0; i < (2 * t_arvore); i++) {
    novoNodo->filhos[i] = NULL;
  }

  //inicializa campos do novo nodo
  novoNodo->ehFolha = true;
  novoNodo->n = 0;

  return novoNodo;
}

//--------------- Funções para operações com fila ------------------

// cria uma nova fila para o percurso em largura
struct fila* criaFila() {
  struct fila* novaFila = malloc(sizeof(struct fila));
  if(!novaFila) {
    encerraProgFaltaMemoria();
  }
  novaFila->inicio = NULL;
  novaFila->fim = NULL;

  return novaFila;
}

// insere um nodo na fila 
void enfileirar(struct fila* f, struct nodo* n) {
  if (!f || !n) 
    return;

  //cria um novo item
  struct filaNodo* novo = malloc(sizeof(struct filaNodo));
  if (!novo) {
    encerraProgFaltaMemoria();
  }
  novo->nodoT = n;
  novo->prox = NULL;

  // se a fila estiver vazia, insere no inicio
  if (!f->inicio) {
    f->inicio = novo;
  } else {
    // caso contrario, encontra o ultimo nodo da fila e insere
    struct filaNodo* atual = f->inicio;
    while (atual->prox)
        atual = atual->prox;

    atual->prox = novo;
  }

}

// retira o primeiro item da fila e o devolve
//TERMINAR
struct nodo* desenfileirar(struct fila* f) {
  if(!f || !f->inicio)
    return;
}

int32_t filaVazia(struct fila* f) {
    return (f->inicio == NULL);
}

void destroiFila(struct fila* f) {
    while (!filaVazia(f))
        desenfileirar(f);
    free(f);
}
