#ifndef LISTA_H
#define LISTA_H

typedef struct nolista{
    double info;
    struct nolista *prox;
}NoLista;

int qtdElementos(NoLista **l);
int estaVazia(NoLista **l);
void criarLista(NoLista **l);
void imprimeElementos(NoLista **l);
void liberarLista(NoLista **l);
void insereOrdenado(NoLista **l, double v); 

#endif