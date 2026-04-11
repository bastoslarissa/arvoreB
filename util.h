#ifndef UTIL_H_
#define UTIL_H_

#include <stdint.h>
#include "arvoreB.h"

// estrutura elementos da fila
struct filaNodo {
    struct nodo* nodoT;
    struct filaNodo* prox;
};

// estrutura controle da fila
struct fila {
    struct fila* inicio;
    struct fila* fim;
};

// funções úteis
void encerraProgFaltaMemoria();
struct nodo* alocarNodo(int32_t t_arvore);

//funções da fila
struct fila* criaFila();
void enfileirar(struct fila* f, struct nodo* n);
struct nodo* desenfileirar(struct fila* f);
int32_t filaVazia(struct fila* f);
void destroiFila(struct fila* f);

#endif