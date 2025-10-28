#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void criarLista(NoLista **l){
    *l = NULL;
}

int estaVazia(NoLista **l){
    return(*l == NULL);
}

int qtdElementos(NoLista **l){
    int qtd = 0;
    NoLista *p;

    for(p = *l; p != NULL; p = p->prox){
        qtd++;
    }

    return qtd;
}

void insereOrdenado(NoLista **l, double v){
    NoLista *p, *ant = NULL;
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));

    if(novo != NULL){
        novo->info = v;

        for(p = *l; p != NULL && p->info < v; p = p->prox){
            ant = p;
        }

        novo->prox = p;
        
        if(ant == NULL){
            *l = novo;
        }
        else{
            ant->prox = novo;
        }
    }
    else{
        printf("Não foi possível alocar espaço!\n");
    }
}

void insere(NoLista **l, double v){
    NoLista *p, *ant = NULL;
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));

    if(novo != NULL){
        novo->info = v;

        for(p = *l; p != NULL; p = p->prox){
            ant = p;
        }

        novo->prox = p;
        
        if(ant == NULL){
            *l = novo;
        }
        else{
            ant->prox = novo;
        }
    }
    else{
        printf("Não foi possível alocar espaço!\n");
    }
}

void imprimeElementos(NoLista **l){
    if(!estaVazia(l)){   
        printf("Os valores são: \n");
        for(NoLista *p = *l; p != NULL; p = p->prox){
            printf("%.2lf\n", p->info);
        }
    }
    else{
        printf("A lista está vazia!!\n");
    }
}

void liberarLista(NoLista **l){
    NoLista *p, *temp;

    for(p = *l; p != NULL; p = temp){
        temp = p->prox;
        free(p);
    }

    *l = NULL;
}
