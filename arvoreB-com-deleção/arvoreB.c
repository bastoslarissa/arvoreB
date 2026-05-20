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

void merge (struct nodo *pai, struct nodo *filhoA, struct nodo *filhoB, int32_t chave) {

  if (!pai || !filhoA || !filhoB)
    return;

  // a chave desce para o filhoA
  filhoA->chaves[filhoA->n] = chave;

  // filhoA recebe as chaves de filhoB
  for (int i = 0; i < filhoB->n; i++) {
    filhoA->chaves[filhoA->n + 1 + i] = filhoB->chaves[i];  // filhoA recebe as chaves de filhoB
  }

  // filhoA recebe os filhos de filhoB se forem nós internos
  if (filhoA->ehFolha == false && filhoB->ehFolha == false) {

    for (int i = 0; i < filhoB->n + 1; i++) {
        filhoA->filhos[filhoA->n + 1 + i] = filhoB->filhos[i];  // filhoA recebe os filhos de filhoB
    }
  }

  // atualiza a quantidade de chaves de filhoA
  filhoA->n = filhoA->n + 1 + filhoB->n;

void redistribuicao (struct arvoreB* arvore, struct nodo* pai, int32_t i) {

  // encontra o irmão imediato com mais chaves 
  int indiceB = -1 ;

  for (int j = 0; j <= pai->n; j++) {
    if (j != i) {
      if (indiceB == -1 || pai->filhos[j]->n > pai->filhos[indiceB]->n) {
              indiceB = j; 
      }
    }
  }

  struct nodo* b = pai->filhos[indiceB];

  // se b tem mais de t chaves
  if (b->n >= arvore->t_arvore) {

    // se b eh filho direito
    if (indiceB > i) {
      // pasa uma chave do pai para o filho i
      pai->filhos[i]->chaves[pai->filhos[i]->n] = pai->chaves[i];
      pai->filhos[i]->n++;

      pai->chaves[i] = b->chaves[0];  // pai recebe a primeira chave de b

      removeChaveNodo(b, b->chaves[0]);   // ajusta b
    }
    // se b eh filho esquerdo
    else {
      // abre espaco no inicio do filho i
      for (int j = pai->filhos[i]->n; j > 0; j--) {
        pai->filhos[i]->chaves[j] = pai->filhos[i]->chaves[j - 1];
      }

      // chave do pai desce para o início do filho i
      pai->filhos[i]->chaves[0] = pai->chaves[i - 1];
      pai->filhos[i]->n++;

      // chave do filho b sobe para o pai
      pai->chaves[i - 1] = b->chaves[b->n - 1];
      // remove a chave que subiu de b
      removeChaveNodo(b, b->chaves[b->n - 1]);  // ajusta b
    }
  }
  // nenhum irmao imediato possui pelo menos t chaves 
  else {
    if (indiceB > i) {
      // b eh filho direito
      merge(pai, pai->filhos[i], b, pai->chaves[i]);
      removeChaveNodo(pai, pai->chaves[i]);
      excluiNodo(b);
      ajustaFilhos(pai, indiceB);
    }
    else {
      // b eh filho esquerdo
      merge(pai, b, pai->filhos[i], pai->chaves[i - 1]);
      removeChaveNodo(pai, pai->chaves[i - 1]);
      excluiNodo(pai->filhos[i]);
      ajustaFilhos(pai, i);     
    }

    
    // o pai era a raiz e ficou sem nodos
    if (arvore->raiz == pai && pai->n < 1) {
        arvore->raiz = pai->filhos[0];
        excluiNodo(pai);
    }
  }

}

//remove uma chave, se foi removida, retorna verdadeiro. Caso contrário, retorna falso
//caso 1 é tratado dentro dessa função (caso o nodo excluido esta em uma folha)
bool removerChaveArvoreB(struct arvoreB* arvore, struct nodo *x, int32_t chave) {
  
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
    }  

    // se ambas as subarvores tem a quantidade minima de chaves 
    else if (x->filhos[i]->n == arvore->t_arvore - 1 && x->filhos[i+1]->n == arvore->t_arvore - 1){
      merge(x, x->filhos[i], x->filhos[i+1], x->chaves[i]);
      removeChaveNodo(x, chave);

      excluiNodo(x->filhos[i+1]);
      ajustaFilhos(x, i + 1);  // ajusta os filhos do pai

      // se x era raiz e nao tem mais chaves
      if (x->n < 1) {
        ajustaRaiz(arvore);
        return removerChaveArvoreB(arvore, arvore->raiz, chave);
      }

      removerChaveArvoreB(arvore, x->filhos[i], chave);

      return true;
    }

  //se não achou e é folha
  } else {
    if (x->ehFolha)
      return false;
  }

  // ajusta a quantidade de chave dos filhos antes de descer  
  if (x->filhos[i]->n == arvore->t_arvore - 1) {
    redistribuicao(arvore, x, i);
  }

  return removerChaveArvoreB(arvore, x->filhos[i], chave);
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