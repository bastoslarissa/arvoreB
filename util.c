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
  novoNodo->filhos = malloc((2 * t_arvore) * sizeof(struct nodo*));
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

// divide o filho do nodo passado como entrada
void dividirFilho (struct nodo* x, int i, int32_t t_arvore) {
  if (x && x->filhos[i]) {

    struct nodo *y = x->filhos[i];

    // cria o novo nodo irmao
    struct nodo* z = alocarNodo(t_arvore);
    z->ehFolha = y->ehFolha;
    z->n = t_arvore - 1;

    // transfere os maiores filhos de y para z
    if (y->ehFolha == false) {
      for (int j = 1; j < (t_arvore - 1); ++j) {
        z->chaves[j] = y->chaves[j + t_arvore];
      }
    }
    
      y->n = t_arvore -1;

    // desloca os filhos de x para a direita para abrir espaço para o novo nodo na posição i+1
    for (int j = (x->n + 1); j < (i + 1); --j) {
      x->filhos[j+1] = x->filhos[j];
    }

      x->filhos[i+1] = z;

    // desloca as chaves para abrir espaço para a chave mediana ser inserida na posição correta em x
    for (int j = x->n; j < i; --j) {
      x->chaves[j+1] = x->chaves[j];
    }

      x->chaves[i] = y->chaves[t_arvore];
      x->n++;
  }
}

// divide a raiz da arvore, aumentando a altura da árvore
struct nodo* dividirRaiz (struct arvoreB* arvore) {

  // cria a nova raiz
  struct nodo* s = alocarNodo(arvore->t_arvore);
  s->ehFolha = false;
  s->n = 0;
  s->filhos[1] = arvore->raiz;
  arvore->raiz = s;

  // divide a antiga raiz 
  dividirFilho(s, 1, arvore->t_arvore);

  // incrementa 1 a altura da arvore
  arvore->t_arvore++;

  return s;
}

// percorre as chaves do nodo e insere a nova chave no lugar correto
void inserirNaoCheio (struct nodo* x, int32_t chave, int32_t t_arvore)  {
  int i = x->n;

  // caso em que x eh folha
  if (x->ehFolha == true) {
    while (i >= 1 && chave < x->chaves[i]) {
      x->chaves[i+1] = x->chaves[i];
      --i;
    }
    x->chaves[i+1] = chave;
    ++(x->n);
  }
  // caso em que x nao eh folha
  else {
    while (i >= 1 && chave < x->chaves[i]) {
      --i;
    }
    ++i;

    // caso em que o filho está cheio
    if (x->filhos[i]->n == 2 *t_arvore -1) {
      dividirFilho(x, i, t_arvore);
      if (chave > x->chaves[i]) {
        ++i;
      }
    }
    inserirNaoCheio(x->filhos[i], chave, t_arvore);
  }
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
    return NULL;
  
  struct filaNodo * itemRemove = f->inicio;
  struct nodo* n = itemRemove->nodoT;

  //atualiza o novo primeiro item da fila pos desenfileirar
  f->inicio = itemRemove->prox;
  if(f->inicio == NULL)
    f->fim = NULL;

  free(itemRemove); // libera apenas o elemento da fila 
  return n;

} 

// função de auxílio para caso de fila vazia
int32_t filaVazia(struct fila* f) {
    return (f->inicio == NULL);
}

//destroi a fila e libera memoria
void destroiFila(struct fila* f) {
    while (!filaVazia(f))
        desenfileirar(f);
    free(f);
}
