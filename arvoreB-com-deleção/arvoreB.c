#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "util.h"

// aloca uma struct do tipo arvoreB com um valor t específico e retorna.
struct arvoreB* criarArvoreB(int32_t t_arvore) {
  struct arvoreB* T = malloc(sizeof(struct arvoreB));
  if (!T) {
    encerraProgFaltaMemoria();
  }

  struct nodo* x = alocarNodo(t_arvore);
  T->raiz = x;
  T->t_arvore = t_arvore;

  return T;
}

// insere um novo elemento na árvore
void inserirArvoreB(struct arvoreB* arvore, int32_t chave) {
  struct nodo* r = arvore->raiz;

  if (r->n == (2*(arvore->t_arvore)-1)) {
    struct nodo* s = dividirRaiz(arvore);
    inserirNaoCheio(s, chave, arvore->t_arvore);
  }
  else {
    inserirNaoCheio(r, chave, arvore->t_arvore);
  }

}
//remove uma chave, se foi removida, retorna verdadeiro. Caso contrário, retorna falso
//caso 1 é tratado dentro dessa função (caso o nodo excluido esta em uma folha)
bool removerChaveArvoreB(struct arvoreB* arvore, int32_t chave) {
  // comeca na raiz 
  struct nodo* x = arvore->raiz;

  int32_t i = 0;
  // percorre o nodo
  while ((i < x->n) && (chave > x->chaves[i])) {
    i++;
  }
  // se achou a chave
  if ((i < x->n) && (chave == x->chaves[i])){
    if(x->ehFolha) { //se for uma folha só exclui
      removeFolha(x,i);
      return true;
    } //adicionar os outros casos aqui 

  //se não achou e é folha
  } else {
    if (x->ehFolha)
      return false;
  }
  return removerChaveArvoreB(arvore, chave);
}

// imprime a árvore B na tela em largura.
void imprimirArvoreB(struct arvoreB* arvore) {
  if(!arvore->raiz) {
    return;
  }

  struct fila* f = criaFila();
  enfileirar(f, arvore->raiz);
  int32_t nivel = 0;

  while (!filaVazia(f)) {
    printf("----//----\nNivel %d\n----//----\n", nivel);

    // contagem de nodos no nível atual para saber quando pular pra o prox
    int32_t nodosNivel = 0;
    struct filaNodo* temp = f->inicio;
    while (temp) {
      nodosNivel++;
      temp = temp->prox;
    }

    //imprime na tela os nodos e suas respectivas chaves do nível
    for (int i = 0; i < nodosNivel;i++) {
      struct nodo* atual = desenfileirar(f);

      printf("%c (n:%d) [", (atual->ehFolha ? 'F' : 'I'), atual->n);
      // percorre as chaves do nodo
      for (int j = 0; j < atual->n; j++) {
        printf("%d%s", atual->chaves[j], (j < atual->n - 1 ? " " : ""));
      }
      printf("]");

      if (i < (nodosNivel - 1)) {
        printf(" ");
      }
      // se for interno enfilera filhos
      if (!atual->ehFolha) {
        for (int j = 0; j <= atual->n; j++) {
          enfileirar(f, atual->filhos[j]);
        }
      }
    }
    printf("\n");
    // desce de nível
    nivel++;
  }
  destroiFila(f);
}

// imprime a arvore B na tela em ordem
void imprimirEmOrdem(struct arvoreB* arvore) {
  if (arvore == NULL || arvore->raiz == NULL) {
    printf("Árvore vazia\n");
    return;
  }

  imprimeNodo(arvore->raiz);
  printf("\n");
}


// retorna o endereço do nodo que contém a chave buscada, caso contrário retorna NULL.
// índice de onde a chave se encontra é inserido em idxEncontrado.
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado) {
  // comeca na raiz
  struct nodo* x = arvore->raiz;

  while (x != NULL) {
    int i = 0;

    // percorre o nodo
    while ((i < x->n) && (chave > x->chaves[i])) {
      i++;
    }
    // se achou a chave
    if ((i < x->n) && (chave == x->chaves[i])) {
      *idxEncontrado = i;
      return x; 
    } else if (x->ehFolha) { // se não achou e é folha
      break;
    }
    // desce para o prox nível
    x = x->filhos[i];
  }
  // não achou
  *idxEncontrado = -1;
  return NULL;
}

void deletarArvore(struct arvoreB* arvore) {
  liberarArvoreB(arvore->raiz);
  free(arvore);
}