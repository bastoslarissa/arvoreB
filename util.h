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
    struct filaNodo* inicio;
    struct filaNodo* fim;
};

// funções úteis
void encerraProgFaltaMemoria();
struct nodo* alocarNodo(int32_t t_arvore);
void dividirFilho (struct nodo* x, int i, int32_t t_arvore);
struct nodo* dividirRaiz (struct arvoreB* arvore);
void inserirNaoCheio (struct nodo* x, int32_t chave, int32_t t_arvore);
void imprimeNodo (struct nodo* x);

//funções da fila
struct fila* criaFila();
void enfileirar(struct fila* f, struct nodo* n);
struct nodo* desenfileirar(struct fila* f);
int32_t filaVazia(struct fila* f);
void destroiFila(struct fila* f);

#endif