#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "util.h"

//---------------------- Funções auxiliares (implementação da deleção) -------------------------

// subfunção para remover a chave de um nodo folha
void removeFolha(struct nodo* x, int i) {
  // desloca as chaves uma posição para a esquerda
  for(int j = i + 1; j < x->n; j++) {
    x->chaves[j - 1] = x->chaves[j];
  }

  //diminui a contagem de chaves no nodo
  x->n--;
}

// encontra o predecessor da chave K 
int32_t encontraPred(struct nodo* x, int i) {
  //filho a esquerda da chave
  struct nodo* atual = x->filhos[i];

  //desce até a folha mais a direita
  while(!atual->ehFolha) {
    atual = atual->filhos[atual->n]; //o ultimo ponteiro aponta para os maiores valores do nodo
  }

  //predecessor é a ultima chave da folha
  return atual->chaves[atual->n - 1];
}

// encontra o sucessor da chave K 
int32_t encontraSuc(struct nodo* x, int i) {
  //filho a direita da chave
  struct nodo* atual = x->filhos[i + 1];

  //desce até a folha mais a esquerda da árvore
  while(!atual->ehFolha) {
    atual = atual->filhos[0]; //o primeiro ponteiro de filho aponta para os menores valores
  }

  // O sucessor é a primeira chave da folha
  return atual->chaves[0];
}

// ajusta raiz no caso dela ficar vaiza
void ajustaRaiz(struct arvoreB* arvore) {
  // caso base
  if (arvore == NULL || arvore->raiz == NULL) {
    return;
  }

  // se a raiz ficar vazia e tiver filhos
  if (arvore->raiz->n == 0 && !arvore->raiz->ehFolha) {
    struct nodo* antigaRaiz = arvore->raiz; //nao perder o ponteiro

    //primeiro filho vira a nova raiz
    arvore->raiz = antigaRaiz->filhos[0];

    //libera memoria
    free(antigaRaiz->chaves);
    free(antigaRaiz->filhos);
    free(antigaRaiz);
  }

}

void removeChaveNodo(struct nodo *x, int32_t chave) {

  int i = 0;

  // procura chave
  while (i < x->n && chave > x->chaves[i]) {
    i++;
  }

  // se encontrou a chave
  if (i < x->n && chave == x->chaves[i]) {
    // desloca as chaves para esquerda
    for (int j = i; j < x->n - 1; j++) {
      x->chaves[j] = x->chaves[j+1] ;
    }

    // se for nodo interno
    if (!x->ehFolha) {
      for (int j = i + 1; j < x->n; j++) {
          x->filhos[j] = x->filhos[j+1];
      }
    }

    x->n--;
  }
}

void excluiNodo(struct nodo *x) {

  if (!x)
    return;

  // libera os filhos
  free(x->filhos);

  // libera as chaves
  free(x->chaves);

  // libera o nodo
  free(x);
  x = NULL;
}

void ajustaFilhos (struct nodo *x, int32_t i) {

  for (int j = i; j < x->n + 1; j++) {
    x->filhos[j] = x->filhos[j + 1];
  }
}

//---------------------- Funções auxiliares (primeira parte do trabalho) -------------------------

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

  //faz todos os ponteiros apontarem para NULL para evitar segfault
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
  struct nodo *y = x->filhos[i];

  // cria o novo nodo irmao
  struct nodo* z = alocarNodo(t_arvore);
  z->ehFolha = y->ehFolha;
  z->n = t_arvore - 1;

  for (int j = 0; j < 2*t_arvore - 1; j++) {
    z->chaves[j] = 0;
  }

  // transfere as chaves de y para z
  for (int j = 0; j < t_arvore - 1; ++j) {
    z->chaves[j] = y->chaves[j+t_arvore];
  } 

  // transfere os maiores filhos de y para z
  if (y->ehFolha == false) {
    for (int j = 0; j < t_arvore; ++j) {
      z->filhos[j] = y->filhos[j + t_arvore];
    }
  }
    
  y->n = t_arvore -1;

  // desloca os filhos de x para a direita para abrir espaço para o novo nodo na posição i+1
  for (int j = x->n; j >= i+1; --j) {
    x->filhos[j+1] = x->filhos[j];
  }

  x->filhos[i+1] = z;

  // desloca as chaves para abrir espaço para a chave mediana ser inserida na posição correta em x
  for (int j = x->n - 1; j >= i; --j) {
    x->chaves[j+1] = x->chaves[j];
  }

  //x->chaves[i] = y->chaves[t_arvore];
  x->chaves[i] = y->chaves[t_arvore - 1];
  x->n++;
  }


// divide a raiz da arvore, aumentando a altura da árvore
struct nodo* dividirRaiz (struct arvoreB* arvore) {

  // cria a nova raiz
  struct nodo* s = alocarNodo(arvore->t_arvore);
  s->ehFolha = false;
  s->n = 0;
  s->filhos[0] = arvore->raiz;
  arvore->raiz = s;

  // divide a antiga raiz 
  dividirFilho(s, 0, arvore->t_arvore);

  return s;
}

// percorre as chaves do nodo e insere a nova chave no lugar correto
void inserirNaoCheio (struct nodo* x, int32_t chave, int32_t t_arvore)  {
  int i = x->n - 1;

  // caso em que x eh folha
  if (x->ehFolha == true) {
    while (i >= 0 && chave < x->chaves[i]) {
      x->chaves[i+1] = x->chaves[i];
      --i;
    }
    x->chaves[i+1] = chave;
    ++(x->n);
  }
  // caso em que x nao eh folha
  else {
    while (i >= 0 && chave < x->chaves[i]) {
      --i;
    }
    ++i;

    // caso em que o filho está cheio
    if (x->filhos[i]!= NULL && x->filhos[i]->n == 2 *t_arvore -1) {
      dividirFilho(x, i, t_arvore);
      if (chave > x->chaves[i]) {
        ++i;
      }
    }
    inserirNaoCheio(x->filhos[i], chave, t_arvore);
  }
}

// percorre a árvore imprimindo as chaves em ordem recursivamente
void imprimeNodo (struct nodo* x) {
  if (x == NULL) 
    return;

  for (int i = 0; i < x->n; i++) {
    if(x->ehFolha == false) {
      imprimeNodo(x->filhos[i]);
    }
    printf("%d ", x->chaves[i]);
  }
  if (x->ehFolha == false) {
    imprimeNodo(x->filhos[x->n]);
  }
}

// libera os nodos da arvore
void liberarArvoreB (struct nodo* x) {
  if (!x)
    return;

  // caso em que o nodo é interno
  if (x->ehFolha == false) {
    for (int i = 0; i<= x->n; i++) {
      liberarArvoreB(x->filhos[i]);
    }
  }
  free(x->chaves);
  if (x->filhos) {
    free(x->filhos);
  }
  free(x);
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
