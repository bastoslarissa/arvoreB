#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>

// como trabalhar com o grau maximo aqui?

union ou struct nodo {
  //defina
};

// preciso mexer aqui?
struct arvoreB {
  union ou struct nodo* raiz;
  int32_t t_arvore;
};

struct arvoreB* criarArvoreB(int32_t t_arvore);
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore);
union ou struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado);
void deletarArvore(struct arvoreB* arvore);

#endif